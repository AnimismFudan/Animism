#include <bits/stdc++.h>
#define intl long long
#define midl ((L + R) >> 1)
#define midr (midl + 1)
#define maxn 201000
using namespace std;

int val[maxn],p[maxn];
intl sum[maxn];
int n,ansl,ansr;
intl s;

bool cmp(int a,int b) {
	return (sum[a] < sum[b]);
}

void update(int L, int R) {
	if (R - L > ansr - ansl || (R - L == ansr - ansl && L < ansl)) {
		ansr = R;
		ansl = L;
	}
	return;
}

void solve(int L, int R) {
	if (L == R) return;
	solve(L, midl);
	solve(midr, R);
	sort(p + L, p + midr, cmp);
	sort(p + midr, p + R + 1, cmp);
	int q = midl;
	int ans = n + 1;
	for (int u = R; u >= midr; u--) {
		while (q >= L && sum[p[u]] - sum[p[q]] <= s) {
			ans = min(ans, p[q]);
			q--;
		}
		update(ans, p[u]);
	}
	return;
}

int main() {
	//freopen("A.in","r",stdin);
	//freopen("A.out","w",stdout);
	cin >> n >> s;
	for (int i = 1; i <= n; i++)
		scanf("%d",&val[i]);
	for (int i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + (intl) val[i];
	for (int i = 1; i <= n; i++)
		p[i] = i;
	ansr = ansl = 0;
	solve(0, n);
	if (!(ansr - ansl)) {
		printf("-1\n");
		return 0 ;
	}
	printf("%d\n%d %d\n",ansr - ansl,ansl,n - ansr);
	return 0;
}
