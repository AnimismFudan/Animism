#include <bits/stdc++.h>
using namespace std;

const int MaxN = 1007;
const int MaxM = 500007;
const double eps = 1e-8;

int n,m,x[MaxN],y[MaxN];
double d[MaxM];

int main()
{
	freopen("bubbles.in","r",stdin);
	freopen("bubbles.out","w",stdout);
	
	int i,j;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		scanf("%d%d",x+i,y+i);
	
	for(i=1;i<=n;i++)
		for(j=i+1;j<=n;j++)
			if(x[j]!=x[i])
				d[++m] = 1.0 * x[i] + 1.0 * x[j] + 1.0 * ( 1.0 * y[j]*y[j]-1.0 * y[i]*y[i]) / (1.0 * x[j]- 1.0 * x[i]);
			else if(y[i]==y[j])
			{
				printf("0\n");
				return 0;
			}
	
	sort(d+1,d+m+1);
	
	j = 0;
	if(m>0)
	{
		for(i=2,j=1;i<=m;i++)
			if(fabs(d[i]-d[i-1]) > eps) j++;
	}
	
	printf("%d\n",j+1);
	return 0;
}

