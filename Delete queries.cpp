#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using INT = long long;
using pii = pair<int, int>;

const int NN = 101010, mod = 1e9 + 7;
int a[NN], num[21];
int B[21][NN];

int calc(int id, int u) {
	int ans = 0;
	for(; u; u ^= u & -u) ans += B[id][u];
	return ans;
}
void update(int id, int u, int x, int n) {
	for(; u <= n; u += u & -u) B[id][u] += x;
}

int get_ans(int n, vector<int> A, int q, int t, vector<vector<int> > queries) {
	for(int i = 1; i <= 20; i++) {
		for(int j = 1; j <= n; j++) B[i][j] = 0;
	}
	for(int i = 1; i <= n; i++) {
		a[i] = A[i - 1];
		update(a[i], i, 1, n);
	}
	
	int ans = 0;
	for(vector<int> vec : queries) {
		int t = vec[0], L = vec[1], R = vec[2];
		if(t == 1) {
			int len = R - L + 1, mx = 1;
			for(int i = 1; i <= 20; i++) {
				num[i] = calc(i, R) - calc(i, L - 1);
				mx = max(mx, num[i]);
			}
			if(len % 2 == 0 && mx <= len / 2) ans = (ans + len) % mod;
		}
		else {
			update(a[L], L, -1, n);
			a[L] = R;
			update(a[L], L, 1, n);
		}
	}
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.in", "r", stdin);
//	freopen("out.out", "w", stdout);
#endif

	int n; scanf("%d", &n);
	vector<int> A;
	for(int i = 0; i < n; i++) {
		int x; cin>>x;
		A.push_back(x);
	}
	int q, t; scanf("%d %d", &q, &t);
	
	vector<vector<int> > queries;
	for(int i = 0; i < q; i++) {
		vector<int> tmp;
		for(int j = 0; j < 3; j++) {
			int x; scanf("%d", &x);
			tmp.push_back(x);
		}
		queries.push_back(tmp);
	}
	
	cout<<get_ans(n, A, q, t, queries);
	return 0;
}