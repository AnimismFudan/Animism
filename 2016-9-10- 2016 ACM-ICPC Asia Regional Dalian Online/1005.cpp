#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
	freopen("1005.in","r",stdin);
	freopen("1005.out","w",stdout);
	int s,t,m,h,l,k,res;
	while(scanf("%d%d%d",&h,&l,&k)!=EOF)
	{
		m = k/h;
		t = (k+m)/(m+1);
		res = l%t;
		s = l/t;
		//printf("%d %d %d\n",res,t,s);
		if(res==0) printf("%d\n",(s+m-1)/m);
		else
		{
			if(s%m==0)
			{
				if(res + t*m <= k) printf("%d\n",s/m);
				else printf("%d\n",s/m+1);
			}
			else printf("%d\n",(s+m-1)/m);
		}
	}
	return 0;
}

