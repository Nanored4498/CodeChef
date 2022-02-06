#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

int main() {
	int T;
	cin >> T;
	while(T--) {
		int N;
		cin >> N;
		vector<ll> A(N);
		for(ll &x : A) cin >> x;
		ll ans = 0;
		for(int i = 0; i < N-2; ++i) {
			int j = i+1;
			for(int k = i+2; k < N; ++k) {
				while(j+1 < k && (A[j]-A[i]) * (A[k]-A[j]) <= (A[j+1]-A[i]) * (A[k]-A[j+1])) ++j;
				ans += (A[j]-A[i]) * (A[k]-A[j]);
			}
		}
		cout << ans << '\n';
	}
	return 0;
}