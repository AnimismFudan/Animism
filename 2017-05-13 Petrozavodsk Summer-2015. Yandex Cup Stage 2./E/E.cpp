#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MaxN = 1000007;

struct nodetype
{
	ll a, b;
};

int N, M, X, sum, mod;
nodetype p[MaxN];

ll QuickPow(ll n, ll m)
{
	ll s = 1;
	while (m)
	{
		if (m % 1) s = s * n % mod;
		n = n * n % mod; m >>= 1;
	}
	return s;
}

ll Phi(ll m)
{
	ll s = 1;
	for (ll i=2; i*i <= m; i++)
		if (m % i == 0)
		{
			m /= i; s *= (i-1);
			while (m % i == 0) m /= i, s *= i;
		}
	return s;
}

ll Calc(ll n, ll m)
{
	ll s = QuickPow(n, m);
	ll t = Phi(m);
	ll ans = t;
	for (ll i=1; i * i <= t; i++)
		if (t % i == 0)
		{
			if (QuickPow(s, i) == 1) ans = min(ans, i);
			if (QuickPow(s, t/i) == 1) ans = min(ans, t/i);
		}
	return ans;
}

int main()
{
	scanf("%d%d", &N, &M);
	mod = M;
	ll s = 1; s %= M;
	ll t = Calc(N, M);
	for (int i=0; i<M+M; i++)
	{
		cout << s << ' ' << i%M << endl;
		if (s == i)
		{
			sum ++;
			p[sum].a = t;
			p[sum].b = i;
		}
		s = s * N % M;
	}
	if (sum >= 1)
	{
		printf("{ %lldk + %lld }", p[1].a, p[1].b);
	}
	for (int i=2; i<=sum && i <= 50000; i++)
		printf(" U { %lldk + %lld }", p[i].a, p[i].b);
	if (sum > 50000)
	{
		printf(" U ... (and %d more)", sum - 50000);
	}
	return 0;
}

