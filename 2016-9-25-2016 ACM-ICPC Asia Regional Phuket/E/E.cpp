#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
int powmod(int a , int b)
{
	int r = 1;
	while(b)
	{
		if(b & 1)r = (long long)r * a % mod;
		a = (long long)a * a % mod;
		b >>= 1;
	}
	return r;
}
int fac[50001] , rfac[50001];

int comb(int n , int m)
{return (long long)fac[n] * rfac[n - m] % mod * rfac[m] % mod;}

int n , k;
map<int , int> h;

int f[2][1001];

int main()
{
	fac[0] = rfac[0] = 1;
	for(int i = 1 ; i <= 50000 ; i++)fac[i] = (long long)fac[i - 1] * i % mod;
	rfac[50000] = powmod(fac[50000] , mod - 2);
	for(int i = 50000 - 1 ; i >= 1 ; i--)
		rfac[i] = (long long)rfac[i + 1] * (i + 1) % mod;
	int T;
	scanf("%d" , &T);
	for(int t = 1 ; t <= T ; t++)
	{
		h.clear();
		scanf("%d%d" , &n , &k);
		for(int i = 1 ; i <= n ; i++)
		{
			int htmp;scanf("%d" , &htmp);
			h[htmp]++;
		}
		int p = 0;
		int swi = 0;
		for(pair<int,int> x : h)
		{
			for(int clearind = 0 ; clearind <= k ; clearind++)
				f[swi ^ 1][clearind] = 0;
			int num = x.second;
			if(p == 0)
				f[swi ^ 1][0] = 1;
			else
			{
				for(int newkill = 0 ; newkill <= num ; newkill++)
				{
					int coef = comb(newkill + p - 1 , p - 1);
					//printf("	num = %d, newkill = %d , coef = %d\n" , num , newkill , coef);
					for(int oldkill = 0 ; oldkill + newkill <= k ; oldkill++)
					{
						f[swi ^ 1][oldkill + newkill] += (long long)f[swi][oldkill] * coef % mod;
						f[swi ^ 1][oldkill + newkill] %= mod;
					}
				}
			}
			p += num;
			swi ^= 1;
		}
		printf("Case %d: %d\n" , t , f[swi][k]);
	}
	return 0;
}
