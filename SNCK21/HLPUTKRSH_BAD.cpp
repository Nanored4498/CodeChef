#include <iostream>
#include <vector>
#include <algorithm>

#include "../CPHeaders/aho_corasick.h"

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while(T--) {
		int N;
		cin >> N;
		vector<string> S(N);
		for(string &s : S) cin >> s;
		sort(S.begin(), S.end());
		S.resize(unique(S.begin(), S.end()) - S.begin());
		sort(S.begin(), S.end(), [](const string &a, const string &b) { return a.size() < b.size(); });
		N = S.size();
		int ans = 0;
		AhoCorasick ac(S);
		vector<pair<int, int>> dp(ac.ends.size(), {-1, -1});
		vector<vector<int>> st(N);
		for(int i = 0; i < N; ++i) st[i] = ac.states(S[i]);
		for(int i0 = 0, j = 0; i0 < N; ++j) {
			for(int i = i0; i < N; ++i) {
				const int s = st[i][j];
				if(dp[s].first != -1) continue;
				dp[s].first = j == 0 ? 0 : dp[st[i][j-1]].first;
				dp[s].second = j == 0 ? 0 : dp[st[i][j-1]].second;
				const int r = ac.back[s];
				if(r <= 0) continue;
				const int l = dp[r].first;
				dp[s].first = max(dp[s].first, l);
				dp[s].second = max({dp[s].second, dp[r].second, l + dp[st[i][j-l]].first});
			}
			while(i0 < N && j+1 == st[i0].size()) {
				// cerr << "A " << i0 << ' ' << j+1 << ' ' << dp[st[i0][j]].second << endl;
				ans += j+1 - dp[st[i0][j]].second;
				dp[st[i0][j]] = { j+1, j+1 };
				++ i0;
			}
		}
		cout << ans << '\n';
	}
	return 0;
}