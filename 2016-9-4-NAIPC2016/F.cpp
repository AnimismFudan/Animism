#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

#define ll long long

const int MaxN = 107;
const int MaxM = 10007;
const int mod = (int)1e9+7;

int n,w,h;
ll ans,f[MaxN][MaxM];

int main()
{
	//freopen("F.in","r",stdin);
	//freopen("F.out","w",stdout);

	int i,j;

	scanf("%d%d%d",&n,&w,&h);
	ans = 0;

	for(i=0;i<=h;i++) f[1][i] = 1;
	for(i=2;i<=w;i++)
	{
		for(j=0;j<=n;j++)
		{
			f[i][j] = f[i][j-1] + f[i-1][j];
			if(j>h) f[i][j] -= f[i-1][j-h-1];
			f[i][j] = (f[i][j]%mod+mod) % mod;
			//printf("%d %d %d\n",i,j,f[i][j]);
		}
	}

	for(i=0;i<=n;i++)
		ans = (ans+f[w][i]) % mod;
	
	i = n/w;
	if(i>h) i = h;
	ans = (ans-i-1)%mod;
	ans = (ans+mod) % mod;

	printf("%d\n",(int)ans);

	return 0;
}
