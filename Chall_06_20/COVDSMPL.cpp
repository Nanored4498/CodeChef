#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
#include <tuple>

using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef tuple<int, int, int> t3i;

bool fill_seg(vi& a, int N, int tot, bool row) {
	a.assign(N+1, -1);
	a[0] = 0;
	a[N] = tot;
	int i = 0, j = N;
	while(true) {
		if(a[i] == a[j] || i+1 >= j) {
			while(i < j) a[++i] = a[j];
			while(i < N && a[i] >= 0) ++i;
			if(a[i] >= 0) break;
			j = i--;
			while(a[j] < 0) ++j;
			continue;
		}
		double e = double(a[j]-a[i]) / double(j-i);
		int lc = 1e9;
		int k = (i+j)/2;
		bool up = false;
		for(int kk = (i+j)/2; kk <= (i+j+1)/2; ++kk) {
			double x0 = a[i] + (kk-i) * e;
			double x1 = a[N] - x0;
			int c0 = (N*(2*N-kk) + x0) / (1. + x0);
			int c1 = (N*(N+kk) + x1) / (1. + x1);
			if(c0 < lc) { k = kk; up = false; lc = c0; }
			if(c1 < lc) { k = kk; up = true; lc = c1; }
		}
		if(up) {
			if(row) cout << "1 " << k+1 << " 1 " << N << " " << N << endl;
			else cout << "1 1 " << k+1 << " " << N << " " << N << endl;
			int x;
			cin >> x;
			if(x == -1) return false;
			a[k] = a[N] - x;
		} else {
			if(row) cout << "1 1 1 " << k << " " << N << endl;
			else cout << "1 1 1 " << N << " " << k << endl;
			cin >> a[k];
			if(a[k] == -1) return false;
		}
		j = k;
	}
	return true;
}

double H(int x, int n) {
	if(x == 0 || x == n) return 0;
	double p = double(x) / double(n);
	return - p*log2(p) - (1-p)*log2(1-p);
}

template <typename T>
inline T subsum(const vector<vector<T>> &S, int r1, int c1, int r2, int c2) {
	return S[r2][c2]-S[r1][c2]-S[r2][c1]+S[r1][c1];
} 

pair<double, int> q_score(int i, int j, int r1, int c1, const vector<vi> &S, const vector<vector<double>> &E) {
	int N = S.size()-1, nr = E.size()-1, nc = E[0].size()-1;
	int r2 = r1+nr, c2 = c1+nc;
	pair<double, int> ans = {1e9, 0};
	double X, A, B, score;

	A = i, B = j;
	X = subsum(S, 0, 0, i, c1) + subsum(S, 0, c1, r1, j);
	X += subsum(E, 0, 0, i-r1, j-c1);
	score = ceil((2*N-A) * (2*N-B) / (1 + X));
	if(score < ans.first) ans = {score, 0};
	if(j < N) {
		A = i; B = N-j;
		X = subsum(S, 0, c2, i, N) + subsum(S, 0, j, r1, c2);
		X += subsum(E, 0, j-c1, i-r1, nc);
		score = ceil((2*N-A) * (2*N-B) / (1 + X));
		if(score < ans.first) ans = {score, 1};
	}
	if(i < N) {
		A = N-i; B = j;
		X = subsum(S, i, 0, N, c1) + subsum(S, r2, c1, N, j);
		X += subsum(E, i-r1, 0, nr, j-c1);
		score = ceil((2*N-A) * (2*N-B) / (1 + X));
		if(score < ans.first) ans = {score, 2};
	}
	if(j < N && i < N) {
		A = N-i; B = N-j;
		X = subsum(S, i, c2, N, N) + subsum(S, r2, j, N, c2);
		X += subsum(E, i-r1, j-c1, nr, nc);
		score = ceil((2*N-A) * (2*N-B) / (1 + X));
		if(score < ans.first) ans = {score, 3};
	}

	return ans;
}

bool q_send(int i, int j, int t, vector<vi> &S) {
	int ans, N = S.size()-1;
	switch(t) {
		case 0:
			cout << "1 1 1 " << i << " " << j << endl;
			cin >> ans;
			if(ans == -1) return false;
			S[i][j] = ans;
			break;
		case 1:
			cout << "1 1 " << j+1 << " " << i << " " << N << endl;
			cin >> ans;
			if(ans == -1) return false;
			S[i][j] = S[i][N]-ans;
			break;
		case 2:
			cout << "1 " << i+1 << " 1 " << N << " " << j << endl;
			cin >> ans;
			if(ans == -1) return false;
			S[i][j] = S[N][j]-ans;
			break;
		case 3:
			cout << "1 " << i+1 << " " << j+1 << " " << N << " " << N << endl;
			cin >> ans;
			if(ans == -1) return false;
			S[i][j] = ans+S[i][N]+S[N][j]-S[N][N];
			break;
	}
	return true;
}

bool f(int r1, int c1, int r2, int c2, vector<vi> &S, vector<vi> &A) {
	// cerr << "f call: " << r1 << " " << c1 << " " << r2 << " " << c2 << endl;
	int nor=0, noc=0, N=S.size()-1;
	vi row_o(r2-r1+1, 0), row_z(r2-r1+1, 0), col_o(c2-c1+1, 0), col_z(c2-c1+1, 0);
	for(int i = r1+1; i <= r2; ++i)
		for(int j = c1+1; j <= c2; ++j)
			if(A[i][j] == 0) {
				++ row_z[i-r1];
				++ col_z[j-c1];
			} else if(A[i][j] == 1) {
				++ row_o[i-r1];
				++ col_o[j-c1];
			}
	vi rs, cs;
	for(int i = r1+1; i <= r2; ++i) rs.push_back(i);
	for(int j = c1+1; j <= c2; ++j) cs.push_back(j);
	while(!rs.empty() && !cs.empty()) {
		int del = -1;
		for(int i = 0; i < rs.size(); ++i) {
			int r = rs[i];
			int s = subsum(S, r-1, c1, r, c2);
			if(row_o[r-r1] == s) {
				for(int j : cs) if(A[r][j] < 0) {
					A[r][j] = 0;
					++ col_z[j-c1];
					++ row_z[r-r1];
				}
				del = i;
				break;
			}
			if(row_z[r-r1] == c2-c1-s) {
				for(int j : cs) if(A[r][j] < 0) {
					A[r][j] = 1;
					++ col_o[j-c1];
					++ row_o[r-r1];
				}
				del = i;
				break;
			}
		}
		if(del >= 0) {
			rs[del] = rs.back();
			rs.pop_back();
			continue;
		}
		for(int j = 0; j < cs.size(); ++j) {
			int c = cs[j];
			int s = subsum(S, r1, c-1, r2, c);
			if(col_o[c-c1] == s) {
				for(int i : rs) if(A[i][c] < 0) {
					A[i][c] = 0;
					++ col_z[c-c1];
					++ row_z[i-r1];
				}
				del = j;
				break;
			}
			if(col_z[c-c1] == r2-r1-s) {
				for(int i : rs) if(A[i][c] < 0) {
					A[i][c] = 1;
					++ col_o[c-c1];
					++ row_o[i-r1];
				}
				del = j;
				break;
			}
		}
		if(del >= 0) {
			cs[del] = cs.back();
			cs.pop_back();
			continue;
		}
		break;
	}
	if(rs.empty() || cs.empty()) return true;

	// Compute entropy and expectation
	double shr=0, shc=0;
	const auto getH = [&](const t3i &t)->double {
		return get<2>(t) * H(get<1>(t), get<2>(t));
	};
	vector<t3i> is, js;
	for(int i : rs) {
		is.emplace_back(i, subsum(S, i-1, c1, i, c2)-row_o[i-r1], c2-c1-row_o[i-r1]-row_z[i-r1]);
		shr += getH(is.back());
	}
	for(int j : cs) {
		js.emplace_back(j, subsum(S, r1, j-1, r2, j)-col_o[j-c1], r2-r1-col_o[j-c1]-col_z[j-c1]);
		shc += getH(js.back());
	}
	sort(is.begin(), is.end());
	sort(js.begin(), js.end());
	vector<vector<double>> E(r2-r1+1, vector<double>(c2-c1+1, 0));
	int ii=0, jj;
	for(int i = r1+1; i <= r2; ++i) {
		jj = 0;
		for(int j = c1+1; j <= c2; ++j) {
			E[i-r1][j-c1] = E[i-r1-1][j-c1]+E[i-r1][j-c1-1]-E[i-r1-1][j-c1-1];
			if(A[i][j] >= 0) E[i-r1][j-c1] += A[i][j];
			else E[i-r1][j-c1] += .5 * (double(get<1>(is[ii])) / double(get<2>(is[ii])) + double(get<1>(js[jj])) / double(get<2>(js[jj])));
			if(jj < js.size() && get<0>(js[jj]) == j) ++jj;
		}
		if(ii < is.size() && get<0>(is[ii]) == i) ++ii;
	}

	// Find center
	double rat_min = .3;
	int bi=-1, bj=-1;
	ii = 0;
	pair<double, int> best_c = {1e12, 0};
	double hshr = 0;
	for(int i = r1+1; i < r2; ++i) {
		if(ii < is.size() && get<0>(is[ii]) == i) hshr += getH(is[ii++]);
		if(ii+1 < is.size() && hshr+getH(is[ii+1]) <= rat_min*shr) continue;
		if(ii > 1 && hshr-getH(is[ii-1]) >= (1-rat_min)*shr) break;
		jj = 0;
		double hshc = 0;
		for(int j = c1+1; j < c2; ++j) {
			if(jj < js.size() && get<0>(js[jj]) == j) hshc += getH(js[jj++]);
			if(jj+1 < js.size() && hshc+getH(js[jj+1]) <= rat_min*shc) continue;
			if(jj > 0 && hshc-getH(js[jj-1]) >= (1-rat_min)*shc) break;
			pair<double, int> tmp_c = q_score(i, j, r1, c1, S, E);
			tmp_c.first *= (r2-r1-1) + (c2-c1-1);
			tmp_c.first += q_score(r1+1, j, r1, c1, S, E).first * (i-r1-.5) + q_score(r2-1, j, r1, c1, S, E).first * (r2-i-.5);
			tmp_c.first += q_score(i, c1+1, r1, c1, S, E).first * (j-c1-.5) + q_score(i, c2-1, r1, c1, S, E).first * (c2-j-.5);
			tmp_c.first *= max(hshr, shr-hshr) + max(hshc, shc-hshc);
			if(tmp_c.first < best_c.first) { best_c = tmp_c; bi = i; bj = j; }
		}
	}
	if(!q_send(bi, bj, best_c.second, S)) return false;

	// Create U, D, L and R
	int rr = r2-r1, cc = c2-c1;
	vector<pii> L(rr+1, {0,0}), R(rr+1, {0,0}), U(cc+1, {0,0}), D(cc+1, {0,0});
	const auto upd_A = [&](int i, int j, int v)->void {
		A[i][j] = v;
		if(v == 1) {
			if(i <= bi) ++ U[j-c1].second;
			else ++ D[j-c1].second;
			if(j <= bj) ++ L[i-r1].second;
			else ++ R[i-r1].second;
		} else {
			if(i <= bi) ++ U[j-c1].first;
			else ++ D[j-c1].first;
			if(j <= bj) ++ L[i-r1].first;
			else ++ R[i-r1].first;
		}
	};
	for(int i = 1; i <= rr; ++i) {
		for(int j = 1; j <= cc; ++j) {
			if(A[r1+i][c1+j] == 1) upd_A(r1+i, c1+j, 1);
			else if(A[r1+i][c1+j] == 0) upd_A(r1+i, c1+j, 0);
		}
	}
	const auto upd_E = [&]()->void {
		for(int i = 0; i <= rr; ++i) E[i][0] = 0;
		for(int j = 0; j <= cc; ++j) E[0][j] = 0;
		for(int i = 1; i <= rr; ++i) {
			for(int j = 1; j <= cc; ++j) {
				E[i][j] = E[i-1][j]+E[i][j-1]-E[i-1][j-1];
				if(A[i+r1][j+c1] >= 0) E[i][j] += A[i+r1][j+c1];
				else {
					int nz, no, ro, unk;
					if(S[i+r1][bj] >= 0 && S[i+r1-1][bj] >= 0) {
						if(j+c1 <= bj) {
							nz = L[i].first;
							no = L[i].second;
							ro = subsum(S, r1+i-1, c1, r1+i, bj) - no;
							unk = (bj-c1)-nz-no;
						} else {
							nz = R[i].first;
							no = R[i].second;
							ro = subsum(S, r1+i-1, bj, r1+i, c2) - no;
							unk = (c2-bj)-nz-no;
						}
					} else {
						nz = L[i].first + R[i].first;
						no = L[i].second + R[i].second;
						ro = subsum(S, r1+i-1, c1, r1+i, c2) - no;
						unk = cc-nz-no;
					}
					E[i][j] += .5 * double(ro) / double(unk);
					if(S[bi][j+c1] >= 0 && S[bi][j+c1-1] >= 0) {
						if(i+r1 <= bi) {
							nz = U[j].first;
							no = U[j].second;
							ro = subsum(S, r1, c1+j-1, bi, c1+j) - no;
							unk = (bi-r1)-nz-no;
						} else {
							nz = D[j].first;
							no = D[j].second;
							ro = subsum(S, bi, c1+j-1, r2, c1+j) - no;
							unk = (r2-bi)-nz-no;
						}
					} else {
						nz = U[j].first + D[j].first;
						no = U[j].second + D[j].second;
						ro = subsum(S, r1, c1+j-1, r2, c1+j) - no;
						unk = rr-nz-no;
					}
					E[i][j] += .5 * double(ro) / double(unk);
				}
			}
		}
	};

	// Construct lines
	const auto h_row = [&](int i)->double {
		int nz = L[i].first + R[i].first; // number of zeros
		int no = L[i].second + R[i].second; // number of ones
		int ro = subsum(S, r1+i-1, c1, r1+i, c2) - no; // remaining ones
		int unk = cc-nz-no; // number of unknowns
		return unk*H(ro, unk);
	};
	const auto h_col = [&](int j)->double {
		int nz = U[j].first + D[j].first; // number of zeros
		int no = U[j].second + D[j].second; // number of ones
		int ro = subsum(S, r1, c1+j-1, r2, c1+j) - no; // remaining ones
		int unk = rr-nz-no; // number of unknowns
		return unk*H(ro, unk);
	};
	while(true) {
		int pred=0;
		pii LU={0,0}, RD={0,0}, select;
		double bh=-1, h=0;
		bool block_update = false;

		// Over the rows
		for(int i = 1; i <= rr; ++i) {
			LU.first += L[i].first;
			RD.first += R[i].first;
			LU.second += L[i].second;
			RD.second += R[i].second;
			double hi = h_row(i);
			if(hi == 0) {
				int no = L[i].second + R[i].second; // number of ones
				int ro = subsum(S, r1+i-1, c1, r1+i, c2) - no; // remaining ones
				for(int j = c1+1; j <= c2; ++j) if(A[r1+i][j] < 0) {
					upd_A(r1+i, j, ro==0 ? 0 : 1);
					block_update = true;
				}
				if(S[r1+i][bj] < 0) {
					if(i==pred+1) {
						S[r1+i][bj] = S[i+r1-1][bj] + S[i+r1][c1]-S[i+r1-1][c1] + L[i].second;
						block_update = true;
					}
				} else if(i>pred+1) {
					S[i+r1-1][bj] = S[r1+i][bj] - (S[i+r1][c1]-S[i+r1-1][c1] + L[i].second);
					block_update = true;
				}
				if(block_update) break;
			}
			if(S[r1+i][bj] < 0) {
				h += hi;
				if(h > bh) { bh = h; select = {pred, i}; }
			} else {
				if(i > pred+1
						|| LU.first+LU.second < (i-pred) * (bj-c1)
						|| RD.first+RD.second < (i-pred) * (c2-bj)) { // Some previous unknown S
					int nu = (i-pred) * (bj-c1); // size of left block
					int SU = subsum(S, r1+pred, c1, r1+i, bj);
					if(SU == LU.second || SU == nu-LU.first) { // We can replace unknowns
						int v = SU == LU.second ? 0 : 1;
						for(int i2 = pred+1; i2 <= i; ++i2) {
							for(int j = c1+1; j <= bj; ++j)
								if(A[r1+i2][j] < 0) {
									upd_A(r1+i2, j, v);
									block_update = true;
								}
							if(S[r1+i2][bj] < 0) {
								S[r1+i2][bj] = S[r1+i2-1][bj] + S[r1+i2][c1]-S[r1+i2-1][c1] + L[i2].second;
								block_update = true;
							}
						}
						if(block_update) break;
					}
					nu = (i-pred) * (c2-bj); // size of right block
					SU = subsum(S, r1+pred, bj, r1+i, c2);
					if(SU == RD.second || SU == nu-RD.first) { // We can replace unknowns
						int v = SU == RD.second ? 0 : 1;
						for(int i2 = pred+1; i2 <= i; ++i2) {
							for(int j = bj+1; j <= c2; ++j)
								if(A[r1+i2][j] < 0) {
									upd_A(r1+i2, j, v);
									block_update = true;
								}
							if(S[r1+i2][bj] < 0) {
								S[r1+i2][bj] = S[r1+i2-1][bj] + S[r1+i2][c2]-S[r1+i2-1][c2] - R[i2].second;
								block_update = true;
							}
						}
						if(block_update) break;
					}
				}
				h = 0;
				pred = i;
				LU = {0,0}, RD = {0,0};
			}
		}
		if(block_update) continue;

		// Over the cols
		h = 0;
		pred = 0;
		LU = {0,0}, RD = {0,0};
		for(int j = 1; j <= cc; ++j) {
			LU.first += U[j].first;
			RD.first += D[j].first;
			LU.second += U[j].second;
			RD.second += D[j].second;
			double hj = h_col(j);
			if(hj == 0) {
				int no = U[j].second + D[j].second; // number of ones
				int ro = subsum(S, r1, j+c1-1, r2, j+c1) - no; // remaining ones
				for(int i = r1+1; i <= r2; ++i) if(A[i][j+c1] < 0) {
					upd_A(i, c1+j, ro==0 ? 0 : 1);
					block_update = true;
				}
				if(S[bi][j+c1] < 0) {
					if(j==pred+1) {
						S[bi][j+c1] = S[bi][j+c1-1] + S[r1][j+c1]-S[r1][j+c1-1] + U[j].second;
						block_update = true;
					}
				} else if(j>pred+1) {
					S[bi][j+c1-1] = S[bi][j+c1] - (S[r1][j+c1]-S[r1][j+c1-1] + U[j].second);
					block_update = true;
				}
				if(block_update) break;
			}
			if(S[bi][c1+j] < 0) {
				h += hj;
				if(h > bh) { bh = h; select = {pred, -j}; }
			} else {
				if(j > pred+1
						|| LU.first+LU.second < (bi-r1) * (j-pred)
						|| RD.first+RD.second < (r2-bi) * (j-pred)) { // Some previous unknown S
					int nu = (bi-r1) * (j-pred); // size of upper block
					int SU = subsum(S, r1, c1+pred, bi, c1+j);
					if(SU == LU.second || SU == nu-LU.first) { // We can replace unknowns
						int v = SU == LU.second ? 0 : 1;
						for(int j2 = pred+1; j2 <= j; ++j2) {
							for(int i = r1+1; i <= bi; ++i)
								if(A[i][c1+j2] < 0) {
									upd_A(i, c1+j2, v);
									block_update = true;
								}
							if(S[bi][c1+j2] < 0) {
								S[bi][c1+j2] = S[bi][c1+j2-1] + S[r1][c1+j2]-S[r1][c1+j2-1] + U[j2].second;
								block_update = true;
							}
						}
						if(block_update) break;
					}
					nu = (r2-bi) * (j-pred); // size of lower block
					SU = subsum(S, bi, c1+pred, r2, c1+j);
					if(SU == RD.second || SU == nu-RD.first) { // We can replace unknowns
						int v = SU == RD.second ? 0 : 1;
						for(int j2 = pred+1; j2 <= j; ++j2) {
							for(int i = bi+1; i <= r2; ++i)
								if(A[i][c1+j2] < 0) {
									upd_A(i, c1+j2, v);
									block_update = true;
								}
							if(S[bi][c1+j2] < 0) {
								S[bi][c1+j2] = S[bi][c1+j2-1] + S[r2][c1+j2]-S[r2][c1+j2-1] - D[j2].second;
								block_update = true;
							}
						}
						if(block_update) break;
					}
				}
				h = 0;
				pred = j;
				LU = {0,0}, RD = {0,0};
			}
		}
		if(block_update) continue;

		if(bh < 0) break;
		upd_E();
		if(select.second > 0) { // it was over rows
			int i0 = select.first+1;
			h = h_row(i0);
			while(2*h < bh) { ++ i0; h += h_row(i0); }
			int i1 = i0--;
			while(i0 > select.first && h_row(i0) == 0) --i0;
			if(i0 == select.first) ++i0;
			while(i1 < select.second && h_row(i1+1) == 0) ++i1;
			pair<double, int> s0 = q_score(r1+i0, bj, r1, c1, S, E), s1 = q_score(r1+i1, bj, r1, c1, S, E);
			if(s0.first < s1.first) q_send(r1+i0, bj, s0.second, S);
			else q_send(r1+i1, bj, s1.second, S);
		} else { // it was over cols
			int j0 = select.first+1;
			h = h_col(j0);
			while(2*h < bh) { ++ j0; h += h_col(j0); }
			int j1 = j0--;
			while(j0 > select.first && h_col(j0) == 0) --j0;
			if(j0 == select.first) ++j0;
			while(j1 < -select.second && h_col(j1+1) == 0) ++j1;
			pair<double, int> s0 = q_score(bi, c1+j0, r1, c1, S, E), s1 = q_score(bi, c1+j0, r1, c1, S, E);
			if(s0.first < s1.first) q_send(bi, c1+j0, s0.second, S);
			else q_send(bi, c1+j0, s1.second, S);
		}
	}

	if(!f(r1, c1, bi, bj, S, A)) return false;
	if(!f(r1, bj, bi, c2, S, A)) return false;
	if(!f(bi, c1, r2, bj, S, A)) return false;
	if(!f(bi, bj, r2, c2, S, A)) return false;

	return true;
}

int main() {

	int T, N, P;
	cin >> T;
	while(T--) {
		cin >> N >> P;

		cout << "1 1 1 " << N << " " << N << endl;
		int tot;
		cin >> tot;
		if(tot == -1) return 0;

		vi rs, cs;
		if(!fill_seg(rs, N, tot, true)) return 0;
		if(!fill_seg(cs, N, tot, false)) return 0;

		// construct A
		vector<vi> S(N+1, vi(N+1, -1)), A(N+1, vi(N+1, -1));
		for(int i = 0; i <= N; ++i) {
			S[i][0] = S[0][i] = 0;
			S[i][N] = rs[i];
			S[N][i] = cs[i];
		}
		if(!f(0, 0, N, N, S, A)) return 0;

		// Answer
		cout << "2\n";
		for(int i = 1; i <= N; ++i)
			for(int j = 1; j <= N; ++j)
				cout << A[i][j] << " \n"[j==N];
		cout << flush;
		int X;
		cin >> X;
		if(X == -1) return 0;

	}

	return 0;
}
