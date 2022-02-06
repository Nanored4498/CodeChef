#include <iostream>
#include <cmath>

using namespace std;
typedef long long ll;

int main() {
	int T;
	cin >> T;
	while(T--) {
		ll K;
		cin >> K;
		int n = sqrt(2*K);
		while((n+1)*(n+2) < 2*K) ++n;
		while(n*(n+1) >= 2*K) --n;
		cout << 2*n+2 << '\n';
	}
	return 0;
}