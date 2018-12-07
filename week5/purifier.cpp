#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<long long> oo(530000);
vector<long long> ox(530000);
vector<long long> xo(530000);
vector<long long> xx(530000);

void update(int pos, int s, int e, int p, long long v){
    if(e - s <= 1){
        if(pos == e) xo[p] = v;
        else ox[p] = v;
        return;
    }
    int m = (s + e) / 2;
    if(pos <= m) update(pos, s, m, 2*p, v);
    else update(pos, m+1, e, 2*p+1, v);
    if(e - s > 2){
        ox[p] = max(oo[2*p] + xx[2*p+1], max(ox[2*p] + xx[2*p+1], ox[2*p] + ox[2*p+1]));
        xo[p] = max(xx[2*p] + oo[2*p+1], max(xo[2*p] + xo[2*p+1], xx[2*p] + xo[2*p+1]));
    }
    else{
        ox[p] = max(oo[2*p] + xx[2*p+1], ox[2*p] + xx[2*p+1]);
        xo[p] = max(xx[2*p] + oo[2*p+1], xx[2*p] + xo[2*p+1]);
    }
    oo[p] = max(oo[2*p] + xo[2*p+1], max(ox[2*p] + xo[2*p+1], ox[2*p] + oo[2*p+1]));
    xx[p] = max(xo[2*p] + xx[2*p+1], max(xx[2*p] + xx[2*p+1], xx[2*p] + ox[2*p+1]));
}

int main(){
    int n, m, x, y;
    long long clean = 0;
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> x;
        update(i, 1, n, 1, x);
    }
    while(m--){
        cin >> x >> y;
        update(x, 1, n, 1, y);
        clean += max(max(ox[1], xo[1]), max(oo[1], xx[1]));
    }
    cout << clean;
    return 0;
}