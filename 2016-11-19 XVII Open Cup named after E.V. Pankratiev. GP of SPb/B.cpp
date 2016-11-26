#include<bits/stdc++.h>
using namespace std;

int N, ansx, ansy, MAX, A[110];
int dp[110][100010], prex[110][100010], prey[110][100010], prew[110][100010];

void RENEW(int i, int j, int x, int y, int w){
	if (dp[i][j] > dp[x][y] + w){
		dp[i][j] = dp[x][y] + w;
		prex[i][j] = x;
		prey[i][j] = y;
		prew[i][j] = w;
	}
}

void dfs(int ansx, int ansy){
	if (!ansx)return;
	dfs(prex[ansx][ansy], prey[ansx][ansy]);
	printf("%d + %d\n", prew[ansx][ansy], A[ansx] - prew[ansx][ansy]);
}

int main(){
//	freopen("B.in", "r", stdin);
//	freopen("B.out", "w", stdout);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &A[i]);
	memset(dp, 61, sizeof(dp));
	dp[0][0] = 0;
	MAX = 0;
	for (int i = 1; i <= N; i++){
		for (int j = 0; j <= MAX; j++)
			if (dp[i - 1][j] < 1e9){
				int t = min(j, A[i]);
				RENEW(i, j - t, i - 1, j, A[i] - t);
				t = A[i] / 100;
				RENEW(i, j + t, i - 1, j, A[i]);
			}
		MAX += A[i] / 100;
	}
	ansx = N;
	ansy = 0;
	for (int j = 0; j <= MAX; j++)
		if (dp[N][ansy] > dp[N][j])
			ansy = j;
	printf("%d\n", dp[ansx][ansy]);
	dfs(ansx, ansy);
	return 0;
}
