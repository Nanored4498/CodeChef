#include <iostream>
#include <vector>

using namespace std;
const int MOD = 998244353;
const int MAX = 2e5+5;
#define LSB(i) ((i)&(-(i)))

int main() {
	int N, ans = 1;
	cin >> N;
	vector<int> fen(MAX, 0);
	for(int i = 0; i < N; ++i) {
		int s;
		cin >> s;
		int add = 1;
		for(int j = s-1; j > 0; j -= LSB(j)) add = (add + fen[j]) % MOD;
		for(int j = s; j < MAX; j += LSB(j)) fen[j] = (fen[j] + add) % MOD;
		ans = (ans + add) % MOD;
	}
	cout << ans << endl;
	return 0;
}