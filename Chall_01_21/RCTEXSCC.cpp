#include <iostream>

using namespace std;
typedef long long ll;
const ll MOD = 998'244'353;

inline ll pow(ll x, ll n) {
	ll ans = 1;
	while(n > 0) {
		if(n&1) ans = (ans * x) % MOD;
		x = (x * x) % MOD;
		n >>= 1;
	}
	return ans;
}

inline ll inv(ll x) {
	return pow(x, MOD-2);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll M, N, K;
	cin >> M >> N >> K;
	if(M == 1) {
		ll ans = (N + (N-1) * (MOD - inv(K))) % MOD;
		cout << ans << "\n";
	} else {
		ll iK = inv(K);
		ll p0 = ((K-1) * iK) % MOD;
		ll q = ((K-2) * iK) % MOD;
		ll E[2] = {2, 1}, E2[2];
		while(--N) {
			E2[0] = (p0 * (E[0] + 2*p0) + iK * (E[1] + 2*p0)) % MOD;
			E2[1] = (p0 * (E[0] + q) + iK * (E[1] + p0)) % MOD;
			swap(E, E2);
		}
		ll ans = (p0 * E[0] + iK * E[1]) % MOD;
		cout << ans << "\n";
	}

	return 0;
}