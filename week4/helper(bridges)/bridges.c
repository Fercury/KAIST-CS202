#include <stdio.h>
#include <stdlib.h>

int sail(int a, int b) {
	printf("? %d %d\n", a, b); fflush(stdout);
	int v; scanf("%d", &v);
	if(v == -202) {
		exit(0);
	}
	return v;
}

void report(int num_bridges, int *p, int *q) {
	printf("!\n"); fflush(stdout);
	printf("%d\n", num_bridges); fflush(stdout);
	for(int i = 0; i < num_bridges; i++) {
		printf("%d %d\n", p[i], q[i]); fflush(stdout);
	}
}

int main() {		
	int N;
	scanf("%d", &N);
	if(N < 0) {
		/* this means your code is already wrong, exit immediately */
		return 0;
	}

	/* IMPLEMENT HERE */
	/* IMPLEMENT HERE */
	/* IMPLEMENT HERE */
	/* IMPLEMENT HERE */
	// Below is WRONG. It assumes every bridge connects (i, i).
	// Don't forget to initialize all global variables.

	#define MAX_N 50000
	int num_bridges = 0;
	static int p[MAX_N];
	static int q[MAX_N];
	#undef MAX_N

	int i;
	for(i = 1; i <= N; i++) {
		if(sail(i, i) == -1) {
			p[num_bridges] = i;
			q[num_bridges] = i;
			num_bridges += 1;
		}
	}

	report(num_bridges, p, q);
	/* IMPLEMENT HERE */
	/* IMPLEMENT HERE */
	/* IMPLEMENT HERE */
	/* IMPLEMENT HERE */
	/* IMPLEMENT HERE */
	/* IMPLEMENT HERE */

	return 0;
}