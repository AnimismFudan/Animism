#include <bits/stdc++.h>
using namespace std;


int n, m, Ans, tp, top;
int p[1010], cnt[1010], pas[1010], g[1010];
int f[1010][110], d[1010][110];
int anss[1010];

bool judge(int a, int b) {
	for (int i = 1; i <= m; i++)
		if (f[a][i] < f[b][i]) return false;
	return true;
}

bool cmp(int a, int b) {
	return (cnt[a] < cnt[b]);
}

void solve(int u) {
	top = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			f[i][j] = d[i][j] - d[u][j];			
		}
		int mi = 1 << 30;
		for (int j = 1; j <= m; j++)
			mi = min(f[i][j], mi);
		for (int j = 1; j <= m; j++)
			f[i][j] -= mi;
		bool flag = true;
		for (int j = 1; j <= m; j++)
			if (f[i][j] > 1) { flag = false; break; }
		if (!flag) continue;
		p[++top] = i;
		cnt[i] = 0;
		for (int j = 1; j <= m; j++)
			cnt[i] += f[i][j];
	}
	sort(p + 1, p + top + 1, cmp);
	int ans = 0;
	for (int i = 1; i <= top; i++) {
		g[i] = 1; pas[i] = 0;
		for (int j = i - 1; j > 0; j--) {
			if (judge(p[i], p[j]) && g[i] < g[j] + 1) {
				g[i] = g[j] + 1;
				pas[i] = j;
				//break;
			}
		}
		if (g[ans] < g[i]) {
			ans = i;			
		}
	}
	if (Ans < g[ans]) {
		Ans = g[ans];
		tp = 0;		
		for (int i = ans; i; i = pas[i])
			anss[++tp] = p[i];
	}
}

bool pmc(int a, int b) {
	for (int i = 1; i <= m; i++)
		if (d[a][i] < d[b][i]) return false;
		else if (d[a][i] > d[b][i]) return true;
	return true;
}

int main() {
	//freopen("K.in","r",stdin);
	//freopen("K.out","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			scanf("%d",&d[i][j]);
	}
	srand(173);
	for (int T = 50; T; T--) {
		solve(abs(rand() * rand() + rand()) % n + 1);
	}
	cout << Ans << endl;
	sort(anss + 1, anss + tp + 1, pmc);
	for (int i = 1; i <= tp; i++)
		printf("%d ",anss[i]);
	return 0;
}
