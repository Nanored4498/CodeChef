#include <iostream>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T, N;
	cin >> T;
	while(T--) {
		cin >> N;
		int v = 1;
		for(int i = 0; i < N; ++i) {
			bool ok = N&1 || i&1;
			if(ok) cout << v++; 
			else cout << v+N-1;
			for(int j = 1; j < N; ++j) cout << " " << v++; 
			if(!ok) ++v;
			cout << "\n";
		}
	}

	return 0;
}
