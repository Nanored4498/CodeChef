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
		int N, M;
		cin >> N >> M;
		vi A(N), B(M);
		int s = 0;
		for(int i = 0; i < N; ++i) {
			cin >> A[i];
			s += A[i];
		}
		for(int i = 0; i < M; ++i) {
			cin >> B[i];
			s -= B[i];
		}
		int ans = 0;
		sort(A.begin(), A.end());
		sort(B.rbegin(), B.rend());
		N = min(N, M);
		for(int i = 0; i < N && s <= 0; ++i) {
			int d = 2*(B[i] - A[i]);
			if(d <= 0) break;
			s += d;
			++ ans;
		}
		if(s <= 0) ans = -1;
		cout << ans << "\n";
	}

	return 0;
}