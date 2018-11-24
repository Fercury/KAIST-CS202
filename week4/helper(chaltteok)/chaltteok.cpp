#include <cstdio>
#include <vector>
#include <cstdlib>

int pack(std::vector<int> &M) {
    printf("? %d", (int)M.size());
    for(int &x : M) printf(" %d", x);
    puts("");
    fflush(stdout);
    int ret; scanf("%d", &ret);
    if(ret == -202) exit(0);
    return ret;
}

void report(std::vector<int> &M) {
    printf("!");
    for(int &x : M) printf(" %d", x);
    puts("");
    fflush(stdout);
}

int main() {
    int N; scanf("%d", &N);
    std::vector<int> sel, ans;
    
    /* IMPLEMENT HERE */
    /* IMPLEMENT HERE */
    /* IMPLEMENT HERE */
    /* IMPLEMENT HERE */
    // Below is an example.
    // Don't forget to initialize all global variables.

    int turn = 0;
    
    while(turn < 3){
        sel.clear();
        for(int i=1;i<=N;i++){
            sel.push_back(i);
        }
        int ret = pack(sel);
        turn++;
    }
    for(int i=1;i<=N;i++){
        ans.push_back(i);
    }
    report(ans);
    return 0;
}
