#include <bits/stdc++.h>
using namespace std;

int N, up;
int f[100010];
int a[100010], b[100010];
map <int , int> HA, HB;
int B[320][100010];
int L[320], R[320];

int calc(int j, int i){
	int k = sqrt(i - j);
	if (k * k < i - j) k++;
	return f[j] + k;
}

int main() {
//	freopen("J.in","r",stdin);
//	freopen("J.out","w",stdout);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &a[i]);
	memcpy(b, a, sizeof(a));
	sort(b + 1, b + N + 1);
	f[0] = 0;
	up = sqrt(N);
	if (up * up < N) up++;
	for (int i = 1; i <= up; i++)
		L[i] = 1;
	int p = 1;
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= up; j++){
			int k = i - (j - 1) * (j - 1) - 1;
			if (k <= 0) continue;
			while (L[j] <= R[j] && f[B[j][R[j]]] >= f[k])
				R[j]--;
			while (L[j] <= R[j] && j * j < (i - B[j][L[j]]))
				L[j]++;
			B[j][++R[j]] = k;
		}
		HA[a[i]]++;
		HB[b[i]]++;
		while (p < i && HA[b[p]] == HB[b[p]])
			p++;
		if (p == i && HA[b[p]] == HB[b[p]]){
			int k = sqrt(i);
			if (k * k < i) k++;
			f[i] = k;
			if (a[i] == b[i])
				f[i] = f[i - 1];
			for (int j = 1; j <= up; j++)
				if (L[j] <= R[j])
					f[i] = min(f[i], calc(B[j][L[j]], i));
		}
		else f[i] = 2e9;
	}
	printf("%d\n", f[N]);
	return 0;
}
