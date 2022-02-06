#include <iostream>
#include <vector>

using namespace std;

int main() {
	int T;
	cin >> T;
	while(T--) {
		string s;
		cin >> s;
		int count = 0, n = s.size();
		for(char c : s) if(c == '1') ++ count;
		if(n%2 == 0 && count == n) {
			cout << "NO\n";
			continue;
		}
		cout << "YES\n";
		if(count == 0) {
			cout << "0\n";
			continue;
		}
		bool one = count&1;
		bool one0 = one;
		vector<int> ans;
		if(!one && s.substr(0, 3) == "111") {
			int i = 0;
			while(s[++i] == '1');
			if(i&1) {
				ans.push_back(i-2);
				ans.push_back(i-3);
				s[i-1] = s[i-2] = '0';
				s[i] = '1';
				i -= 3;
			} 
			for(int j = 0; j <= i; ++j) s[j] = '0';
			while(i >= 2) {
				ans.push_back(i-2);
				ans.push_back(i);
				i -= 2;
			}
		}
		for(int i = 0; i < n; ++i) if(s[i] == '1') {
			if(one) {
				ans.push_back(i);
				s[i] = '0';
				one = false;
			} else if(i+2 < n) {
				if(s.substr(i, 3) == "111") {
					ans.push_back(i-1);
					ans.push_back(i-1);
					for(int j = 0; j < 2; ++j) s[i+j] = '0';
				} else {
					ans.push_back(i);
					for(int j = 0; j < 3; ++j) s[i+j] = '1'+'0'-s[i+j];
					one = true;
				}
			} else { // ... 0 1 1 -> 1 0 0 -> 0 0 0
				ans.push_back(i-1);
				ans.push_back(i-1);
				break;
			}
		}

		cout << ans.size() << '\n' << (one0 ? 2 : 1) << '\n';
		for(int i : ans) cout << i << '\n';
	}
	return 0;
}