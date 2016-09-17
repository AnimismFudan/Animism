#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MaxN = 5 * (int)1e5 + 7;
const ll len = 2 * (ll) 1e9;

int n,l,b[MaxN];

int Query(int d)
{
	//printf("%d\n",d);
	int le,ri,mi;
	le = 1; ri = l;
	while(le<=ri)
	{
		mi = (le+ri)>>1;
		if(b[mi]<d) le = mi+1;
		else ri = mi-1;
	}
	return b[le];
}

int main()
{
	freopen("1001.in","r",stdin);
	freopen("1001.out","w",stdout);
	
	int i,dt;
	ll x,y,z,w;

	for(x=1LL;x<=len;x*=2)
		for(y=1LL;x*y<=len;y*=3)
			for(z=1LL;x*y*z<=len;z*=5)
				for(w=1LL;x*y*z*w<=len;w*=7)
				{
					//printf("%lld\n",x*y*z*w);
					b[++l] = (int) x*y*z*w;
				}
	sort(b+1,b+l+1);
	//printf("%d\n",l);
	//for(i=1;i<=l;i++)
	//	printf("%d ",b[i]);
	//printf("\n");
	
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		scanf("%d",&dt),
		printf("%d\n",Query(dt));
	
	return 0;
}

