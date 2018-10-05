#include <iostream>
#define RMD 987654321
using namespace std;

int sum(int x, int y) {
	return ((x%RMD) + (y%RMD)) % RMD;
}

int mul(int x, int y) {
	return (long long)(x % RMD) * (y % RMD) % RMD;
}

//calculate x^n
int power(int x, int n) {
	int ret;

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


// 2 sec
int main() {

	int N, rail, railSum = 0;
	int ret = 1;
	int cTable[5010][5010];

	for (int i = 0; i <= 5000; i++) {
		for (int j = 0; j <= 5000; j++)
			cTable[j][i] = 0;
	}

	//combination table
	cTable[0][0] = 1;
	for (int i = 1; i <= 5000; i++) {
		cTable[i][0] = 0;
		cTable[0][i] = 1;
	}
	for (int i = 1; i <= 5000; i++) {
		for (int j = 1; j <= i; j++)
			cTable[j][i] = sum(cTable[j - 1][i - 1], cTable[j][i - 1]);
	}


	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> rail;
		railSum += rail;
		ret = mul(ret, power(2, rail - 1));
		ret = mul(ret, cTable[rail][railSum]);
	}

	cout << ret;

	return 0;
}