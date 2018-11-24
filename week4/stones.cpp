#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;


char weigh(int x, int y) {
	std::cout << "? " << x << " " << y << std::endl << std::flush;
	std::string s; std::cin >> s;
	if (s == "-202") {
		exit(0);
	}
	return s[0];
}


void report(std::vector<int> minPos, std::vector<int> maxPos) {
	std::cout << "!" << std::endl;
	std::cout << minPos.size();
	for (size_t i = 0; i < minPos.size(); i++)
		std::cout << " " << minPos[i];
	std::cout << std::endl << maxPos.size();
	for (size_t i = 0; i < maxPos.size(); i++)
		std::cout << " " << maxPos[i];
	std::cout << std::endl << std::flush;
}


int main() {
	int T; std::cin >> T;
	for (int test_case_id = 1; test_case_id <= T; test_case_id++) {
		int N;
		std::cin >> N;
		if (N < 0) {
			/* this means your code is already wrong, exit immediately */
			return 0;
		}


		std::vector<int> minPos, maxPos;


		maxPos.push_back(1);
		minPos.push_back(1);

		for (int i = 2; i < N; i += 2) {
			switch (weigh(i, i + 1)) {
			case '<':
				switch (weigh(maxPos[0], i + 1)) {
				case '<':
					maxPos.clear();
					maxPos.push_back(i + 1);
					break;
				case '>':
					break;
				case '=':
					maxPos.push_back(i + 1);
					break;
				}

				switch (weigh(minPos[0], i)) {
				case '>':
					minPos.clear();
					minPos.push_back(i);
					break;
				case '<':
					break;
				case '=':
					minPos.push_back(i);
					break;
				}
				break;
			case '>':
				switch (weigh(maxPos[0], i)) {
				case '<':
					maxPos.clear();
					maxPos.push_back(i);
					break;
				case '>':
					break;
				case '=':
					maxPos.push_back(i);
					break;
				}
				switch (weigh(minPos[0], i + 1)) {
				case '>':
					minPos.clear();
					minPos.push_back(i + 1);
					break;
				case '<':
					break;
				case '=':
					minPos.push_back(i + 1);
					break;
				}
				break;

			case '=':
				switch (weigh(maxPos[0], i)) {
				case '<':
					maxPos.clear();
					maxPos.push_back(i);
					maxPos.push_back(i + 1);
					break;
				case '>':
					break;
				case '=':
					maxPos.push_back(i);
					maxPos.push_back(i + 1);
					break;
				}
				switch (weigh(minPos[0], i)) {
				case '>':
					minPos.clear();
					minPos.push_back(i);
					minPos.push_back(i + 1);
					break;
				case '<':
					break;
				case '=':
					minPos.push_back(i);
					minPos.push_back(i + 1);
					break;
				}

				break;
			}
		}

		if (N % 2 == 0) {
			switch (weigh(maxPos[0], N)) {
			case '<':
				maxPos.clear();
				maxPos.push_back(N);
				break;
			case '>':
				break;
			case '=':
				maxPos.push_back(N);
				break;
			}
			switch (weigh(minPos[0], N)) {
			case '>':
				minPos.clear();
				minPos.push_back(N);
				break;
			case '<':
				break;
			case '=':
				minPos.push_back(N);
				break;
			}
		}



		report(minPos, maxPos);


	}
	return 0;
}