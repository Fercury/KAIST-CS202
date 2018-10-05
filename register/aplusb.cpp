#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
int main() {
	int t;
	char n[3010];
	scanf("%d\n", &t);
	while (t--) {
		fgets(n, 3010, stdin);
		int nsize = strlen(n)-1;
		sort(n, n + nsize);
		int a = n[0] - '0';
		for (int i = 1; i < nsize; i++) {
			n[i] = (n[i] - '0') + a;
			if (n[i] >= 10) {
				a = 1;
				n[i] = n[i] - 10 + '0';
				if (i == nsize - 1)
					printf("1");
			}
			else {
				n[i] = n[i] + '0';
				break;
			}
		}
		for (int i = nsize - 1; i >= 1; i--)
			printf("%c", n[i]);
		printf("\n");
	}
	return 0;
}