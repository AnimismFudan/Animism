#include <bits/stdc++.h>

using namespace std;

int Test, N, M, ans;
int A[260];
int S[260][260];
int dp[260][260][260][2];

int calc(int l, int r, int d){
	return S[l][d] - S[r][d] + A[r];
}

int work(int l, int r, int d, int t){
	if (l > r) return 0;
	if (l == r) return A[l];
	if (dp[l][r][d][t] != -1) 
		return dp[l][r][d][t];
	int res;
	dp[l][r][d][t] = 0;
	if (calc(l, r, d) <= M){
		dp[l][r][d][t] = calc(l, r, d);
		return dp[l][r][d][t];
	}
	res = 0;
	for (int i = l + d; i <= r; i += d){
		res += A[i - d];
		if (res > M) break;
		dp[l][r][d][t] = max(dp[l][r][d][t], res + calc(i, r, d) - work(i, r, d, !t));
	}
	res = 0;
	for (int i = r - d; i >= l; i -= d){
		res += A[i + d];
		if (res > M) break;
		dp[l][r][d][t] = max(dp[l][r][d][t], res + calc(l, i, d) - work(l, i, d, !t));
	}
	for (int dd = 2 * d; ; dd += d){
		res = calc(l, r, d);
		int ll = l + dd - d;
		if (ll > r) break;
		int tt = (r - ll) / dd;
		int rr = ll + dd * tt;
		res -= calc(ll, rr, dd);
		if (res > M) continue;
		res = res + calc(ll, rr, dd) - work(ll, rr, dd, !t);
		dp[l][r][d][t] = max(dp[l][r][d][t], res);
	}
	return dp[l][r][d][t];
}

int main(){
	freopen("coins.in", "r", stdin);
	freopen("coins.out", "w", stdout);
	scanf("%d", &Test);
	memset(dp, 255, sizeof(dp));
	while (Test--){
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= N; i++)
			scanf("%d", &A[i]);
		for (int i = N; i > 0; i--)
			for (int j = 1; j <= N; j++){
				S[i][j] = A[i];
				if (i + j <= N)
					S[i][j] += S[i + j][j];
			}
		ans = work(1, N, 1, 0);
		printf("%d %d\n", ans, S[1][1] - ans);
		for (int l = 1; l <= N; l++)
			for (int d = 1; d <= N; d++){
				S[l][d] = 0;
				for (int r = l; r <= N; r += d)
					dp[l][r][d][0] = dp[l][r][d][1] = -1;
			}
	}
}
