#include <iostream>

using namespace std;
typedef long long ll;
const ll MAX = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while(T--) {
		ll x[3], y[3], a[3], m[3], n=3, nu=0;
		for(int i = 0; i < 3; ++i) cin >> x[i];
		for(int i = 0; i < 3; ++i) cin >> y[i];
		for(int i = 0; i < 3; ++i) {
			a[i] = y[i]-x[i];
			if(a[i] == 0) { --n; nu = i; }
			if(x[i] != 0 && (y[i]%x[i]) == 0) m[i] = y[i] / x[i];
			else m[i] = MAX+1;
		}
		if(n == 0) cout << "0\n";
		else if(n == 1) cout << "1\n";
		else if(n == 2) {
			int i = (nu+1)%3, j = (nu+2)%3;
			if(a[i] == a[j]) cout << "1\n";
			else if(m[i] <= MAX && m[i] == m[j]) cout << "1\n";
			else cout << "2\n";
		} else {
			if(a[0] == a[1] && a[1] == a[2]) cout << "1\n";
			else if(m[0] <= MAX && m[0] == m[1] && m[1] == m[2]) cout << "1\n";
			else if(a[0] == a[1] || a[0] == a[2] || a[1] == a[2]) cout << "2\n";
			else if(m[0] <= MAX && m[0] == m[1]) cout << "2\n";
			else if(m[0] <= MAX && m[0] == m[2]) cout << "2\n";
			else if(m[1] <= MAX && m[1] == m[2]) cout << "2\n";
			else {
				bool ok = false;
				for(int i = 0; i < 3; ++i) {
					int j = (i+1)%3, k = (i+2)%3;
					if(a[i] == a[j]+a[k]) ok = true;
					if(m[i] <= MAX && m[j] <= MAX && m[k] <= MAX && m[i] == m[j]*m[k]) ok = true;
					if(m[k] <= MAX && y[i] == (x[i]+a[j])*m[k]) ok = true;
					if(m[k] <= MAX && y[i] == m[k]*x[i]+a[j]) ok = true;
					if(m[j] <= MAX && y[i] == (x[i]+a[k])*m[j]) ok = true;
					if(m[j] <= MAX && y[i] == m[j]*x[i]+a[k]) ok = true;
					if((x[j]+a[i]) != 0 && (y[j] % (x[j]+a[i])) == 0 && y[k]*(x[j]+a[i]) == (x[k]+a[i])*y[j]) ok = true;
					if(x[j] != 0 && ((y[j]-a[i]) % x[j]) == 0 && (y[k]-a[i])*x[j] == x[k]*(y[j]-a[i])) ok = true;
					if(m[i] <= MAX) {
						if(y[j]-m[i]*x[j] == y[k]-m[i]*x[k]) ok = true;
						if(m[i] != 0 && (y[j]%m[i]) == 0 && y[j] - m[i]*x[j] == y[k] - m[i]*x[k]) ok = true;
					}
				}
				if(!ok && x[0] != x[1] && ((y[1]-y[0]) % abs(x[1]-x[0])) == 0) {
					ll m0 = (y[1]-y[0]) / (x[1]-x[0]);
					if(y[0]-m0*x[0] == y[2]-m0*x[2]) ok = true;
				}
				if(!ok && y[0] != y[1] && ((y[1]*x[0]-y[0]*x[1]) % abs(y[0]-y[1])) == 0) {
					ll a0 = (y[1]*x[0]-y[0]*x[1]) / (y[0]-y[1]);
					if(x[0]+a0 != 0 && y[0] % (x[0]+a0) == 0 && y[0]*(x[2]+a0) == y[2]*(x[0]+a0)) ok = true;
				}
				if(ok) cout << "2\n";
				else cout << "3\n";
			}
		}
	}

	return 0;
}
