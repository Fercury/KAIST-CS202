#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;


int main() {
	int N, M;
	int c, r, p;
	typedef pair<int, pair<int, int>> com; // core, clock , price
	long long int expense = 0, income = 0;

	/* input data */

	scanf("%d", &N);
	vector<com> bor(N);


	for (int i = 0; i < N; i++) {
		scanf("%d %d %d", &c, &r, &p);
		bor[i] = make_pair(c, make_pair(r, p));
		expense += p;
	}

	scanf("%d", &M);
	vector<com> req(N + M);

	for (int i = 0; i < N; i++) {
		req[i] = bor[i];
	}

	for (int i = N; i < N + M; i++) {
		scanf("%d %d %d", &c, &r, &p);
		req[i] = make_pair(c, make_pair(r, p));
	}

	sort(bor.begin(), bor.end());
	sort(req.begin(), req.end());

	/* input end */



	///* task 1 */
	//
	//long long int ans = 0;
	//for (int i = 0; i < M; i++) {
	//	if (i >= N || bor[i].second.second > req[M - 1 - i].second.second)
	//		break;
	//	ans += req[M - 1 - i].second.second - bor[i].second.second;
	//}

	//// task 2
	long long int ans = 0;
	int coreNum = 0;

	vector<vector<long long int > > profit(N + M, vector<long long int>(N * 50 + 1, 0));

	for (int j = 1; j <= N * 50; j++)
		if (req[0].first <= j)
			profit[0][j] = req[0].second.second;

	for (int i = 1; i < N + M; i++) {
		for (int j = 1; j <= N * 50; j++) {
			if (req[i].first > j)
				profit[i][j] = profit[i - 1][j];
			else
				profit[i][j] = max(profit[i - 1][j], profit[i - 1][j - req[i].first] + req[i].second.second);
		}
	}

	for (int i = 0; i < N; i++)
		coreNum += bor[i].first;

	printf("%lld", profit[N + M - 1][coreNum] - expense);


}