#include <stdio.h>
int main() {
	int a, b;
	scanf("%d %d", &a, &b);
	if (a == 100 && b == 100)
		printf("YES");
	else
		printf("NO");
	return 0;
}