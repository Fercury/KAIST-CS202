#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

int sail(int a, int b) {
	std::cout << "? " << a << " " << b << std::endl << std::flush;
	int v; std::cin >> v;
	if (v == -202) {
		exit(0);
	}
	return v;
}

void report(std::vector<std::pair<int, int>> bridges) {
	std::cout << "!" << std::endl << std::flush;
	std::cout << bridges.size() << std::endl << std::flush;
	for (size_t i = 0; i < bridges.size(); i++) {
		std::cout << bridges[i].first << " " << bridges[i].second << std::endl << std::flush;
	}
}

void add(vector<pair<int, int> > &answer, int a, int b) {
	answer.push_back(make_pair(a, b));
	return;
}


int main() {
	int N;
	std::cin >> N;
	if (N < 0) {
		/* this means your code is already wrong, exit immediately */
		return 0;
	}

	vector<pair<int, int> > answer;
	vector<int> up(N + 1), down(N + 1);
	int a, b;
	int last = 0, now;

	for (int i = 1; i <= N; i++) {
		up[i] = i;
		down[i] = i;
	}

	if (N > 1)
		if (sail(N, N) == -1)
			add(answer, N, N);

	while (up.size() > 2 && down.size() > 2) {
		a = up.back();
		b = down.back();
		now = sail(a - 1, b);

		switch (now) {
		case -1:
			add(answer, a - 1, b);
			if (last == 1)
				add(answer, a, b);
			up.pop_back();
			break;
		case 0:
			if (last - now == 1) {
				add(answer, a, b);
			}
			up.pop_back();
			break;
		default:
			if (last - now == 1) {
				add(answer, a, b);
			}
			down.pop_back();
			break;
		}
		last = now;
	}

	if (down.size() > 2)
		down.pop_back();

	while (down.size() > 2) {
		b = down.back();
		down.pop_back();
		if (sail(1, b) == -1)
			add(answer, 1, b);
	}

	if (up.size() > 2)
		up.pop_back();

	while (up.size() > 2) {
		a = up.back();
		up.pop_back();
		now = sail(a, 1);
		if (now == -1) {
			add(answer, a, 1);
			if (last == 1)
				add(answer, a + 1, 1);
			last = 0;
			continue;
		}

		if (last - now == 1) {
			add(answer, a + 1, 1);
			last = 0;
		}
	}

	if (sail(1, 1) == -1)
		add(answer, 1, 1);

	if (last == 1)
		add(answer, 2, 1);

	report(answer);


	return 0;
}