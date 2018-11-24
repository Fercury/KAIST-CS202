#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

int sail(int a, int b) {
	std::cout << "? " << a << " " << b << std::endl << std::flush;
	int v; std::cin >> v;
	if(v == -202) {
		exit(0);
	}
	return v;
}

void report(std::vector<std::pair<int, int>> bridges) {
	std::cout << "!" << std::endl << std::flush;
	std::cout << bridges.size() << std::endl << std::flush;
	for(size_t i = 0; i < bridges.size(); i++) {
		std::cout << bridges[i].first << " " << bridges[i].second << std::endl << std::flush;
	}
}

int main() {
	int N;
	std::cin >> N;
	if(N < 0) {
		/* this means your code is already wrong, exit immediately */
		return 0;
	}

	/* IMPLEMENT HERE */
	/* IMPLEMENT HERE */
	/* IMPLEMENT HERE */
	/* IMPLEMENT HERE */
	// Below is WRONG. It assumes every bridge connects (i, i).
	
	std::vector<std::pair<int, int>> answer;
	for(int i = 1; i <= N; i++) {
		if(sail(i, i) == -1) {
			answer.push_back(std::make_pair(i, i));
		}
	}
	report(answer);

	/* IMPLEMENT HERE */
	/* IMPLEMENT HERE */
	/* IMPLEMENT HERE */
	/* IMPLEMENT HERE */
	/* IMPLEMENT HERE */
	/* IMPLEMENT HERE */
	
	return 0;
}