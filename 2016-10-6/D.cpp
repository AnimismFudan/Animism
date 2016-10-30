#include <bits/stdc++.h>
#define intl long long
#define maxn 1010
using namespace std;
const intl Mo = 1000000007LL;
int n,q;
char s[maxn][maxn];
int f[maxn][maxn],g[maxn][maxn];
int ans[maxn][maxn];
intl Way,way[maxn][maxn],fw[maxn][maxn],gw[maxn][maxn];
int Ans;
int main() {
    freopen("D.in","r",stdin);
    freopen("D.out","w",stdout);
    scanf("%d",&n);
    for (int i = 1; i <= n; i++)
	scanf("%s",s[i] + 1);
    
    f[1][1] = (s[1][1] == 'C'); fw[1][1] = 1;
    for (int i = 0; i <= n; i++) f[i][0] = f[i][n + 1] = g[i][0] = g[i][n + 1] = -1;
    for (int i = 0; i <= n; i++) f[0][i] = f[n + 1][i] = g[0][i] = g[n + 1][i] = -1;
    for (int i = 1; i <= n; i++)
	for (int j = 1; j <= n; j++) {
	    if (i == 1 && j == 1) continue;
	    if (f[i - 1][j] > f[i][j - 1]) {
		f[i][j] = f[i - 1][j];
		fw[i][j] = fw[i - 1][j];
	    } else if (f[i - 1][j] < f[i][j - 1]) {
		f[i][j] = f[i][j - 1];
		fw[i][j] = fw[i][j - 1];
	    } else {
		f[i][j] = f[i][j - 1];
		fw[i][j] = (fw[i][j - 1] + fw[i - 1][j]) % Mo;
	    }
	    f[i][j] += (s[i][j] == 'C');
	}

    g[n][n] = (s[n][n] == 'C'); gw[n][n] = 1;
    for (int i = n; i >= 1; i--)
	for (int j = n; j >= 1; j--) {
	    if (i == n && j == n) continue;
	    if (g[i + 1][j] > g[i][j + 1]) {
		g[i][j] = g[i + 1][j];
		gw[i][j] = gw[i + 1][j];
	    } else if (g[i + 1][j] < g[i][j + 1]) {
		g[i][j] = g[i][j + 1];
		gw[i][j] = gw[i][j + 1];
	    } else {
		g[i][j] = g[i][j + 1];
		gw[i][j] = (gw[i][j + 1] + gw[i + 1][j]) % Mo;
	    }
	    g[i][j] += (s[i][j] == 'C');
	}

    for (int i = 1; i <= n; i++)
	for (int j = 1; j <= n; j++) {
	    ans[i][j] = f[i][j] + g[i][j] - (s[i][j] == 'C');
	    way[i][j] = ((intl)fw[i][j] * (intl)gw[i][j]) % Mo;
	}

    for (scanf("%d",&q); q; q--) {
	Ans = -1; Way = 0;
	int x1,y1,x2,y2,a,b;
	scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
	x1++; y1++; x2++; y2++;
	for (a = x2 + 1, b = y1 - 1; a <= n && b >= 1; a++, b--) {
	    if (ans[a][b] > Ans) {
		Ans = ans[a][b];
		Way = way[a][b];
	    } else if (ans[a][b] == Ans) {
		Way += way[a][b];
		Way %= Mo;
	    }
	}

	for (a = x1 - 1, b = y2 + 1; b <= n && a >= 1; a--, b++) {
	    if (ans[a][b] > Ans) {
		Ans = ans[a][b];
		Way = way[a][b];
	    } else if (ans[a][b] == Ans) {
		Way += way[a][b];
		Way %= Mo;
	    }
	}

	if (Ans == -1)
	    printf("0 0\n");
	else
	    cout << Ans << " " << Way << endl;
    }
    return 0;
}
