#include <iostream>
#include <vector>

using namespace std;
typedef vector<int> vi;

int main() {
	int T;
	cin >> T;
	while(T--) {
		int N, Q, K;
		cin >> N >> Q >> K;
		vector<vi> ans(N+1, vi(N+1));
		int Z[2];
		
		for(int i = 1; i < N; i += 2) {
			for(int j = 1; j < N; j += 2) {
				Z[0] = K;
				int add = (i > 1 && j > 1 && ans[i-1][j-1] == 0 && ans[i-1][j] == 1 && ans[i][j-1] == 1) ? 2 : 1;
				ans[i][j] = 0;
				ans[i+1][j] = ans[i][j+1] = ans[i+1][j+1] = 1;
				for(int k = 1; k < 16; ++k) {
					int s = 0;
					while(!((k>>s) & 1)) ++s;
					if(s == 0) cout << "1 " << i << " " << j << endl;
					else if(s == 1) cout << "1 " << i+1 << " " << j << endl;
					else if(s == 2) cout << "1 " << i+1 << " " << j+1 << endl;
					else cout << "1 " << i << " " << j+1 << endl;
					cin >> Z[k&1];
					if((k&1) && abs(Z[1]-Z[0]) == add) {
						if(Z[0] > Z[1]) ans[i][j] = 1;
						K = Z[1];
						break;
					}
				}
				cout << "1 " << i+1 << " " << j+1 << endl;
				cin >> K;
			}
		}

		if(N&1) {
			for(int i = 1; i < N; i += 2) {
				ans[i][N-1] = ans[i+1][N] = 0;
				ans[i+1][N-1] = ans[i][N] = 1;
				cout << "1 " << i << " " << N-1 << endl;
				cin >> Z[0];
				for(int k = 1; k < 4; ++k) {
					if(k&1) cout << "1 " << i << " " << N << endl;
					else cout << "1 " << i+1 << " " << N << endl;
					cin >> Z[k&1];
					if((k&1) && abs(Z[1]-Z[0]) == 1) {
						if(Z[0] > Z[1]) ans[i][N] = 0;
						break;
					}
				}
			}

			for(int j = 1; j < N; j += 2) {
				ans[N-1][j] = ans[N][j+1] = 0;
				ans[N-1][j+1] = ans[N][j] = 1;
				cout << "1 " << N-1 << " " << j << endl;
				cin >> Z[0];
				for(int k = 1; k < 4; ++k) {
					if(k&1) cout << "1 " << N << " " << j << endl;
					else cout << "1 " << N << " " << j+1 << endl;
					cin >> Z[k&1];
					if((k&1) && abs(Z[1]-Z[0]) == 1) {
						if(Z[0] > Z[1]) ans[N][j] = 0;
						break;
					}
				}
			}
			
			cout << "1 " << N-1 << " " << N-1 << endl;
			cin >> Z[0];
			cout << "1 " << N << " " << N-1 << endl;
			cin >> Z[0];
			cout << "1 " << N-1 << " " << N << endl;
			cin >> Z[0];
			cout << "1 " << N << " " << N << endl;
			cin >> Z[1];
			ans[N-1][N-1] = 0;
			ans[N-1][N] = ans[N][N-1] = 1;
			ans[N][N] = Z[1] < Z[0];
		}

		cout << 2 << endl;
		for(int i = 1; i <= N; ++i) {
			for(int j = 1; j <= N; ++j) cout << ans[i][j] << " ";
			cout << endl;
		}
		cin >> K;
		if(K == -1) return 0;
	}

	return 0;
}