#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("J.in","r",stdin);
	freopen("J.out","w",stdout);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &A[i]);
	memcpy(B, A, sizeof(A));
	sort(B + 1, B + N + 1);
	f[0] = 0;
	r = 0;
	int i = 0;
	while (i <= N){
		int j = i + 1;
		while (j <= N){
			HA[A[j]]++;
			HB[B[j]]++;
			while (i < j && HA[B[i + 1]] == HB[B[i + 1]])
				i++;
			if (i == j) break;
		}
		while (calc())
	}
	return 0;
}
