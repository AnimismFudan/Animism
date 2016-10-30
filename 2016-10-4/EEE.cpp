#include <bits/stdc++.h>
using namespace std;

const int MaxN = 20;

int T,id,n,d[MaxN][MaxN];
int way[MaxN],ans,ansx,ansy;

void DFS(int x)
{
	int i,t;
	if(x>n)
	{
		int s = 0;
		for(i=1; i<n; i++)
			s += d[way[i]][way[i+1]];
		if(s<ans) ans = s, ansx = way[1], ansy = way[n];
		else if(s==ans)
		{
			if(ansx>way[1] || (ansx==way[1] && ansy>way[n]))
				ansx = way[1], ansy = way[n];
		}
		return;
	}
	for(i=x;i<=n;i++)
	{
		t = way[i]; way[i] = way[x]; way[x] = t;
		DFS(x+1);
		t = way[i]; way[i] = way[x]; way[x] = t;
	}
	return;
}

int main()
{
	freopen("E.in","r",stdin);
	freopen("E_.out","w",stdout);
	
	int i,j,k,a,b;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++) d[i][j] = 1<<20;
		for(i=1;i<=n;i++)
			scanf("%d%d",&a,&b),
			d[a][b] = d[b][a] = 1;
		for(k=1;k<=n;k++)
			for(i=1;i<=n;i++)
				for(j=1;j<=n;j++)
					if(d[i][j]>d[i][k]+d[k][j])
						d[i][j] = d[i][k]+d[k][j];
		for(i=1;i<=n;i++) way[i] = i;
		ans = 1<<20;
		DFS(1);
		printf("Case #%d: %d %d %d\n",++id,ans,ansx,ansy);
	}
	return 0;
}

