#include <bits/stdc++.h>
using namespace std;

double f[52][52][52 * 52];
int n,m,T;

int main() {
	for (scanf("%d",&T); T; T--) {
		scanf("%d %d",&n,&m);
		for (int i = max(n, m); i <= n * m; i++)
			f[n][m][i] = 0;
		for (int t = n * m - 1; t >= 0; t--) {
			for (int i = 0; i <= n; i++)
				for (int j = 0; j <= m; j++) {
					if (i == n && j == m) continue;
					if (t < max(i, j)) continue;
					if (t > i * j) continue;
					f[i][j][t] = 0;
					f[i][j][t] += f[i][j][t + 1] * (double) (i * j - t) / (double) (n * m - t);
					f[i][j][t] += f[i + 1][j][t + 1] * (double) ((n - i) * j) / (double) (n * m - t);
					f[i][j][t] += f[i][j + 1][t + 1] * (double) ((m - j) * i) / (double) (n * m - t);
					f[i][j][t] += f[i + 1][j + 1][t + 1] * (double) ((n - i) * (m - j)) / (double) (n * m - t);
					f[i][j][t] += 1.0;
				}
		}
		printf("%.12lf\n",f[0][0][0]);
	}
	return 0;
}