#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while(T--) {
		int N;
		cin >> N;
		vector<pii> X;
		vector<pii> M(N, {0, 0});
		for(int i = 0; i < N; ++i) {
			int m;
			cin >> m;
			for(int j = 0; j < m; ++j) {
				int x;
				cin >> x;
				if(x < 0) ++ M[i].first;
				else ++ M[i].second;
				X.emplace_back(x, i);
			}
		}
		sort(X.begin(), X.end(), [](const pii &a, const pii &b) {
			return abs(a.first) < abs(b.first);
		});
		int i = 0;
		ll ans = 0;
		while(i < X.size()) {
			int j = i+1;
			while(j < X.size() && abs(X[i].first) == abs(X[j].first)) ++j;
			for(int k = i; k < j; ++k)
				if(X[k].first < 0) -- M[X[k].second].first;
				else -- M[X[k].second].second;
			if(j > i+1) ++ans;
			else X[i].first *= -1;
			for(; i < j; ++i) {
				if(X[i].first < 0) ans += M[X[i].second].first;
				else ans += M[X[i].second].second;
			}
		}
		cout << ans << "\n";
	}

	return 0;
}