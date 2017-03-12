#include <bits/stdc++.h>
#define intl long long
#define maxn 101000
using namespace std;

intl f[maxn][2],ans;
int d[maxn][2];
int n;

int main() {
	freopen("space-cat.in","r",stdin);
	freopen("space-cat.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) scanf("%d",&d[i][0]);
	for (int i = 1; i <= n; i++) scanf("%d",&d[i][1]);
	f[1][1] = 0; f[1][0] = d[1][0] - d[1][1];
	for (int i = 2; i <= n; i++)
		f[i][0] = f[i][1] = 1LL << 61;
	for (int i = 2; i <= n; i++) {
		if (d[i - 1][1] >= d[i][1] && d[i - 1][1] < d[i][0]) f[i][1] = min(f[i][1], f[i - 1][1]);
		if (d[i - 1][0] <= d[i][0] && d[i - 1][0] > d[i][1]) f[i][0] = min(f[i][0], f[i - 1][0]);
		f[i][1] = min(f[i][1], f[i][0] + (intl) (d[i][0] - d[i][1]));
		f[i][0] = min(f[i][0], f[i][1] + (intl) (d[i][0] - d[i][1]));
	}
	ans = f[n][1];
	if (ans == 1LL << 61) printf("-1\n");
	else cout << ans << endl;
	return 0;
}
