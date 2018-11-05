#include <cstdio>
#include <vector>
using namespace std;

int calPrice(int i, int j, int k) {
	return ((i * j + j * k + k * i) ^ (17 * i + 23 * j + 29 * k)) % 99 + 1;
}

int main() {
	int M, N, H, Q;
	int x1, y1, z1, x2, y2, z2;
	int i, j, k;

	scanf("%d %d %d", &H, &N, &M);
	vector<vector<vector<int > > > price(M+1, vector<vector<int> >(N+1, vector<int>(H+1, 0)));
	vector<vector<vector<long long int > > > priceSum(M+1, vector<vector<long long int> >(N+1, vector<long long int>(H+1, 0)));

	for (i = 1; i <= M; i++) {
		for (j = 1; j <= N; j++) {
			for (k = 1; k <= H; k++) {
				price[i][j][k] = calPrice(i, j, k);
			}
		}
	}

	priceSum[1][1][1] = price[1][1][1];

	for (i = 2; i <= M; i++)
		priceSum[i][1][1] = price[i][1][1] + priceSum[i - 1][1][1];

	for (j = 2; j <= N; j++)
		priceSum[1][j][1] = price[1][j][1] + priceSum[1][j - 1][1];

	for (k = 2; k <= H; k++)
		priceSum[1][1][k] = price[1][1][k] + priceSum[1][1][k - 1];

	for (i = 2; i <= M; i++)
		for (j = 2; j <= N; j++)
			priceSum[i][j][1] = price[i][j][1] + priceSum[i - 1][j][1] + priceSum[i][j - 1][1] - priceSum[i - 1][j - 1][1];

	for (i = 2; i <= M; i++)
		for (k = 2; k <= H; k++)
			priceSum[i][1][k] = price[i][1][k] + priceSum[i - 1][1][k] + priceSum[i][1][k - 1] - priceSum[i - 1][1][k - 1];

	for (k = 2; k <= H; k++)
		for (j = 2; j <= N; j++)
			priceSum[1][j][k] = price[1][j][k] + priceSum[1][j - 1][k] + priceSum[1][j][k - 1] - priceSum[1][j - 1][k - 1];

	for (i = 2; i <= M; i++)
		for (j = 2; j <= N; j++)
			for (k = 2; k <= H; k++)
				priceSum[i][j][k] = price[i][j][k] + priceSum[i - 1][j][k] + priceSum[i][j - 1][k] + priceSum[i][j][k - 1] \
				- priceSum[i - 1][j - 1][k] - priceSum[i - 1][j][k - 1] - priceSum[i][j - 1][k - 1] + priceSum[i - 1][j - 1][k - 1];



	scanf("%d", &Q);
	while (Q--) {
		scanf("%d %d %d %d %d %d", &z1, &y1, &x1, &z2, &y2, &x2);
		long long int soldPrice = priceSum[x2][y2][z2] - priceSum[x1 - 1][y2][z2] - priceSum[x2][y1 - 1][z2] - priceSum[x2][y2][z1 - 1] \
			+ priceSum[x1 - 1][y1 - 1][z2] + priceSum[x1 - 1][y2][z1 - 1] + priceSum[x2][y1 - 1][z1 - 1] - priceSum[x1 - 1][y1 - 1][z1 - 1];
		printf("%lld\n", soldPrice);

	}
	return 0;
}