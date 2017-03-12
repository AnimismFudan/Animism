#include <bits/stdc++.h>
using namespace std;

struct str { double C; int I,O; } dot[2010];

double C[60][60];
int I[60][60],O[60][60];
int m,n,ans;
int f[2][1510][1510];

bool cmp(const str &a, const str &b) {
    return (a.C < b.C);
}

int main() {
    freopen("J.in","r",stdin);
    freopen("J.out","w",stdout);
    scanf("%d",&m);
    for (int i = 1; i <= m; i++)
	for (int j = 1; j <= m; j++)
	    scanf("%lf",&C[i][j]);
    for (int i = 1; i <= m; i++)
	for (int j = 1; j <= m; j++)
	    scanf("%d",&I[i][j]);
    for (int i = 1; i <= m; i++)
	for (int j = 1; j <= m; j++)
	    scanf("%d",&O[i][j]);
    for (int i = 1; i <= m; i++)
	for (int j = i + 1; j <= m; j++) {
	    dot[++n] = (str) { C[i][j], I[i][j], O[i][j] };
	}

    sort(dot + 1, dot + n + 1, cmp);

    for (int i = 1; i <= n + 1; i++)
	f[0][0][i] = f[1][0][i] = (1 << 28);

    f[1][0][0] = (1 << 28);
    for (int i = 1; i <= n; i++) {
	for (int j = 0; j <= n + 1; j++)
	    f[0][i][j] = f[1][i][j] = (1 << 28);
	for (int j = 0; j <= n; j++) {
	    f[0][i][j + 1] = min(f[0][i][j + 1], f[0][i - 1][j] + dot[i].O);
	    if (j > 0) f[0][i][j - 1] = min(f[0][i][j - 1], f[0][i - 1][j] + dot[i].I);
	    f[1][i][j + 1] = min(f[1][i][j + 1], f[1][i - 1][j] + dot[i].O);
	    if (j > 0) f[1][i][j - 1] = min(f[1][i][j - 1], f[1][i - 1][j] + dot[i].I);
	    f[1][i][j] = min(f[1][i][j], f[0][i - 1][j]);
	}
    }

    printf("%d %d\n",n / 2, f[n & 1][n][0]);
    return 0;
}
