#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll L; int N;

inline ll Calc(ll m)
{
	ll s = 0, t = 2;
	while (t <= m)
	{
		s += (m/t);
		t *= 2;
	}
	return s;
}

bool C(ll m, ll n)
{
	//cout << m << ' ' << n << ' ' << Calc(m) << ' ' << Calc(n) << ' ' << Calc(m-n) << endl;
	return Calc(m) == Calc(n) + Calc(m-n);
}

int main()
{
	cin >> L; scanf("%d", &N);
	
	bool res = false;
	
	for (int i=1; i<=N; i++)
	{
		int x, y, z;
		scanf("%d%d", &y, &z);
		
		y --; z --;
		x = L - 1 - y;
		y = y - z;
		
		//cout << x << ' ' << y << ' ' << z << ' ' << (C(x+y+z, x) & C(y+z, z)) << endl;
		
		res ^= C(x+y+z, x) & C(y+z, z);
	}
	
	if (!(L&1)) res ^= true;
	
	if (res) printf("Iori\n");
	else printf("Yayoi\n");
	
	return 0;
}

