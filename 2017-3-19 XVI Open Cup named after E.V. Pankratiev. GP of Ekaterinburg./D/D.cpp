#include <bits/stdc++.h>
using namespace std;

const int MaxN = (int)1e5 + 7;
const int mod = (int)1e9 + 7;

#define ll long long

int N;
ll f[MaxN], sf[MaxN];

int main()
{
	scanf("%d", &N);
	f[0] = sf[0] = 1;
	for (int i=1; i<=N; i++)
	{
		f[i] = sf[i/2];
		sf[i] = sf[i-1] + f[i];
		if (sf[i] >= mod) sf[i] -= mod;
	}
	printf("%lld\n", f[N]);
	return 0;
}

