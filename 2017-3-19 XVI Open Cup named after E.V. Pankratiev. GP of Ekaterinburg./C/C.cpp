#include <bits/stdc++.h>
#define maxn 1010
using namespace std;

int p[maxn], f[maxn][maxn], g[maxn];
int n, m;

bool cmp(int a, int b) {
	return (g[a] < g[b] || (g[a] == g[b] && a > b));
}

int main() {
	//freopen("C.in","r",stdin);
	//freopen("C.out","w",stdout);
	scanf("%d %d",&n,&m);
	f[1][1] = m;
	for (int i = 2; i <= n; i++) {
		int res = (i + 1) / 2 - 1;
		for (int j = 1; j < i; j++) p[j] = j;
		for (int j = 1; j < i; j++) g[j] = f[i - 1][j];
		sort(p + 1, p + i, cmp);
		int Res = m;
		for (int j = 1; j < i; j++) {
			if (res > 0) {
				f[i][p[j]] = f[i - 1][p[j]] + 1;
				Res -= f[i][p[j]];
				res--;
			} else {
				f[i][p[j]] = 0;				
			}
		}
		if (Res < 0) {
			f[i][i] = -1;
			for (int j = 1; j < i; j++)
				f[i][j] = f[i - 1][j];
		} else {
			f[i][i] = Res;
		}
	}
	for (int i = n; i >= 1; i--)
		printf("%d ",f[n][i]);
	return 0;
}
