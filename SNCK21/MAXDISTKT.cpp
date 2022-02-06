#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int, int> pii;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while(T--) {
		int N;
		cin >> N;
		vector<pii> B(N);
		vector<int> A(N);
		for(int i = 0; i < N; ++i) {
			cin >> B[i].first;
			B[i].second = i;
		}
		sort(B.rbegin(), B.rend());
		int a = N+1;
		for(const auto &[b, i] : B) {
			if(a > 0) a = min(a-1, b-1);
			A[i] = a;
		}
		for(int x : A) cout << x << ' ';
		cout << '\n';
	}

	return 0;
}