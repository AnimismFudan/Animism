#include <bits/stdc++.h>
using namespace std;

const int MaxN = 10007;
const int MaxM = 107;

int n,m,ans,loc;
int cnt[MaxN],f[MaxN],g[MaxN];
char mp[MaxM][MaxN];

int main()
{
	//freopen("A.in","r",stdin);
	//freopen("A.out","w",stdout);

	int i,j;

	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
		scanf("%s",mp[i]+1);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			if(mp[j][i]=='E') cnt[i]++;

	for(i=1;i<=n;i++)
		f[i] = f[i-1] + cnt[i];
	for(i=n;i>=1;i--)
		g[i] = g[i+1] + (m-cnt[i]);
	
	ans = n*m+1;
	for(i=0;i<=n;i++)
	{
		if(f[i]+g[i+1]<ans) ans = f[i]+g[i+1],loc = i;
		//printf("%d %d\n",i,f[i]+g[i+1]);
	}
	
	printf("%d %d\n",loc,loc+1);
	
	return 0;
}

