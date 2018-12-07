#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const long long LLMAX = 9987654321;
vector<long long> stree(530000);
vector<long long> mtree(530000, LLMAX);

void update(int pos, int s, int e, int p, long long v){

    if(s == e){
        stree[p] = v;
        mtree[p] = v;
        return;
    }

    int m = (s + e) / 2;
    if(pos <= m) update(pos, s, m, 2*p, v);
    else update(pos, m+1, e, 2*p+1, v);

    stree[p] = stree[2*p] + stree[2*p+1];
    mtree[p] = min(mtree[2*p], mtree[2*p+1]);
}

long long subSum(int s, int e, int ps, int pe, int p){

    if(ps >= s && pe <= e) return stree[p];
    if(pe < s || ps > e) return 0;

    int m = (ps + pe) / 2;
    return subSum(s, e, ps, m, 2*p) + subSum(s, e, m+1, pe, 2*p+1);
}

long long findMin(int s, int e, int ps, int pe, int p){
    
    if(ps >= s && pe <= e) return mtree[p];
    if(pe < s || ps > e) return LLMAX;

    int m = (ps + pe) / 2;
    return min(findMin(s, e, ps, m, 2*p), findMin(s, e, m+1, pe, 2*p+1));

}

int main(){

    int n, q;
    long long num;
    int req, l, r;
    cin >> n >> q;

    // init
    for(int i=1;i<=n;i++){
        cin >> num;
        update(i, 1, n, 1, num);
    }

    while(q--){
        cin >> req >> l >> r;

        switch(req){
        case 1:
        update(l, 1, n, 1, r);
        break;

        case 2:
        cout << findMin(l, r, 1, n, 1) << endl;
        break;

        case 3:
        cout << subSum(l, r, 1, n, 1) << endl;
        break;
        }
    }


    return 0;
}