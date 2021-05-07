#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef vector<ll> vl;
const int M = 1e5+7;
const ll MOD = 998244353;

vl SP(M, 0), S2P(M, 0), S2Po(M, 0);
vl fac(M, 1), ifac(M, 1);

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

inline ll bin(int i, int n) {
	return (((fac[n] * ifac[i]) % MOD) * ifac[n-i]) % MOD;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	for(int i = 1; i < M; ++i) {
		fac[i] = (fac[i-1]*i) % MOD;
		ifac[i] = inv(fac[i]);
	}
	for(int i = 3; i < M; ++i) {
		if(i&1) {
			if(SP[i] == 0) {
				for(int j = i; j < M; j += i)
					SP[j] = i;
			}
			SP[i] = SP[i/SP[i]] + 1;
			S2P[i] = (S2P[i-1] + SP[i]) % MOD;
			S2Po[i] = (S2Po[i-1] + SP[i]) % MOD;
		} else {
			SP[i] = SP[i>>1];
			S2P[i] = (S2P[i-1] + SP[i]) % MOD;
			S2Po[i] = S2Po[i-1];
		}
	}

	int T;
	cin >> T;
	while(T--) {
		int L, R, A, B;
		cin >> L >> R >> A >> B;
		int N = R-L+1;
		ll ans = 0;
		if(A <= N) {
			B = min(B, N);
			ll K = (S2P[R] + MOD - S2P[L-1]) % MOD;
			ll Ko = (S2Po[R] + MOD - S2Po[L-1]) % MOD;
			int No = N / 2;
			if((L&1) && (R&1)) ++ No;
			int N2 = N / 4;
			for(int i = L+4*N2; i <= R; ++i) if(i%4==2) ++N2;
			for(int i = A; i <= B; ++i) {
				ans = (ans + 2*K * bin(i-1, N-1)) % MOD;
				ans = (ans + 3 * bin(i, N)) % MOD;
				if(i <= No) {
					ans = (ans + Ko * (MOD - bin(i-1, No-1))) % MOD;
					ans = (ans + 2 * (MOD - bin(i, No))) % MOD;
				}
				if(i-1 <= No) {
					ans = (ans + N2 * (MOD - bin(i-1, No))) % MOD;
				}
			}
		}
		cout << ans << "\n";
	}

	return 0;
}