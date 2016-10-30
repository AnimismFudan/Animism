#include <bits/stdc++.h>
using namespace std;

int T,id,n,m;

int main()
{
	int i;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		printf("Case #%d:",++id);
		for(i=m+1; i<m+m; i++)
			printf(" %d",i);
		for(i=1; i<=m; i++)
			printf(" %d",i);
		for(i=m+m; i<=n; i++)
			printf(" %d",i);
		printf("\n");
	}
	return 0;
}

