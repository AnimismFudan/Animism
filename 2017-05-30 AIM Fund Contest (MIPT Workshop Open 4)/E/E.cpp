#include <bits/stdc++.h>
using namespace std;

const int MaxN = 300007;

int N, h[MaxN], g[MaxN];
long long ans;

int main()
{
	scanf("%d", &N);
	for (int i=1; i<=N; i++)
		scanf("%d", h+i);
	for (int i=1; i<=N; i++)
		scanf("%d", g+i);
	sort(h+1, h+N+1);
	sort(g+1, g+N+1);
	for (int i=1; i<=N; i++)
		ans += abs(h[i] - g[i]);
	cout << ans << endl;
	return 0;
}

