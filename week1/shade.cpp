#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {

	int N;
	long long int x1, x2, y1, y2;
	long long int dy, dx;
	unsigned long long int sz = 0;

	typedef pair<long long int, pair<char, pair<long long int, long long int> > >  Subrect;
	typedef pair<long long int, pair<long long i¤¼`nt, pair<long long int, long long int> > > Rect;

	set<Rect> rects;
	vector<Subrect> xpt; // x, dir ,lowy, upy
	set<Subrect> xpt_overlap;

	cin >> N;

	for (int i = 0; i < N; i++) {
		scanf("%lld %lld %lld %lld", &x1, &x2, &y1, &y2);
		xpt.push_back(make_pair(x1, make_pair(1, make_pair(y1, y2))));
		xpt.push_back(make_pair(x2, make_pair(-1, make_pair(y1, y2))));
		rects.insert(make_pair(x1, make_pair(x2, make_pair(y1, y2))));
	}


	for (int i = 0; i < 2 * N; i++) {
		for (set<Rect>::iterator jt = rects.begin(); jt != rects.end(); jt++) {
			if (xpt[i].first > (*jt).first && xpt[i].first < (*jt).second.first)
				xpt.push_back(make_pair(xpt[i].first, make_pair(1, make_pair((*jt).second.second.first, (*jt).second.second.second))));
		}

	}

	sort(xpt.begin(), xpt.end());

	vector<Subrect>::iterator it = xpt.begin();
	while (it != xpt.end()) {
		x1 = (*it).first;
		long long int lowy, upy;
		char dir;
		dir = (*it).second.first;
		lowy = (*it).second.second.first;
		upy = (*it).second.second.second;
		while (++it != xpt.end() && x1 == (*it).first && dir == (*it).second.first) {
			if (upy > (*it).second.second.first && upy < (*it).second.second.second)
				upy = (*it).second.second.second;

			if (x1 != (*it).first || upy <= (*it).second.second.first) {
				break;
			}

		}
		xpt_overlap.insert(make_pair(x1, make_pair(dir, make_pair(lowy, upy))));
	}


	set<Subrect>::iterator jt = xpt_overlap.end();
	long long int xmax = (*(--jt)).first;

	for (set<Subrect>::iterator it = xpt_overlap.begin(); it != xpt_overlap.end(); it++) {
		dy = (*it).second.second.second - (*it).second.second.first;
		if ((*it).first != xmax && (*it).second.first == 1) {
			while ((*it).first == (*(++it)).first) {
				dy += (*it).second.second.second - (*it).second.second.first;
			}
			dx = (*it).first;
			dx -= (*(--it)).first;
			sz += dx * dy;
		}
	}

	printf("%lld", sz);

	return 0;
}