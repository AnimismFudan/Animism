#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, T, P, ans;
int A[200010], C[200010];
int SG[200010], pre[200010], Tpre[200010];

int main() {
//	freopen("H.in","r",stdin);
//	freopen("H.out","w",stdout);
	scanf("%d", &N);
	SG[0] = 0;
	T = sqrt(N);
	P = N / T;
	ans = 0;
	for (int i = 1; i <= N; i++)
		pre[i] = -1;
	for (int j = 0; j <= P; j++){
		Tpre[j] = 2e9;
		for (int k = 0; k < T; k++)
			Tpre[j] = min(Tpre[j], pre[j * T + k]);
	}
	for (int i = 1; i < N; i++){
		scanf("%d%d", &C[i], &A[i]);
		for (int j = 0; j <= P; j++)
			if (Tpre[j] < i - C[i]){
				for (int k = 0; k < T; k++)
					if (pre[j * T + k] < i - C[i]){
						SG[i] = j * T + k;
						pre[SG[i]] = i;
						break;
					}
				Tpre[j] = 2e9;
				for (int k = 0; k < T; k++)
					Tpre[j] = min(Tpre[j], pre[j * T + k]);
				break;
			}
		if (A[i] & 1) ans ^= SG[i];
	}
	if (ans) printf("First\n");
	else printf("Second\n");
	return 0;
}
