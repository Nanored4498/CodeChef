#include <iostream>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while(T--) {
		int d=0;
		for(int i = 0; i < 5; ++i) {
			int R;
			cin >> R;
			if(R == 1) ++d;
			else if(R == 2) --d;
		}
		cout << (d == 0 ? "DRAW" : (d > 0 ? "INDIA" : "ENGLAND")) << '\n';
	}

	return 0;
}