#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while(T--) {
		int N;
		cin >> N;
		vector<int> A(N);
		for(int &x : A) cin >> x;

		vector<pair<int, bool>> ma, Ma;
		{
		int i = 1;
		while(i < N)
			if(abs(A[i]-A[0]) > 1) {
				if(A[i] > A[0]) {
					ma.emplace_back(A[0], true);
					Ma.emplace_back(A[i], false);
				} else {
					ma.emplace_back(A[i], false);
					Ma.emplace_back(A[0], true);
				}
				break;
			} else ++i;
		while(++i < N) {
			if(ma.size() < Ma.size() || (ma.size() == Ma.size() && ma[0].first == A[0])) {
				if(A[i] < Ma.back().first-1) ma.emplace_back(A[i], false);
				else Ma.back().first = max(Ma.back().first, A[i]);
			} else {
				if(A[i] > ma.back().first+1) Ma.emplace_back(A[i], false);
				else ma.back().first = min(ma.back().first, A[i]);
			}
		}
		}

		if(ma.empty()) {
			for(int i = 2; i <= N; ++i) cout << "-1 "; cout << '\n';
			for(int i = 2; i <= N; ++i) cout << "-1 "; cout << '\n';
			continue;
		}
		if(ma.size() < Ma.size() || (ma.size() == Ma.size() && ma[0].first == A[0])) Ma.back().second = true;
		else ma.back().second = true;

		sort(ma.begin(), ma.end());
		sort(Ma.rbegin(), Ma.rend());
		vector<int> m(N-1, -1), M(N-1, -1);
		for(int i = 2, add = 1; i <= N; ++i) {
			int j = (i-1-add) / 2;
			if(j < ma.size()) {
				if(ma[j].second) --add;
				m[i-2] = ma[j].first+1;
			}
		}
		for(int i = 2, add = 1; i <= N; ++i) {
			int j = (i-1-add) / 2;
			if(j < Ma.size()) {
				if(Ma[j].second) --add;
				M[i-2] = Ma[j].first-1;
				if(M[i-2] < m[i-2]) M[i-2] = m[i-2] = -1;
			}
		}
		for(int x : m) cout << x << ' '; cout << '\n';
		for(int x : M) cout << x << ' '; cout << '\n';

	}
	return 0;
}