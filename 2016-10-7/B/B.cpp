#include <bits/stdc++.h>
#define intl long long
#define maxn 1010
using namespace std;

intl sum[maxn][maxn],f[maxn][maxn];
int A[maxn][maxn];
int n,T;
intl ans;

int main() {
    freopen("B.in","r",stdin);
    freopen("B.out","w",stdout);
    while(scanf("%d",&n) != EOF && n) {
	ans = 0;
	for (int i = 1; i <= n; i++)
	    for (int j = 1; j <= i; j++) {
		scanf("%d",&A[i][j]);
		ans += A[i][j];
	    }
	for (int j = 0; j <= n + 1; j++)
	    A[n + 1][j] = 0;
	for (int i = 0; i <= n + 1; i++)
	    for (int j = 0; j <= n + 1; j++) {
		f[i][j] = 1LL << 60;
	    }
	for (int i = 0; i <= n + 1; i++)
	    f[i][0] = 0;
	for (int j = 1; j <= n; j++) {
	    sum[n + 1][j] = 0;
	    for (int i = n; i >= j; i--)
		sum[i][j] = sum[i + 1][j] + (intl)A[i][j];
	}
	for (int j = 1; j <= n; j++) {
	    for (int i = n + 1; i >= j; i--) {
		f[i][j] = 1LL << 60;
		f[i][j] = min(f[i][j], f[i][j - 1] + sum[i][j]);
		f[i][j] = min(f[i][j], f[i - 1][j - 1] + sum[i][j]);		
		if (i <= n)
		    f[i][j] = min(f[i][j], f[i + 1][j] + A[i][j]);
	    }
	}
	ans -= min(f[n][n], f[n + 1][n]);
	cout << ans << endl;
    }
    return 0;
}
