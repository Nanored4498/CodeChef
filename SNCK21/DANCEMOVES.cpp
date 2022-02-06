#include <iostream>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while(T--) {
		int X, Y;
		cin >> X >> Y;
		if(Y >= X) {
			Y -= X;
			cout << 2*(Y&1) + (Y>>1) << '\n';
		} else {
			cout << X-Y << '\n';
		}
	}

	return 0;
}