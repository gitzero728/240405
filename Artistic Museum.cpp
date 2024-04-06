#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using INT = long long;
using pii = pair<int, int>;

const int NN = 505;
int a[NN], saved_ans[NN][NN];
int dp[NN][NN][NN];

int calc_num(int L, int R, int mn, int mx) {
	if(mn > mx) return 0;
	return dp[L][R][mx] - dp[L][R][mn - 1];
}

int calc(int L, int R) {
	if(R - L + 1 < 3) return 0;
	if(~saved_ans[L][R]) return saved_ans[L][R];
	
	int ans = 0, mx = a[L];
	for(int i = L + 1; i < R; i++) {
		ans = max(ans, calc(L, i - 1) + calc_num(i + 1, R, a[i], mx) + calc(i + 1, R));
		mx = max(mx, a[i]);
	}
	return saved_ans[L][R] = ans;
}

int MaxBeauty(int N, vector<int> A) {
	int n = N;
	for(int i = 1; i <= n; i++) {
		for(int j = i; j <= n; j++) saved_ans[i][j] = -1;
	}
	for(int i = 1; i <= n; i++) a[i] = A[i - 1];
	for(int x = 1; x <= n; x++) {
		for(int L = 1; L <= n; L++) {
			int num = 0;
			for(int R = L; R <= n; R++) {
				if(a[R] <= x) num++;
				dp[L][R][x] = num;
			}
		}
	}
	return calc(1, N);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.in", "r", stdin);
	//freopen("out.out", "w", stdout);
#endif
	
	int n; scanf("%d", &n);
	vector<int> A;
	for(int i = 0; i < n; i++) {
		int x; scanf("%d", &x);
		A.push_back(x);
	}
	cout<<MaxBeauty(n, A);
	return 0;
}
