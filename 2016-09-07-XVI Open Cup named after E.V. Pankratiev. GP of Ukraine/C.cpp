#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int MaxN = 1000007;

int K,n,m,p[MaxN];
int l,kp[MaxN];
bool isp[MaxN];

int main()
{
	//freopen("C.in","r",stdin);
	//freopen("C.out","w",stdout);

	int i,j,t;

	scanf("%d",&K);
	n = 1000000; m = l = 0;
	for(i=2;i<MaxN;i++) isp[i] = true;
	for(i=2;i<MaxN;i++)
		if(isp[i])
		{
			p[++m] = i;
			for(j = i+i; j<MaxN; j+=i)
				isp[j] = false;
		}
	for(i=1;i<=m;i++)
	{
		t = p[i]; j = 0;
		while(t) j = j*10+(t%10), t/=10;
		if(j != p[i] && isp[j]) kp[++l] = p[i];
	}

	if(K>m) printf("%d\n",-1);
	else printf("%d\n",kp[K]);

	return 0;
}
