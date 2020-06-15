#include <iostream>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while(T--) {
		ll TS;
		cin >> TS;
		while(!(TS&1)) TS >>= 1;
		cout << (TS >> 1) << "\n";
	}

	return 0;
}
