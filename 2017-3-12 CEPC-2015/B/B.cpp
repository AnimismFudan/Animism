#include <bits/stdc++.h>
#define maxn 501000
using namespace std;

char s[maxn];
int p[maxn], sum[maxn], Ans[maxn];
int n, m, top, base, L, R;

void prepare() {
	int q = 1;
	while (q <= m) {
		if (s[q] == ' ') { q++; continue; }
		int cnt = 0;
		for (; s[q] != ' ' && q <= m; q++) cnt++;
		sum[++n] = cnt + 1;
		sum[n] += sum[n - 1];
	}
	return;
}

void brute_force(int x) {
	x++;
	int ans = -1 + sum[1]; int pas = 1;
	
	for (int i = 2; i <= n; i++) {
		if (sum[i] - sum[pas - 1] > x) {
			pas = i;
			ans += sum[i] - sum[i - 1];
		}
	}

	printf("%d\n",ans);
}

void solve(int L, int R) {
	int top = 0;
	p[++top] = 1;
	int pas = 1;
	Ans[L] = -1 + sum[1];
	for (int i = 2; i <= n; i++) {
		if (sum[i] - sum[pas - 1] > L + 1) {
			pas = i;
			Ans[L] += sum[i] - sum[i - 1];
			p[++top] = i;
		}
	}
	for (int u = L + 1; u <= R; u++) {
		for (int t = 2; t <= top; t++) {
			while (p[t] <= n && sum[p[t]] - sum[p[t - 1] - 1] <= u + 1)
				p[t]++;
			if (p[t] > n) break;
		}
		Ans[u] = -1;
		for (int t = 1; t <= top && p[t] <= n; t++) {
			Ans[u] += sum[p[t]] - sum[p[t] - 1];
		}
	}
	for (int u = L; u <= R; u++)
		printf("%d\n",Ans[u]);
}

int main() {
	//freopen("B.in","r",stdin);
	//freopen("B.out","w",stdout);
	do s[++m] = getchar();
	while (s[m] != '\n');
	m--;
	base = sqrt(m) + 1;
	prepare();
	scanf("%d %d",&L,&R);	
	for (int i = L; i <= min(R, base); i++)
		brute_force(i);
	if (base >= R) { return 0; }
	solve(max(base + 1, L), R);
	return 0;
}
