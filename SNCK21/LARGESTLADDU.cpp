#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while(T--) {
		int N;
		cin >> N;
		N = 1<<N;
		vector<int> A(N);
		for(int &x : A) cin >> x;
		sort(A.begin(), A.end());
		cout << (A[0]+1 >= A.back() ? "YES" : "NO") << '\n';
	}
	return 0;
}