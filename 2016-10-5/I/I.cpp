#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MaxN = (int)1e6 + 7;

int T,n,a[MaxN],b[MaxN];
ll ans;

int main()
{
	int i;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(i=1; i<=n; i++)
			scanf("%d",a+i);
		b[n+1] = 0;
		for(i=n; i>=1; i--)
			b[i] = max(b[i+1], a[i]);
		ans = 0;
		for(i=1; i<=n; i++)
			ans += (ll) b[i]-a[i];
		printf("%lld\n",ans);
	}
	return 0;
}
