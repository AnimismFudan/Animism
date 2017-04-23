#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MaxN = 1007;
const int MaxM = 207;
const int mod1 = 999973;
const ll mod2 = 10000000007;

int N, M, d[MaxN][MaxM];
int sd[MaxN][MaxM];
int fir[mod1], nxt[MaxN];
ll has[MaxN]; int cnt[MaxN], tot, mask[MaxN];
int hs1[MaxN]; ll hs2[MaxN];

void Add(int x, int h1, ll h2)
{
	int i;
	hs1[x] = h1; hs2[x] = h2;
	for (i=fir[h1]; i; i = nxt[i])
		if (has[i] == h2)
		{
			mask[x] = i;
			cnt[i] ++;
			return;
		}
	tot++; has[tot] = h2; nxt[tot] = fir[h1]; fir[h1] = tot;
	mask[x] = tot; cnt[tot] = 1;
	return;
}

int main()
{
	int i, j;

	scanf("%d%d", &N, &M);
	for (i=1; i<=N; i++)
	{
		for (j=1; j<=M; j++)
			scanf("%d", &d[i][j]);
		int hash1 = 0; ll hash2 = 0;
		for (j=1; j<=M; j++)
		{
			sd[i][j] = d[i][j] - d[i][1];
			hash1 = (hash1 * 27 + sd[i][j]) % mod1;
			hash2 = (hash2 * 197 + sd[i][j]) % mod2;
			Add(i, hash1, hash2);
		}
	}
	for (i=1; i<=N; i++)
	{
		int hash1 = 0; ll hash2 = 0;
		int k1 = 0; ll k2 = 0;
		for (j=M; j>=1; j--)
		{
			hash1 = (hs[i] + k1) % mod1;
			hash2 = (hs[i] + k2) % mod2;
			
	}
	return 0;
}

