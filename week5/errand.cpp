#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <utility>

using namespace std;

vector<pair<int, int> > buildings(110000);
vector<long long> stree(530000); //sum segment tree
vector<long long> mtree(530000); //min segment tree

long long dist(int x1, int x2, int y1, int y2){
    return abs(x1 - x2) + abs(y1-y2);
}

void update(int pos, int s, int e, int p, long long v){

    if(s == e){
        stree[p] = v;
        return;
    }

    int m = (s + e) / 2;
    if(pos <= m) update(pos, s, m, 2*p, v);
    else update(pos, m+1, e, 2*p+1, v);

    stree[p] = stree[2*p] + stree[2*p+1];
}

void update2(int pos, int s, int e, int p, long long v){
    
    if(s == e){
        mtree[p] = v;
        return;
    }

    int m = (s + e) / 2;
    if(pos <= m) update2(pos, s, m, 2*p, v);
    else update2(pos, m+1, e, 2*p+1, v);

    mtree[p] = min(mtree[2*p], mtree[2*p+1]);
}

long long subSum(int s, int e, int ps, int pe, int p){

    
    if(ps >= s && pe <= e) return stree[p];
    if(pe < s || ps > e) return 0;

    int m = (ps + pe) / 2;
    return subSum(s, e, ps, m, 2*p) + subSum(s, e, m+1, pe, 2*p+1);
}

long long findMin(int s, int e, int ps, int pe, int p){
    
    if(s > e) return 0;
    if(ps >= s && pe <= e) return mtree[p];
    if(pe < s || ps > e) return 0;

    int m = (ps + pe) / 2;
    return min(findMin(s, e, ps, m, 2*p), findMin(s, e, m+1, pe, 2*p+1));

}


int main(){

    int n, m;
    int x, y, w;
    long long z;
    char req;
    cin >> n >> m;

    cin >> x >> y;
    buildings[1] = make_pair(x, y);

    for(int i=2;i<=n;i++){
        cin >> x >> y;
        z = dist(x, buildings[i-1].first, y, buildings[i-1].second);
        buildings[i] = make_pair(x, y);
        update(i-1, 1, n-1, 1, z);

    }

    for(int i=1;i<=n-2;i++){
        z = dist(buildings[i].first, buildings[i+2].first, buildings[i].second, buildings[i+2].second)\
            - dist(buildings[i].first, buildings[i+1].first, buildings[i].second, buildings[i+1].second)\
            - dist(buildings[i+1].first, buildings[i+2].first, buildings[i+1].second, buildings[i+2].second);
        update2(i, 1, n-2, 1, z);
    }

    while(m--){
        cin >> req;
        if(req == 'Q'){
            cin >> x >> y;

            z = subSum(x, y-1, 1, n-1, 1) + findMin(x, y-2, 1, n-2, 1);
            cout << z << endl;

        }

        else{
            cin >> x >> y >> w;
            buildings[x] = make_pair(y, w);

            if(x > 1){
                z = dist(buildings[x-1].first, y, buildings[x-1].second, w);
                update(x-1, 1, n-1, 1, z);
                
                if(x > 2){
                    z = dist(buildings[x].first, buildings[x-2].first, buildings[x].second, buildings[x-2].second)\
                        - dist(buildings[x].first, buildings[x-1].first, buildings[x].second, buildings[x-1].second)\
                        - dist(buildings[x-1].first, buildings[x-2].first, buildings[x-1].second, buildings[x-2].second);
                    update2(x-2, 1, n-2, 1, z);
                }

                if(x < n){
                    z = dist(buildings[x-1].first, buildings[x+1].first, buildings[x-1].second, buildings[x+1].second)\
                        - dist(buildings[x].first, buildings[x-1].first, buildings[x].second, buildings[x-1].second)\
                        - dist(buildings[x].first, buildings[x+1].first, buildings[x].second, buildings[x+1].second);
                    update2(x-1, 1, n-2, 1, z);
                }
            }

            if(x < n){
                z = dist(buildings[x+1].first, y, buildings[x+1].second, w);
                update(x, 1, n-1, 1, z);
                if(x < n-1){
                    z = dist(buildings[x].first, buildings[x+2].first, buildings[x].second, buildings[x+2].second)\
                        - dist(buildings[x].first, buildings[x+1].first, buildings[x].second, buildings[x+1].second)\
                        - dist(buildings[x+1].first, buildings[x+2].first, buildings[x+1].second, buildings[x+2].second);
                    update2(x, 1, n-2, 1, z);
                }
            }
            
        }
    }
    return 0;
}