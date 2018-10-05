#include <iostream>
#define RMD 987654321
using namespace std;

int mul(int x, int y) {
	return (long long)(x % RMD) * (y % RMD) % RMD;
}

int sum(int x, int y) {
	return ((x%RMD) + (y%RMD)) % RMD;
}

typedef struct M{
	int arr[10][10];	// arr[x][y]
	M(){
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				arr[i][j] = 0;
	}
}mtrx;

mtrx operator*(mtrx m1, mtrx m2) {
	mtrx ret;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 10; k++) {
				ret.arr[j][i] = sum(ret.arr[j][i], mul(m1.arr[k][i], m2.arr[j][k]));
			}
		}
	}
	return ret;
}

mtrx operator+(mtrx m1, mtrx m2) {
	mtrx ret;

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			ret.arr[i][j] = sum(m1.arr[i][j], m2.arr[i][j]);

	return ret;

}

mtrx power(mtrx A, long long int k) {
	mtrx ret;
	
	if (k == 0) {
		for(int i=0;i<10;i++)
			for (int j = 0; j < 10; j++)
				ret.arr[i][j] = i == j ? 1 : 0;
		return ret;
	}

	if (k == 1)
		return A;
	
	if (k % 2) {
		ret = power(A, (k - 1) / 2);
		return ret * ret * A;
	}
	ret = power(A, k / 2);
	return ret * ret;
}

mtrx matrixSum(mtrx A, long long int k) {
	mtrx I;

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			I.arr[i][j] = i == j ? 1 : 0;

	if (k == 0)
		return I;

	if (k == 1)
		return I+A;

	if (k % 2)
		return (I + power(A, (k + 1) / 2)) * matrixSum(A, (k - 1) / 2);

	else
		return  power(A, k) + matrixSum(A, k - 1);
}



int main() {
	int n;
	long long int k;
	cin >> n >> k;

	//input
	mtrx A;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> A.arr[j][i]; // (x , y)

	A = matrixSum(A, k);

	//output
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << A.arr[j][i] << " "; // (x , y)
		cout << endl;
	}

	return 0;
}