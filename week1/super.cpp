#include <iostream>
#include <set>
using namespace std;
int main() {
	long long int n, a, b;
	multiset<long long int> spq;

	cin >> n;
	for (int i = 0; i<n; i++) {
		cin >> a >> b;

		if (a == 1)
			spq.insert(b);

		else if (a == 2 && !spq.empty()) {
			if (b == 1)
				spq.erase(--spq.end());
			else
				spq.erase(spq.begin());
		}

		else if (a == 3) {
			if (spq.empty())
				printf("EMPTY ");
			else if (b == 1)
				printf("%lld ", *(--spq.end()));
			else
				printf("%lld ", *spq.begin());
		}

	}
	return 0;
}