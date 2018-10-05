#include <iostream>
#include <queue>
#include <set>
using namespace std;

int main() {

	int N, M, cnt = 0;
	long long int app;
	cin >> N >> M;
	queue<long long int> qapp;
	queue<long long int> frontapp;
	set<pair<long long int, int>> minapp;


	for (int i = 0; i < M; i++) {
		scanf("%lld", &app);
		qapp.push(app);
		frontapp.push(app);
		minapp.insert(make_pair(app, i));
	}

	printf("%lld ", (*minapp.begin()).first);

	for (int i = M; i < N; i++) {
		minapp.erase(make_pair(qapp.front(), cnt++));
		qapp.pop();

		scanf("%lld", &app);
		qapp.push(app);
		minapp.insert(make_pair(app, i));

		printf("%lld ", (*minapp.begin()).first);
	}

	for (int i = 0; i < M - 1; i++) {
		minapp.erase(make_pair(qapp.front(), cnt++));
		qapp.pop();

		app = frontapp.front();
		frontapp.pop();
		qapp.push(app);
		minapp.insert(make_pair(app, M + i));

		printf("%lld ", (*minapp.begin()).first);
	}

	return 0;
}