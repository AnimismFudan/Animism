#include <bits/stdc++.h>
using namespace std;

#define ll long long

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
	ll n,m,a,k,s;
	cin>>n; m = 0;
	for(a=1;a<n;a++)
	{
		s = QckM(a,n,n); k = 1;
		while(s!=a)
			s = QckM(s,n,n), k ++;
		if(k>m) m = k;
	}
	cout<<m<<endl;
	return 0;
}
		
