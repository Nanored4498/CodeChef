#include <iostream>
#include <random>
#include <vector>

using namespace std;
typedef vector<int> vi;

int Ns[6] = {2, 4, 7, 100, 200, 199};
std::random_device rd;
default_random_engine re(rd());
uniform_int_distribution<int> unif(0, 1);

int main() {
	cout << "6" << endl;
	for(int N : Ns) {
		vector<vi> m(N+1, vi(N+1));
		int K = 0, Q = 4*N*N;
		for(int i = 1; i <= N; ++i)
			for(int j = 1; j <= N; ++j) {
				m[i][j] = unif(re);
				if(i > 1 && j > 1 && m[i][j] == 0 && m[i-1][j-1] == 0 && m[i-1][j] == 1 && m[i][j-1] == 1) ++K;
			}
		cout << N << " " << Q << " " << K << endl;
		int q = 0;
		while(true) {
			int t;
			cin >> t;
			if(t == 1) {
				if(++q > Q) return cout << "-1" << endl, 0;
				int i, j;
				cin >> i >> j;
				for(int k = i; k < i+2; ++k)
					for(int l = j; l < j+2; ++l)
						if(k <= N && l <= N && m[k][l] == 0 && m[k-1][l-1] == 0 && m[k-1][l] == 1 && m[k][l-1] == 1) --K;
				m[i][j] ^= 1;
				for(int k = i; k < i+2; ++k)
					for(int l = j; l < j+2; ++l)
						if(k <= N && l <= N && m[k][l] == 0 && m[k-1][l-1] == 0 && m[k-1][l] == 1 && m[k][l-1] == 1) ++K;
				cout << K << endl;
			} else if(t == 2) {
				bool bad = false;
				for(int i = 1; i <= N; ++i) {
					for(int j = 1; j <= N; ++j) cerr << m[i][j] << " ";
					cerr << "  ||   ";
					for(int j = 1; j <= N; ++j) {
						int x;
						cin >> x;
						bad |= x != m[i][j];
						cerr << x << " ";
					}
					cerr << endl;
				}
				if(bad) return cout << "-1" << endl, cerr << "BAD" << endl, 0;
				cout << "1" << endl;
				cerr << "GOOD" << endl;
				break;
			}
		}
	}

	return 0;
}