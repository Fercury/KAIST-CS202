#include <stdio.h>
#include <stdlib.h>

int pack(int SZ, int *M) {
    printf("? %d", SZ);
    for(int i=0;i<SZ;i++) printf(" %d", M[i]);
    puts("");
    fflush(stdout);
    int ret; scanf("%d", &ret);
    if(ret == -202) exit(0);
    return ret;
}

void report (int N, int *M) {
    printf("!");
    for(int i=0;i<N;i++) printf(" %d", M[i]);
    puts("");
    fflush(stdout);
}

int main() {
    int N; scanf("%d", &N);
    int *sel = (int *)malloc(N * sizeof(int));
    int *ans = (int *)malloc(N * sizeof(int));
    
    /* IMPLEMENT HERE */
    /* IMPLEMENT HERE */
    /* IMPLEMENT HERE */
    /* IMPLEMENT HERE */
    // Below is an example.
    // Don't forget to initialize all global variables.

    int turn = 0;
    
    while(turn < 3){
        for(int i=0;i<N;i++) sel[i] = 0;
        
        int SZ = N;
        for(int i=0;i<N;i++){
            sel[i] = i+1;
        }
        int ret = pack(SZ, sel);
        turn++;
    }
    for(int i=0;i<N;i++){
        ans[i] = i+1;
    }
    report(N, ans);
    return 0;
}