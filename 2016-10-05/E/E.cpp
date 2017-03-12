#include <bits/stdc++.h>
using namespace std;

const int MaxN = 10007;

int T,n,l[MaxN],a[MaxN],ans;

int main()
{
	int i;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(i=1; i<=n; i++)
			scanf("%d", l+i);
		sort(l+1,l+n+1);
		for(i=1; i+i<=n; i++)
		{
			a[i] = l[i+i-1];
			a[n-i+1] = l[i+i];
		}
		if(i+i-1==n) a[i] = l[n];
		ans = abs(a[1]-a[n]);
		for(i=1; i<n; i++)
			ans = max(ans, abs(a[i+1]-a[i]));
		printf("%d\n",ans);
	}
	return 0;
}

