#pragma GCC push_options
#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;

bool tt;
int f[2][7][1 << 6][1 << 6][2][2];
int n,m,T;
int A[70][7];
int o;

bool ss;
void add(int &a, int b) {
	(a += b);
	if (a >= 10007) a -= 10007;
}

void dp(int u) {
	//int v = u - 1;
	memset(f[o],0,sizeof(f[o]));
	for (int st = 0; st < (1 << m); st++)
		for (int ts = 0; ts < (1 << m); ts++)
			f[o][0][st][ts][0][0] = f[o ^ 1][m][st][ts][0][0];
	for (int k = 0; k < m; k++) {
		for (int st = 0; st < (1 << m); st++)
			for (int ts = 0; ts < (1 << m); ts++)
				for (int a = 0; a < 2; a++)
					for (int b = 0; b < 2; b++) {
						if (!f[o][k][st][ts][a][b]) continue;
						int resa = (st >> (k)) & 1;
						int resb = (ts >> (k)) & 1;
						resa += a; resb += b;
						if (A[u][k + 1] != -1 && (resa > A[u][k + 1] || resb > A[u][k + 1])) continue;
						for (int x1 = 0; x1 < 2; x1++)
							for (int x2 = 0; x2 < 2; x2++)
								for (int y1 = 0; y1 < 2; y1++)
									for (int y2 = 0; y2 < 2; y2++) {
										int nexa = x1 + x2 + resa;
										int nexb = y1 + y2 + resb;
										if (nexa != nexb) continue;
										if (A[u][k + 1] != -1 && (nexa != A[u][k + 1] || nexb != A[u][k + 1])) continue;
										int st_ = st ^ (st & (1 << (k)));
										int ts_ = ts ^ (ts & (1 << (k)));
										st_ ^= (x1 << (k));
										ts_ ^= (y1 << (k));
										add(f[o][k + 1][st_][ts_][x2][y2], f[o][k][st][ts][a][b]);
									}
					}
	}
	o ^= 1;
}

int main() {
	for (scanf("%d",&T); T; T--) {
		scanf("%d %d",&n,&m);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				scanf("%d",&A[i][j]);
		memset(f,0,sizeof(f));
		o = 1;
		f[0][m][0][0][0][0] = 1;
		for (int i = 1; i <= n; i++)
			dp(i);
		printf("%d\n",f[o ^ 1][m][0][0][0][0]);		
	}
	return 0;
}

#pragma GCC pop_options
