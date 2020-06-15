#include <iostream>
#include <vector>
#include <set>
#include <time.h>

using namespace std;
typedef pair<int, int> pii;

const bool DEBUG = false;
bool lied = false;
int X=1;

int Q = 0;
int query(int y) {
	++ Q;
	cout << y << endl;
	char ans;
	if(DEBUG) {
		if(y == X) ans = 'E';
		else {
			if(lied) lied = false;
			else lied = rand()%2;
			if(y > X) ans = lied ? 'G' : 'L';
			if(y < X) ans = lied ? 'L' : 'G';
		}
		cerr << ans << " " << lied << endl;
	} else cin >> ans;
	return ans;
}

int new_val(int i, set<pii> &s) {
	for(auto it = s.begin(); it != s.end(); ++it) {
		if(i >= it->first) i += it->second - it->first + 1;
		else break;
	}
	return i;
}

int found() {
	if(DEBUG) cerr << Q << endl;
	return 0;
}

int main() {
	int N;
	if(DEBUG) {
		srand(time(0));
		N = int(1e9);
		X = (rand() % N) + 1;
	} else cin >> N;

	int size = N;
	set<pii> nopes;
	while(true) {
		if(DEBUG) {
			for(auto it = nopes.begin(); it != nopes.end(); ++it)
				cerr << "(" << it->first << ", " << it->second << ") ";
			cerr << "  -- " << X << endl;
		}
		int m = (1+size)/2;
		int new_m = new_val(m, nopes);
		char ans = query(new_m);
		if(ans == 'E') return found();
		if(ans == 'L') {
			if(m < size) {
				int m2 = m+max(1., .185*size);
				int new_m2 = new_val(m2, nopes);
				ans = query(new_m2);
				if(ans == 'E') return found();
				if(ans == 'L') {
					nopes.emplace(new_m2, new_val(size, nopes));
					nopes.emplace(new_m, new_m);
					size -= size-m2+2;
				} else {
					int m3 = m/2;
					int new_m3 = new_val(m3, nopes);
					ans = query(new_m3);
					if(ans == 'E') return found();
					if(ans == 'L') {
						nopes.emplace(new_m3, new_m2);
						size -= m2-m3+1;
					} else {
						nopes.emplace(new_val(1, nopes), new_m3);
						nopes.emplace(new_m, new_m2);
						size -= m3+m2-m+1;
					}
				}
			} else {
				nopes.emplace(new_m, new_m);
				-- size;
			}
		} else {
			if(m > 1) {
				int m2 = m-max(1., .185*size);
				int new_m2 = new_val(m2, nopes);
				ans = query(new_m2);
				if(ans == 'E') return found();
				if(ans == 'L') {
					int m3 = (m+1+size)/2;
					int new_m3 = new_val(m3, nopes);
					ans = query(new_m3);
					if(ans == 'E') return found();
					if(ans == 'L') {
						nopes.emplace(new_m3, new_val(size, nopes));
						nopes.emplace(new_m2, new_m);
						size -= size-m3+m-m2+2;
					} else {
						nopes.emplace(new_m2, new_m3);
						size -= m3-m2+1;
					}
				} else {
					nopes.emplace(new_val(1, nopes), new_m2);
					nopes.emplace(new_m, new_m);
					size -= m2+1;
				}
			} else {
				nopes.emplace(new_m, new_m);
				-- size;
			}
		}
		for(auto it = nopes.begin(); it != nopes.end(); ++it) {
			while(true) {
				auto it2 = ++it; --it;
				if(it2 != nopes.end() && it2->first <= it->second+1) {
					int start = it->first;
					int end = max(it->second, it2->second);
					it2 = nopes.erase(it);
					nopes.erase(it2);
					it = nopes.emplace(start, end).first;
				} else break;
			}
		}
	}

}
