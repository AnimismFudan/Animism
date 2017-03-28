#include <bits/stdc++.h>
using namespace std;

#define LL long long

const int pp = (1e9) + 7;

int N, M, K, res, ans;
char A[200010], B[200010];
int f[200010][15], fl[200010][15], fr[200010][15], sfr[200010][15], ff[200010], fn[200010];

int main(){
//	freopen("E.in", "r", stdin);
//	freopen("E.out", "w", stdout);
	scanf("%d%d%d", &N, &M, &K);
//	K = max(K, M - 1);
	scanf("%s%s", A + 1, B + 1);
	for (int i = K; i <= N; i += K)
		for (int t = 1; t <= M; t++){
			for (int k = 1; k <= M; k++) f[i + 1][k] = 0;
			f[i + 1][t + 1] = 1;
			for (int j = 0; j < K; j++){
				f[i - j][t + 1] = 1;
				for (int k = 1; k <= t; k++){
					f[i - j][k] = f[i - j + 1][k];
					if (A[i - j] == B[k])
						f[i - j][k] = (f[i - j][k] + f[i - j + 1][k + 1]) % pp;
				}
			}
			for (int j = 0; j < K; j++)
				sfr[i - j][t] = f[i - j][1];
		}
	for (int i = 1; i <= N; i += K)
		for (int t = 1; t <= M; t++){
			for (int k = 1; k <= M; k++) f[i - 1][k] = 0;
			f[i - 1][t - 1] = 1;
			for (int j = 0; j < K; j++){
				f[i + j][t - 1] = 1;
				for (int k = t; k <= M; k++){
					f[i + j][k] = f[i + j - 1][k];
					if (A[i + j] == B[k])
						f[i + j][k] = (f[i + j][k] + f[i + j - 1][k - 1]) % pp;
				}
			}
			for (int j = 0; j < K; j++)
				fl[i + j][t] = (f[i + j][M] - f[i + j - 1][M]) % pp;
		}
	for (int i = 1; i <= N; i += K){
		for (int k = 0; k <= M; k++) f[i - 1][k] = 0;
		f[i - 1][0] = 1;
		for (int j = 0; j < K; j++){
			f[i + j][0] = 1;
			for (int k = 1; k <= M; k++){
				f[i + j][k] = f[i + j - 1][k];
				if (A[i + j] == B[k])
					f[i + j][k] = (f[i + j][k] + f[i + j - 1][k - 1]) % pp;
			}
		}
		for (int j = 0; j < K; j++)
			ff[i + j] = (f[i + j][M] - f[i + j - 1][M]) % pp;
	}
	memset(f, 0 ,sizeof(f));
	f[0][0] = 1;
	for (int i = 1; i <= N; i++){
		f[i][0] = 1;
		for (int j = 1; j <= M; j++){
			f[i][j] = f[i - 1][j];
			if (A[i] == B[j])
				f[i][j] = (f[i][j] + f[i - 1][j - 1]) % pp;
		}
		fn[i] = (f[i][M] - f[i - 1][M]) % pp;
	}
	ans = 0;
	for (int i = K + 1; i <= N; i++)
		if (A[i] == B[M]){
			res = fn[i];
			if (K >= M){
				if (i % K != 0)
					for (int j = 1; j < M; j++)
						res = (res - (LL)sfr[i - K + 1][j] * fl[i][j + 1] % pp) % pp;
				res = (res - ff[i]) % pp;
			}
			ans = (ans + res) % pp;
		}
	if (ans < 0) ans += pp;
	printf("%d\n", ans);
}
