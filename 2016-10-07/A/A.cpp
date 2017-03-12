#include <bits/stdc++.h>
using namespace std;

const int MaxN = (int)1e5 + 7;

int n,m,f[2][MaxN];

inline int FindF(int d, int x)
{
	if(f[d][x]==x) return x;
	return f[d][x] = FindF(d,f[d][x]);
}

int main()
{
	int i,l,r,d;
	while(true)
	{
		scanf("%d%d",&n,&m);
		if(n==0 && m==0) break;
		for(i=0; i<=n+1; i++)
			f[0][i] = f[1][i] = i;
		for(i=1; i<=m; i++)
		{
			scanf("%d%d",&l,&r);
			d = FindF(0,l-1);
			if(d==0) printf("* ");
			else printf("%d ",d);
			f[0][r] = d;
			d = FindF(1,r+1);
			if(d>n) printf("*\n");
			else printf("%d\n",d);
			f[1][l] = d;
		}
		printf("-\n");
	}
	return 0;
}
