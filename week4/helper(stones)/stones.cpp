#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

char weigh(int x, int y) {
	std::cout << "? " << x << " " << y << std::endl << std::flush;
	std::string s; std::cin >> s;
	if(s == "-202") {
		exit(0);
	}
	return s[0];
}

void report(std::vector<int> minPos, std::vector<int> maxPos) {
	std::cout << "!" << std::endl;
	std::cout << minPos.size();
	for(size_t i = 0; i < minPos.size(); i++) 
		std::cout << " " << minPos[i];
	std::cout << std::endl << maxPos.size();
	for(size_t i = 0; i < maxPos.size(); i++) 
		std::cout << " " << maxPos[i];
	std::cout << std::endl << std::flush;
}

int main() {
	int T; std::cin >> T;
	for(int test_case_id = 1; test_case_id <= T; test_case_id++) {		
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
		// Below is an example solution that requires N(N-1) weighings.
		// Don't forget to initialize all global variables.

		std::vector<int> minPos, maxPos;
		for(int i = 1; i <= N; i++) {
			int cnt_smaller = 0, cnt_larger = 0;
			for(int j = 1; j <= N; j++) {
				if(i != j) {
					switch(weigh(i, j)) {
						case '>': cnt_smaller += 1; break;
						case '<': cnt_larger += 1; break;
					}
				}
			}

			if(cnt_smaller == 0) {
				minPos.push_back(i);
			}
			if(cnt_larger == 0) {
				maxPos.push_back(i);
			}
		}

		report(minPos, maxPos);
		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */

	}
	return 0;
}