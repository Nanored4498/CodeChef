#include <iostream>

using namespace std;

int main() {
	int T;
	cin >> T;
	while(T--) {
		int N;
		cin >> N;
		if(N == 4) {
			cout << "...Q\n....\n.Q..\n....\n";
			continue;
		}
		string s(N+1, '.');
		s[N] = '\n';
		cout << s;
		for(int i = 1; i < N-1; ++i) {
			int j = N&1 ? i : (2*i==N ? i-1 : (2*i+2==N ? i+1 : i));
			s[j] = 'Q';
			cout << s;
			s[j] = '.';
		}
		cout << s;
	}
	return 0;
}