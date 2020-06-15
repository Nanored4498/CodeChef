#include <iostream>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T, N;
	cin >> T;
	while(T--) {
		cin >> N;
		int a = 0, b = 0;
		string ans = "YES";
		while(N--) {
			int x;
			cin >> x;
			if(x == 5) ++a;
			else if(x == 10) {
				if(a > 0) {
					--a;
					++b;
				} else ans = "NO";
			} else {
				if(b > 0) --b;
				else if(a > 1) a -= 2; 
				else ans = "NO";
			}
		}
		cout << ans << "\n";
	}

	return 0;
}
