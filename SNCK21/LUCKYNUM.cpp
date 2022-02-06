#include <iostream>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while(T--) {
		int A, B, C;
		cin >> A >> B >> C;
		cout << ((A == 7 || B == 7 || C == 7) ? "YES" : "NO") << '\n';
	}

	return 0;
}