#include <iostream>
#include <algorithm>
#include <vector>
#define RMD 987654321
using namespace std;

int n, c;
int cake[300];
long long int cakeSum[300][50000];

long long int sum(long long int x, long long int y) {
	return ((x%RMD) + (y%RMD)) % RMD;
}

long long int mul(long long int x, long long int y) {
	return (long long)(x % RMD) * (y % RMD) % RMD;
}

long long int sub(long long int x, long long int y) {
	return (x%RMD - y % RMD + RMD) % RMD;
}

//calculate x^n
long long int power(long long int x, long long int n) {
	long long int ret;

	if (n == 0)
		return 1;

	if (n == 1)
		return x;

	if (n % 2) {
		ret = power(x, (n - 1) / 2);
		return mul(mul(ret, ret), x);
	}

	else {
		ret = power(x, n / 2);
		return mul(ret, ret);
	}
}

int main() {

	long long int vol = 0;
	cin >> n;

	for (int i = 0; i < n; i++)
		cin >> cake[i];

	cin >> c;

	for (int i = 0; i <= n; i++)
		cakeSum[i][0] = 1;

	for (int i = 1; i <= c; i++)
		cakeSum[0][i] = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= c; j++) {

			if (j < cake[i - 1])
				cakeSum[i][j] = cakeSum[i - 1][j];
			if (j >= cake[i - 1])
				cakeSum[i][j] = sub(cakeSum[i - 1][j], cakeSum[i - 1][j - cake[i - 1]]);
		}
	}


	cakeSum[n][0] = 1;

	for (int i = 0; i < c; i++) {
		if (cakeSum[n][i] > 0)
			vol = sum(vol, mul(power(c - i, n), cakeSum[n][i]));
		else
			vol = sub(vol, mul(power(c - i, n), -cakeSum[n][i]));
	}

	/*
	for (int j = 0; j <= c; j++)
		printf("%4d", cakeSum[n][j]);
	printf("\n");
	*/

	cout << vol << endl;

	return 0;
}