#include <bits/stdc++.h>
using namespace std;

#define LL long long

const int pp = (1e6) + 3;

LL N, A, B, C;
LL f[10010][10010];

int main(){
	freopen("F.in", "r", stdin);
	freopen("F_.out", "w", stdout);
	scanf("%lld%lld%lld%lld", &N, &A, &B, &C);
	for (int i = 1; i <= N; i++)
		scanf("%lld", &f[i][1]);
	for (int i = 1; i <= N; i++)
		scanf("%lld", &f[1][i]);
	for (int i = 2; i <= N; i++)
		for (int j = 2; j <= N; j++)
			f[i][j] = (A * f[i][j - 1] + B * f[i - 1][j] + C) % pp;
	printf("%lld", f[N][N]);
	return 0;
}

