#include <bits/stdc++.h>

#define LL long long

const int pp = (1e9) + 7;

int N, K, KK;
LL ans;
LL f[6010][3010], CN[6010];

int quick(int x, int y){
	LL s = 1, t = x;
	for (; y; y >>= 1){
		if (y & 1) s = s * t % pp;
		t = t * t % pp;
	}
	return s;
}

int rev(int x){
	return quick(x, pp - 2);
}

int main() {
	//freopen("E.in","r",stdin);
	//freopen("E.out","w",stdout);
	scanf("%d%d", &N, &K);
	KK = K << 1;
	f[0][0] = 1;
	for (int i = 2; i <= KK; i++)
		for (int j = 1; j <= K; j++)
			f[i][j] = (f[i - 1][j - 1] + f[i - 2][j - 1]) * (i - 1) % pp;
	ans = 0;
	CN[0] = 1;
	for (int i = 1; i <= KK; i++)
		CN[i] = CN[i - 1] * (N - i + 1) % pp * rev(i) % pp;
	for (int i = 0; i <= KK; i++)
		for (int j = 0; j <= K; j++)
			ans = (ans + f[i][j] * CN[i]) % pp;
	printf("%lld\n", ans);
	return 0;
}
