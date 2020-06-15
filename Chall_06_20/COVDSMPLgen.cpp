#include <iostream>
#include <vector>
#include <time.h>

using namespace std;
typedef long long ll;
typedef vector<int> vi;

int fail(string msg) {
	cout << -1 << endl;
	cerr << "[GEN] " <<  msg << endl;
	return 0;
}

int main() {

	int T = 40;
	int N = 60;
	int Q = 5*N*N;
	int PS[4] = {15, 10, 5, 2};
	int SS = 0;
	
	cout << T << endl;
	srand(424269);
	// srand(time(0));
	while(T--) {
		cout << N << " " << PS[T/10] << endl;
		vector<vi> A(N+1, vi(N+1, 0));
		for(int i = 1; i <= N; ++i)
			for(int j = 1; j <= N; ++j)
				if(rand()%100 < PS[T/10])
					A[i][j] = 1;
		int q = 0, score=0;
		bool ok = false;
		while(!ok) {
			int t;
			cin >> t;
			if(t == 1) {
				++ q;
				if(q > Q) return fail("Too much queries");
				int r1, c1, r2, c2;
				cin >> r1 >> c1 >> r2 >> c2;
				if(r1 < 1 || r1 > r2 || r2 > N) return fail("Bad row indices");
				if(c1 < 1 || c1 > c2 || c2 > N) return fail("Bad col indices");
				int ans = 0;
				for(int i = r1; i <= r2; ++i)
					for(int j = c1; j <= c2; ++j)
						ans += A[i][j];
				int a=r2-r1+1, b=c2-c1+1;
				score += (ans + (2*N-a)*(2*N-b)) / (1 + ans);
				cout << ans << endl;
			} else if(t == 2) {
				int s;
				ok = true;
				for(int i = 1; i <= N; ++i) {
					for(int j = 1; j <= N; ++j) {
						int a;
						cin >> a;
						if(a != A[i][j]) ok = false;
						// cerr << a << " ";
					}
					// cerr << "  |  ";
					// for(int j = 1; j <= N; ++j) cerr << " " << A[i][j];
					// cerr << endl;
				}
				if(!ok) return fail("Bad answer");
				else {
					cout << 1 << endl;
					cerr << "[GEN] (P: " << PS[T/10] << ")  Good answer!!! Score: " << score << " (" << q <<  ") " << endl;
					SS += score;
				}
			} else return fail("Bad message type");
		}
	}
	cerr << SS << endl;

	return 0;
}
