#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

#define ll long long

const int MaxN = 17;
const int MaxM = (1<<17);

int n,m,w[MaxN],h[MaxN],q[MaxN];
int N; ll cost[MaxM];
ll f[MaxN][MaxM];

void Init()
{
	int i,j,mw,mh;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
		scanf("%d%d%d",w+i,h+i,q+i);
	N = (1<<n);
	for(i=1;i<N;i++)
	{
		mw = mh = 0;
		for(j=0;j<n;j++)
			if(i&(1<<j))
				mw = max(mw,w[j+1]), mh = max(mh,h[j+1]);
		for(j=0;j<n;j++)
			if(i&(1<<j))
				cost[i] += (ll) q[j+1] * (mw*mh-w[j+1]*h[j+1]);
		//printf("%d %lld  %d %d\n",i,cost[i],mw,mh);
	}
	return;
}

void Solve()
{
	int i,j,k;
	for(i=1;i<N;i++) f[1][i] = cost[i];
	for(j=2;j<=m;j++)
	{
		for(i=1;i<N;i++)
		{
			f[j][i] = f[j-1][i];
			for(k=i;k;k=(k-1)&i)
				f[j][i] = min(f[j][i], f[j-1][k] + cost[i^k]);
			//printf("%d %d %lld\n",j,i,f[j][i]);
		}
	}
	printf("%lld\n",f[m][N-1]);
	return;
}

int main()
{
	//freopen("C.in","r",stdin);
	//freopen("C.out","w",stdout);

	Init();
	Solve();

	return 0;
}
