#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<pll> vll;

int turn_left(const pll &a, const pll &b, const pll &c) {
	ll d = -(b.second - a.second)*(c.first - b.first) + (b.first - a.first)*(c.second - b.second);
	if(d > 0) return 1;
	if(d == 0) return 0;
	return -1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T, N, Q;
	cin >> T;
	while(T--) {
		cin >> N >> Q;
		vll ps(N);
		vector<vector<int>> top, bot;
		vector<int> available(N), avb, count(N);
		for(int i = 0; i < N; ++i) {
			cin >> ps[i].first >> ps[i].second;
			available[i] = i;
		}
		sort(ps.begin(), ps.end());
		while(available.size() >= 3) {
			top.emplace_back();
			bot.emplace_back();
			vector<int> &to = top.back(), &bo = bot.back();
			for(int i : available) {
				count[i] = 0;
				while(to.size() >= 2 && turn_left(ps[to[to.size()-2]], ps[to.back()], ps[i]) > 0) {
					++ count[to.back()];
					to.pop_back();
				}
				to.push_back(i);
				while(bo.size() >= 2 && turn_left(ps[bo[bo.size()-2]], ps[bo.back()], ps[i]) < 0) {
					++ count[bo.back()];
					bo.pop_back();
				}
				bo.push_back(i);
			}
			avb.clear();
			for(int i : available) if(count[i] == 2) avb.push_back(i);
			swap(available, avb);
			// for(const pll &p : top) cerr << "(" << p.first << ", " << p.second << ") ";
			// cerr << endl;
			// for(const pll &p : bot) cerr << "(" << p.first << ", " << p.second << ") ";
			// cerr << endl;
		}
		pll C;
		while(Q--) {
			cin >> C.first >> C.second;
			int ans = 0;
			for(int l = 0; l < top.size(); ++l) {
				bool ok = true;
				vector<int> &to = top[l], &bo = bot[l];
				for(int i = 1; i < to.size(); ++i) if(turn_left(ps[to[i-1]], ps[to[i]], C) >= 0) ok = false;
				for(int i = 1; i < bo.size(); ++i) if(turn_left(ps[bo[i-1]], ps[bo[i]], C) <= 0) ok = false;
				if(ok) ++ans;
				else break;
			}
			cout << ans << "\n";
		}
	}

	return 0;
}
