#include <cstdio>
#include <vector>
#include <cstdlib>
#include <utility>

using namespace std;

int pack(std::vector<int> &M) {
	printf("? %d", (int)M.size());
	for (int &x : M) printf(" %d", x);
	puts("");
	fflush(stdout);
	int ret; scanf("%d", &ret);
	if (ret == -202) exit(0);
	return ret;
}

void report(std::vector<int> &M) {
	printf("!");
	for (int &x : M) printf(" %d", x);
	puts("");
	fflush(stdout);
}

int findTeok(vector<vector<int> > & teok, int x, int start, int end) {

	if (start == end)
		return start;

	int mid = (start + end) / 2;

	vector<int> hap(1, x);

	for (int i = start; i <= mid; i++) {
		for (int j = 0; j < teok[i].size(); j++) {
			hap.push_back(teok[i][j]);
		}
	}

	if (pack(hap) == (mid - start + 1))
		return findTeok(teok, x, start, mid);

	else
		return findTeok(teok, x, mid + 1, end);

}

pair<int, int> findTwoTeok(vector<vector<int> > & teok, int x, int start, int end) {

	if (end - start == 1)
		return make_pair(start, end);

	int mid = (start + end) / 2;

	vector<int> hap(1, x);
	vector<int> hap2(1, x);

	for (int i = start; i <= mid; i++) {
		for (int j = 0; j < teok[i].size(); j++) {
			hap.push_back(teok[i][j]);
		}
	}

	int t = pack(hap);

	if (t == (mid - start))
		return findTwoTeok(teok, x, start, mid);


	for (int i = mid + 1; i <= end; i++) {
		for (int j = 0; j < teok[i].size(); j++) {
			hap2.push_back(teok[i][j]);
		}
	}
	int t2 = pack(hap2);

	if (t2 == (end - mid - 1))
		return findTwoTeok(teok, x, mid + 1, end);

	else
		return make_pair(findTeok(teok, x, start, mid), findTeok(teok, x, mid + 1, end));


}

int main() {
	int N; scanf("%d", &N);
	std::vector<int> chap(N), ans(N), sel;
	vector<int> debug(1, N);

	// task 3
	int now, before = 0;
	vector<vector<int> > teok;

	for (int i = 1; i <= N; i++)
		chap[i - 1] = i;

	for (int i = 0; i < N; i++) {
		int x = chap[i];
		sel.push_back(x);

		now = pack(sel);

		if (now > before) {
			teok.push_back(vector<int>(1, x));
		}

		if (now == before) {

			int idx = findTeok(teok, x, 0, teok.size() - 1);

			vector<int> * hap = &teok[idx];
			vector<int> add(1, x);

			if (hap->size() == 1) {
				hap->push_back(x);
			}

			else {
				add.push_back(hap->back());

				if (pack(add) == 1) {
					hap->push_back(x);
				}

				else
					hap->insert(hap->begin(), x);

			}
		}

		if (now < before) {

			pair<int, int> idx = findTwoTeok(teok, x, 0, teok.size() - 1);

			vector<int> hap1 = teok[idx.first];
			vector<int> hap2 = teok[idx.second];
			vector<int> add(1, x);

			int x1 = hap1.front();
			if (hap1.size() > 1)
				int x2 = hap1.back();

			int y1 = hap2.front();
			if (hap2.size() > 1)
				int y2 = hap1.back();


			add.push_back(x1);
			if (pack(add) == 1) {
				add.push_back(y1);
				if (pack(add) == 1) {

					add.clear();
					for (int i = hap1.size() - 1; i >= 0; i--) {
						add.push_back(hap1[i]);
					}
					add.push_back(x);
					for (int i = 0; i < hap2.size(); i++)
						add.push_back(hap2[i]);

				}
				else {

					add.clear();
					for (int i = hap1.size() - 1; i >= 0; i--) {
						add.push_back(hap1[i]);
					}
					add.push_back(x);
					for (int i = hap2.size() - 1; i >= 0; i--) {
						add.push_back(hap2[i]);
					}
				}
			}
			else {
				add.pop_back();
				add.push_back(y1);
				if (pack(add) == 1) {

					add.clear();
					for (int i = 0; i < hap1.size(); i++)
						add.push_back(hap1[i]);
					add.push_back(x);
					for (int i = 0; i < hap2.size(); i++)
						add.push_back(hap2[i]);

				}
				else {

					add.clear();
					for (int i = 0; i < hap1.size(); i++)
						add.push_back(hap1[i]);
					add.push_back(x);
					for (int i = hap2.size() - 1; i >= 0; i--) {
						add.push_back(hap2[i]);
					}

				}
			}

			if (idx.first > idx.second) {
				teok.erase(teok.begin() + idx.first);
				teok.erase(teok.begin() + idx.second);
			}
			else {
				teok.erase(teok.begin() + idx.second);
				teok.erase(teok.begin() + idx.first);
			}

			teok.push_back(add);


		}
		before = now;
	}

	report(teok[0]);

	return 0;
}