#include <iostream>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	string S;
	cin >> T;
	while(T--) {
		cin >> S;
		int ans = 0;
		for(int i = 1; i < S.size(); ++i) {
			if(S[i] != S[i-1]) {
				++ ans;
				++ i;
			}
		}
		cout << ans << "\n";
	}

	return 0;
}
