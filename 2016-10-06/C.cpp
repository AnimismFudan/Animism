#include <bits/stdc++.h>
using namespace std;

int n,m,s;

int main()
{
	int i,j;
	scanf("%d",&s);
	if(s==2 || s==5)
	{
		printf("Impossible\n");
		return 0;
	}
	n = 1;
	while(n*(n-1) <= s+s) n++;
	n--;
	s = s - n*(n-1)/2;
	m = n*(n-1)/2 - s;
	printf("%d %d\n",n,m);
	for(i=1; i<=n; i++)
		for(j=i+1; j<=n; j++)
		{
			if(s>0 && i==1 && j>2) {s--; continue;}
			if(s>0 && i==n-1 && j==n) {s--; continue;}
			printf("%d %d\n",i,j);
		}
	return 0;
}

