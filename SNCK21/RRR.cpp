#include <iostream>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while(T--) {
		int N, K;
		cin >> N >> K;
		cout << (N-K + (K-1)/2)*2 << '\n';
	}

	return 0;
}