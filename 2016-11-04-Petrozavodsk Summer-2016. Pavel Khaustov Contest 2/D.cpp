#include <bits/stdc++.h>
using namespace std;

struct str { int a, b, c; };

vector<str> f[2][10][1 << 8];
int mark[1 << 7][29][29][29];
int g[29][29][29];
int ans,t_;
int n,m,cl;
char s[60][60],s_[60][60];

void add(str u) {
	ans = max(ans, g[u.a][u.b][u.c]);
}

int get(int st, int a) {
	return ((st >> (a - 1)) & 1);
}

void dp() {
	for (int i = 0; i < 2; i++)
		for (int j = 0; j <= m; j++)
			for (int k = 0; k < (1 << m); k++)
				f[i][j][k].clear();
	f[0][m][0].push_back((str) { 0, 0, 0 });
	int o = 1;
	for (int u = 1; u <= n; u++) {
		for (int v = 0; v <= m; v++)
			for (int st = 0; st < (1 << m); st++)
				f[o][v][st].clear();
		for (int st = 0; st < (1 << m); st++)
			f[o][0][st] = f[o ^ 1][m][st];
		for (int v = 1; v <= m; v++) {
			cl++;
			for (int st = 0; st < (1 << m); st++) {
				if (!get(st, v) && s[u - 1][v] != 'B' && s[u][v] != 'B') {
					for (int j = 0; j < (int) f[o][v - 1][st].size(); j++) {
						int a = f[o][v - 1][st][j].a;
						int b = f[o][v - 1][st][j].b;
						int c = f[o][v - 1][st][j].c;
						if (s[u - 1][v] == 'G' && s[u][v] == 'G')
							a++;
						else if (s[u - 1][v] != 'G' && s[u][v] != 'G')
							c++;
						else b++;
						int ts = st | (1 << (v - 1));
						if (mark[ts][a][b][c] != cl) {
							mark[ts][a][b][c] = cl;
							f[o][v][ts].push_back((str) { a, b, c });
						}
					}
				}
				if (v > 1 && (s[u - 1][v - 1] == 'B' || get(st, v - 1))
					&& (s[u - 1][v] == 'B' || get(st, v))
					&& (s[u][v] != 'B' && s[u][v - 1] != 'B')) {
					for (int j = 0; j < (int) f[o][v - 2][st].size(); j++) {
						int a = f[o][v - 2][st][j].a;
						int b = f[o][v - 2][st][j].b;
						int c = f[o][v - 2][st][j].c;
						if (s[u][v] == 'G' && s[u][v - 1] == 'G')
							a++;
						else if (s[u][v] != 'G' && s[u][v - 1] != 'G')
							c++;
						else b++;
						int ts = st | (1 << (v - 1)) | (1 << (v - 2));
						if (mark[ts][a][b][c] != cl) {
							mark[ts][a][b][c] = cl;
							f[o][v][ts].push_back((str) { a, b, c });
						}
					}
				}
				if ((s[u - 1][v] == 'B' || get(st, v))) {
					for (int j = 0; j < (int) f[o][v - 1][st].size(); j++) {
						int a = f[o][v - 1][st][j].a;
						int b = f[o][v - 1][st][j].b;
						int c = f[o][v - 1][st][j].c;
						int ts = (st | (1 << (v - 1))) ^ (1 << (v - 1));
						if (mark[ts][a][b][c] != cl) {
							mark[ts][a][b][c] = cl;
							f[o][v][ts].push_back((str) { a, b, c });
						}
					}
				}
			}
		}
		o ^= 1;
	}
	int ST = 0;
	for (int i = 0; i < m; i++)
		if (s[n][i + 1] == 'B');
		else ST |= (1 << i);	
	for (int i = 0; i < (int) f[o ^ 1][m][ST].size(); i++)
		add(f[o ^ 1][m][ST][i]);
}

void prepare() {
	for (int i = 0; i <= 6; i++)
		for (int j = i; j <= 6; j++) {
			for (int a = 28; a >= 0; a--)
				for (int b = 28; b >= 0; b--)
					for (int c = 28; c >= 0; c--) {
						if (a > 0)
							g[a][b][c] = max(g[a][b][c], g[a - 1][b][c] + i + j);
						if (b > 0)
							g[a][b][c] = max(g[a][b][c], g[a][b - 1][c] + j);
						if (c > 0)
							g[a][b][c] = max(g[a][b][c], g[a][b][c - 1]);
					}
		}
	return;
}

int main() {
	//freopen("D.in","r",stdin);
	//freopen("D.out","w",stdout);
	prepare();
	while (scanf("%d %d",&n,&m) != EOF && n && m) {
		ans = -1;
		for (int i = 1; i <= n; i++)
			scanf("%s",s_[i] + 1);
		if (n < m) {
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= m; j++)
					s[j][i] = s_[i][j];
			swap(n,m);
		} else {
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= m; j++)
					s[i][j] = s_[i][j];
		}
		for (int i = 0; i <= n + 1; i++)
			for (int j = 0; j <= m + 1; j++)
				if (i == 0 || i == n + 1 || j == 0 || j == m + 1)
					s[i][j] = 'B';
		dp();
		printf("Case %d: ",++t_);
		if (ans == -1)
			printf("No solution\n");
		else printf("%d\n",ans);
	}
	return 0;
}
