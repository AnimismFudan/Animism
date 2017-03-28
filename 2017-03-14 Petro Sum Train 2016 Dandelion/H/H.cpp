#include <bits/stdc++.h>
using namespace std;

const int X[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int Y[8] = { 1,-1, 0,  0, 1, -1, 1, -1 };

int done[1010][1010], val[1010][1010], vis[1010][1010];
char s[1010][1010];
int ans, n, m;
int qx[1010000], qy[1010000];
int xx[1010000], yy[1010000];

int bfs(int x, int y, int js) {
	int L = 0, R = 0;
	qx[++R] = x; qy[R] = y;
	done[x][y] = 1;
	int ans = 0;
	while (L < R) {		
		int a = qx[++L], b = qy[L];
		ans += val[a][b];
		for (int i = 0; i < js; i++) {
			if (s[a + X[i]][b + Y[i]] == '*' && !done[a + X[i]][b + Y[i]]) {
				done[a + X[i]][b + Y[i]] = 1;
				qx[++R] = a + X[i];
				qy[R] = b + Y[i];
			}
		}
	}
	return R;
}

int BFS(int x, int y, int js) {
	int L = 0, R = 0;
	qx[++R] = x; qy[R] = y;
	int ans = 0;
	vis[x][y] = 1;
	while (L < R) {		
		int a = qx[++L], b = qy[L];
		ans += val[a][b];
		for (int i = 0; i < js; i++) {
			if (!done[a + X[i]][b + Y[i]] && !vis[a + X[i]][b + Y[i]]) {
				vis[a + X[i]][b + Y[i]] = 1;
				qx[++R] = a + X[i];
				qy[R] = b + Y[i];
			}
		}
	}
	return ans;
}

bool prepare() {
	bool flag = false;
	int top = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (s[i][j] == '*' && s[i + 1][j + 1] == '*'
				&& !done[i][j] && done[i][j + 1] && done[i + 1][j]) {
				flag = true;
				int tp = bfs(i, j, 8);
				for (int i = 1; i <= tp; i++) {
					xx[++top] = qx[i];
					yy[top] = qy[i];
				}
			}
			if (s[i][j] == '*' && s[i + 1][j - 1] == '*'
				&& !done[i][j] && done[i][j - 1] && done[i + 1][j]) {
				flag = true;
				int tp = bfs(i, j, 8);
				for (int i = 1; i <= tp; i++) {
					xx[++top] = qx[i];
					yy[top] = qy[i];
				}
			}
		}
	
	if (!flag) return false;

	for (int i = 1; i <= top; i++) {
		int a = xx[i]; int b = yy[i];
		for (int j = 0; j < 8; j++)
			done[a + X[j]][b + Y[j]] = 1;
	}
	
	return true;
}

int main() {
	freopen("H.in","r",stdin);
	freopen("H.out","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++)
		scanf("%s",s[i] + 1);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (s[i][j] == '*' && !done[i][j]) {
				val[i][j] = 1; bfs(i, j, 4);
			}
		}

	memset(done,0,sizeof(done));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (!done[i][j] && s[i][j] == '*' && (i == 1 || i == n || j == 1 || j == m)) {
				bfs(i, j, 8);
			}
	int tp = 0;
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (done[i][j]) qx[++tp] = i, qy[tp] = j;
		}

	for (int i = 1; i <= tp; i++) {
		int a = qx[i], b = qy[i];
		for (int j = 0; j < 8; j++)
			done[a + X[j]][b + Y[j]] = 1;
	}
	
	for (int i = 0; i <= n + 1; i++) done[i][1] = done[i][0] = done[i][m] = done[i][m + 1] = 1;
	for (int i = 0; i <= m + 1; i++) done[1][i] = done[0][i] = done[n][i] = done[n + 1][i] = 1;

	while (prepare());
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (!vis[i][j] && !done[i][j]) ans = max(ans, BFS(i, j, 4));
		}
	
	printf("%d\n",ans);
	return 0;

}
