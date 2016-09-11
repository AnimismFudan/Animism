#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define ll long long

const int MaxN = 40007;

int n,m,a;
int x[MaxN],y[MaxN];

int main()
{
	freopen("1006.in","r",stdin);
	//freopen("1006.out","w",stdout);
	
	int i,a; ll s;
	bool flg;
	
	while(scanf("%d",&n)!=EOF)
	{
		while(n--)
		{
			scanf("%d",&m);
			flg = true; s = 0;
			for(i=1;i<=m;i++)
			{
				scanf("%d",&a);
				if(a<0||a>2*(m-1)) flg = false;
				else
				{
					s += a;
					a -= m-1;
					if(a>0) x[m-a]++;
					if(a<0) y[m+a]++;
				}
			}
			flg &= (s==(ll)m*(m-1));
			if(flg)
			{
				for(i=1;i<m;i++)
					if(x[i]>i||y[i]>i) flg = false;
			}
			for(i=1;i<=m;i++) x[i] = y[i] = 0;
			if(flg) printf("T\n");
			else printf("F\n");
		}
	}
	
	return 0;
}

