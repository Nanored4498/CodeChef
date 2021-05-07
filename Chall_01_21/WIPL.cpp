#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef vector<int> vi;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while(T--) {
		int N, K;
		cin >> N >> K;
		vi H(N);
		for(int i = 0; i < N; ++i) cin >> H[i];
		sort(H.rbegin(), H.rend());
		vector<bool> dp(K, false);
		int tot = 0, ans = -1;
		dp[0] = true;
		for(int i = 0; i < N; ++i) {
			tot += H[i];
			for(int j = K-1; j >= 0; --j) if(dp[j]) {
				int k = j + H[i];
				if(k < K) dp[k] = true;
				else if(tot-k >= K) {
					ans = i+1;
					break;
				}
			}
			if(ans >= 0) break;
		}
		cout << ans << "\n";
	}

	return 0;
}