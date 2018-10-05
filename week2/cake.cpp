#include <iostream>
#include <algorithm>
#include <vector>
#define RMD 987654321
using namespace std;

int sum(long long int x, long long int y) {
	return ((x%RMD) + (y%RMD)) % RMD;
}

int mul(long long int x, long long int y) {
	return (long long)(x % RMD) * (y % RMD) % RMD;
}

int sub(long long int x, long long int y) {
	return (x%RMD - y % RMD + RMD) % RMD;
}

//calculate x^n
long long int power(long long int x, long long int n) {
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

long long int volume(long long int c, vector<long long int>& side) {

	const int dim = side.size();
	long long int ret = 1;
	long long int subrect, subside, subdim;
	long long int size = power(2, dim);

	for (int i = 0; i < dim; i++)
		ret = mul(ret, c);

	for (int i = 1; i < size - 1; i++) {

		subside = c;
		subrect = 1;
		subdim = 0;

		for (int j = 0; j < dim; j++) {
			if (i & (1 << j)) {
				subside -= side[j];
				subdim++;
				if (subside < 0)
					break;
			}
		}

		if (subside > 0) {
			for (int j = 0; j < dim; j++)
				subrect = mul(subrect, subside);

			if (subdim % 2)
				ret = sub(ret, subrect);
			else
				ret = sum(ret, subrect);
		}

	}

	return ret;

}


// time limit: 2 sec
int main() {

	int n;
	long long int c;
	cin >> n;

	vector<long long int> side(n);
	for (int i = 0; i < n; i++)
		cin >> side[i];

	cin >> c;

	cout << volume(c, side);

	return 0;
}