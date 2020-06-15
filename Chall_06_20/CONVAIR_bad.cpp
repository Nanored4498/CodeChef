#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T, N, M;
	cin >> T;
	while(T--) {
		cin >> N >> M;
		vi d(N+1, 0), order(N);
		for(int i = 0; i < N; ++i) order[i] = i+1;
		for(int i = 0; i < M; ++i) {
			int a, b;
			cin >> a >> b;
			++ d[a];
			++ d[b];
		}
		int ans = 0;
		sort(order.begin(), order.end(), [&](int i, int j) { return d[i] < d[j]; });
		vector<pii> edges;
		vector<bool> conected(N+1, false);
		int j = N-1;
		conected[j] = true;
		for(int i = 0; i < N; ++i) {
			while(!conected[i] || d[order[i]]) {
				while(i < j && d[order[j]] <= d[order[N-1]] && d[order[j-1]] > d[order[N-1]]) --j;
				if(i == j || d[order[j]] <= d[order[N-1]]) j = N-1;
				if(!d[order[i]]) {
					++ d[order[i]];
					++ ans;
				}
				if(!d[order[j]]) {
					++ d[order[j]];
					++ ans;
				}
				edges.emplace_back(order[i], order[j]);
				-- d[order[i]];
				-- d[order[j]];
				if(conected[i]) conected[j] = true;
				conected[i] = true;
			}
		}
		cout << ans << " " << edges.size() << "\n";
		for(const pii &e : edges) cout << e.first << " " << e.second << "\n";
		cerr << "\n";
	}

	return 0;
}
