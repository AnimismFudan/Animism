#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mod = (int)1e9 + 7;

int n,a,b,x;
int m,p[20]; bool cho[20];
int l,d[20],o2,f2,s; bool ch[20];
ll ans,tmp;

void GetPrime()
{
	int i; m = 0;
	for (i=2; i*i <= x; i++)
		if (x%i == 0)
		{
			m++; p[m] = 1;
			while (x%i==0)
				x /= i, p[m] *= i;
		}
	if (x>1)
	{
		m++; p[m] = x;
	}
	/*
	for (int i=1; i<=m; i++)
		printf("%d ", p[i]);
	printf("\n");
	*/
}

void Calc(int x)
{
	if (x>l)
	{
		//cout << "calc: " << f2 << ' ' << o2 << endl;
		s += f2*(b/o2 - (a-1)/o2);
		return;
	}
	ch[x] = false;
	Calc(x+1);
	
	o2 = o2 * d[x];
	f2 = -f2;
	ch[x] = true;
	Calc(x+1);
	o2 = o2 / d[x];
	f2 = -f2;
	ch[x] = false;
}

inline ll C(int m, int n)
{
	int i; ll s = 1;
	for (i=0; i<n; i++)
		s = s * (m-i) % mod;
	s = s * tmp % mod;
	return s;
}

void DFS(int x)
{
	if (x>m)
	{
		int i,f; f = 1; l = 0;
		for (i=1; i<=m; i++)
			if (cho[i])
			{
				f = -f; l++;
				d[l] = p[i];
				ch[l] = false;
			}
		o2 = f2 = 1; s = 0;
		Calc(1);
		//cout << cho[1] << ' ' << cho[2] << ' ';
		//cout << s << ' ' << C(s+n-1, n) << endl;
		ans = (ans + f * C(s+n-1, n)) % mod;
		return;
	}
	cho[x] = false;
	DFS(x+1);
	cho[x] = true;
	DFS(x+1);
	cho[x] = false;
}

inline ll QckM(ll a, ll b)
{
	ll s = 1;
	while (b)
	{
		if (b&1) s = s*a % mod;
		a = a*a % mod; b>>=1;
	}
	return s;
}

int main()
{
	scanf("%d%d%d%d", &n, &a, &b, &x);
	tmp = 1;
	for (int i=1; i<=n; i++)
		tmp = tmp * i % mod;
	tmp = QckM(tmp, mod-2);
	GetPrime();
	ans = 0LL;
	DFS(1);
	ans = (ans % mod + mod) % mod;
	printf("%I64d\n", ans);
	return 0;
}
