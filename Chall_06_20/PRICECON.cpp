#include <iostream>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T, N, P, K;
	cin >> T;
	while(T--) {
		cin >> N >> K;
		int ans = 0;
		while(N --) {
			cin >> P;
			if(P > K) ans += P-K;
		}
		cout << ans << "\n";
	}

	return 0;
}
