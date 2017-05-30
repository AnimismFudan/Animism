#include <bits/stdc++.h>
#define intl long long
using namespace std;

intl f[2][1010][1010];
intl S[1010][1010], A[3][3];
int n, m;

int main() {
	//freopen("H.in","r",stdin);
	//freopen("H.out","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%lld",&S[i][j]);
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			scanf("%lld", &A[i][j]);
	intl L = 1LL << 60;
	intl R = -L;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			f[0][i][j] = S[i][j];
			L = min(L, S[i][j]);
			R = max(R, S[i][j]);
		}
	printf("%lld %lld\n",L, R);
	int o = 1;
	for (int t = 1; t <= m; t++) {
		intl R = -1LL << 60;
		intl L = -R;
		for (int i = 1; i + (1 << t) - 1 <= n; i++)
			for (int j = 1; j + (1 << t) - 1 <= n; j++) {
				intl just = 0;
				for (int a = 0; a < 2; a++)
					for (int b = 0; b < 2; b++)
						just += A[a][b] * f[o ^ 1][i + a * (1 << (t - 1))][j + b * (1 << (t - 1))];
				f[o][i][j] = just;
				R = max(R, f[o][i][j]);
				L = min(L, f[o][i][j]);
			}
		printf("%lld %lld\n", L, R);
		o ^= 1;
	}
	return 0;
}
