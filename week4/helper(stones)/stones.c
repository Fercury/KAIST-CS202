#include <stdio.h>
#include <stdlib.h>

char weigh(int x, int y) {
	printf("? %d %d\n", x, y);
	fflush(stdout);
	char tmp[10]; scanf("%5s", tmp);
	if(tmp[0] == '-' && tmp[1] == '2' && tmp[2] == '0' && tmp[3] == '2') {
		exit(0);
	}
	return tmp[0];
}

void report(int num_min, int *min_pos, int num_max, int *max_pos) {
	printf("!\n"); fflush(stdout);
	printf("%d", num_min);
	for(size_t i = 0; i < num_min; i++) printf(" %d", min_pos[i]);
	printf("\n"); fflush(stdout);
	printf("%d", num_max);
	for(size_t i = 0; i < num_max; i++) printf(" %d", max_pos[i]);
	printf("\n"); fflush(stdout);
}

int main() {
	int T; scanf("%d", &T);
	int test_case_id;
	for(test_case_id = 1; test_case_id <= T; test_case_id++) {		
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
		// Below is an example solution that requires N(N-1) weighings.
		// Don't forget to initialize all global variables.

		#define MAX_N 400
		int num_min = 0;
		static int min_pos[MAX_N];
		int num_max = 0;
		static int max_pos[MAX_N];
		#undef MAX_N

		for(int i = 1; i <= N; i++) {
			int cnt_smaller = 0, cnt_larger = 0;
			for(int j = 1; j <= N; j++) {
				if(i != j) {
					switch(weigh(i, j)) {
						case '>': cnt_smaller += 1; break;
						case '<': cnt_larger += 1; break;
					}
				}
			}

			if(cnt_smaller == 0) {
				min_pos[num_min] = i;
				num_min += 1;
			}
			if(cnt_larger == 0) {
				max_pos[num_max] = i;
				num_max += 1;
			}
		}

		report(num_min, min_pos, num_max, max_pos);
		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */

	}
	return 0;
}