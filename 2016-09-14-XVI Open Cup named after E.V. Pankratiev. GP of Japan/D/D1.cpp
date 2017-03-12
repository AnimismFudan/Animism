#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll n,m,phin,res;

inline ll Gcd(ll a,ll b)
{
	ll d;
	while(b)
	{
		d = a;
		a = b;
		b = d%b;
	}
	return a;
}

inline ll GetPhi(ll d)
{
	ll i,j,k;
	j = 1; k = d;
	for(i=2;i*i<=k;i++)
		if(k%i==0)
		{
			k/=i; j*=(i-1);
			while(k%i==0)
				k/=i, j*=i;
		}
	if(k>1) j*=(k-1);
	return j;
}

inline ll QckM(ll a,ll b,ll mod)
{
	ll s = 1, t = a;
	while(b)
	{
		if(b&1) s = s*t%mod;
		t = t*t%mod; b >>= 1;
	}
	return s;
}

int main()
{
	ll i;
	freopen("D1.out","w",stdout);
	for(n=1;n<=10000;n++)
	{
	//cin>>n;
	
	phin = GetPhi(n);
	//cout << n << ' '<< phin<<endl;
	if(Gcd(n,phin)!=1)
	{
		printf("-1\n");
		continue;
		//return 0;
	}
	m = res = GetPhi(phin);
	for(i=1;i*i<=m;i++)
	{
		if(m%i==0)
		{
			if(QckM(n,i,phin)==1) res = min(res,i);
			if(QckM(n,m/i,phin)==1) res = min(res,m/i);
		}
	}
	
	cout<<res<<endl;
	}
	return 0;
}

