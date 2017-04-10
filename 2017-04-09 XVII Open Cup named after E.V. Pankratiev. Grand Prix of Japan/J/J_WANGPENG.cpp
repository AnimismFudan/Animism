#include <bits/stdc++.h>
using namespace std;

int f[110][1200][32];
int n, M, k;
int D[110];

void update(int &a, int b) {
	a += b;
	a %= 1000000007;
}

int main() {
	//freopen("J.in","r",stdin);
	//freopen("J.out","w",stdout);
	scanf("%d %d %d",&n,&M,&k);
	for (int i = 1; i <= n; i++) {
		scanf("%d",&D[i]);
		D[i] = (D[i - 1] + D[i]) % M;
	}
	f[0][0][0] = 1;
	for (int i = 1; i <= n; i++) {
		memcpy(f[i], f[i - 1], sizeof(f[i - 1]));
		for (int st = 0; st < (1 << k); st++) {
			for (int j = 0; j < k; j++) {
				if ((st >> j & 1)) continue;
				int bias = 0;
				if (j > 0 && (st >> (j - 1) & 1)) bias += D[i - 1];
				else if (j > 0) bias -= D[i - 1];
				if (j < (k - 1) && (st >> (j + 1) & 1)) bias += D[i - 1];
				else if (j < (k - 1)) bias -= D[i - 1];
				bias = (bias % M + M) % M;
				for (int dis = 0; dis < M; dis++)
					update(f[i][st | (1 << j)][(dis + bias) % M], f[i - 1][st][dis]);
			}
		}
	}

	printf("%d\n",f[n][(1 << k) - 1][0]);
	return 0;
}
