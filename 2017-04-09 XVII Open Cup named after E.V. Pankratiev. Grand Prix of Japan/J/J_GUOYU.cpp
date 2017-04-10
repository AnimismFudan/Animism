#include <bits/stdc++.h>
using namespace std;

#define LL long long

//const LL pp = (1e9) + 7;
const LL pp = 1e18;

int N, M, K;
LL D[110];
LL dp[110][210][12][40][2][2][3];

void Plus(LL &x, LL y){
	x = x + y;
	if (x >= pp) x -= pp;
}

int main() {
	freopen("J.in","r",stdin);
	freopen("J.out","w",stdout);
	scanf("%d%d%d", &N, &M, &K);
	for (int i = 1; i < N; i++) scanf("%lld", &D[i]);
	dp[1][0][0][0][0][0][1] = 1;
	for (int i = 1; i <= N; i++)
		for (int j = 0; j <= N * 2; j++)
			for (int k = 0; k <= K; k++)
				for (int m = 0; m < M; m++)
					for (int t1 = 0; t1 < 2; t1++)
						for (int t2 = 0; t2 < 2; t2++)
							for (int t3 = 0; t3 < 3; t3++)
								if (dp[i][j][k][m][t1][t2][t3]){
									LL ju = (j + t3 - 1) / 2;
									LL jd = (j - t3 + 1) / 2;
									LL ja = (j - t1 - t2) / 2;
									
									if (i == 3 && j == 3)
										printf(" ");
									
									Plus(dp[i + 1][j][k][(m + j * D[i]) % M][t1][t2][t3], dp[i][j][k][m][t1][t2][t3]);
									if (j == 0 && t1 && t2) continue;
									if (ju < 0) continue;
									if (jd < 0) continue;
									if (ja < 0) continue;
									
									Plus(dp[i + 1][j][k + 1][(m + j * D[i]) % M][t1][t2][t3], dp[i][j][k][m][t1][t2][t3] * j % pp);
									Plus(dp[i + 1][j + 2][k + 1][(m + (j + 2) * D[i]) % M][t1][t2][t3], dp[i][j][k][m][t1][t2][t3]);
									if (j > 1){
										LL tt = (ju * jd - ja) % pp;
										Plus(dp[i + 1][j - 2][k + 1][(m + (j - 2) * D[i]) % M][t1][t2][t3], dp[i][j][k][m][t1][t2][t3] * tt % pp);
									}
									if (!t1 && t3 > 0)
										Plus(dp[i + 1][j + 1][k + 1][(m + (j + 1) * D[i]) % M][ 1][t2][t3 - 1], dp[i][j][k][m][t1][t2][t3]);
									if (!t1 && j > 0 && t3 > 0)
										Plus(dp[i + 1][j - 1][k + 1][(m + (j - 1) * D[i]) % M][ 1][t2][t3 - 1], dp[i][j][k][m][t1][t2][t3] * ju % pp);
									if (!t2 && t3 < 2)
										Plus(dp[i + 1][j + 1][k + 1][(m + (j + 1) * D[i]) % M][t1][ 1][t3 + 1], dp[i][j][k][m][t1][t2][t3]);
									if (!t2 && j > 0 && t3 < 2)
										Plus(dp[i + 1][j - 1][k + 1][(m + (j - 1) * D[i]) % M][t1][ 1][t3 + 1], dp[i][j][k][m][t1][t2][t3] * jd % pp);
								}
	printf("%lld\n", dp[N + 1][0][K][0][1][1][1]);
	return 0;
}
