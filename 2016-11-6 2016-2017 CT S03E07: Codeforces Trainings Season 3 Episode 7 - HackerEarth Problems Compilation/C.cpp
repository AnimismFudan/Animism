#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MaxN = 207;
const int mod = (int)1e9 + 7;

int n,m;
ll ans,C[MaxN][MaxN];
bool lnk[MaxN][MaxN];

inline ll Calc(int m, int n)
{
	if (n>m || n<0 || m<0) return 0;
	return C[m][n];
}

int main()
{

	int i,j,k,a,b;
	int n1,n2,n3;
	
	scanf("%d%d", &n, &m); ans = 0LL;
	for (i=1; i<=n; i++)
		for (j=1; j<=n; j++)
			lnk[i][j] = false;
	for (i=0; i<=n; i++)
	{
		C[i][0] = C[i][i] = 1;
		for (j=1; j<n; j++)
		{
			C[i][j] = (C[i-1][j-1] + C[i-1][j]);
			if (C[i][j] >= mod) C[i][j] -= mod;
		}
	}
	for (i=1; i<=m; i++)
	{
		scanf("%d%d", &a, &b);
		lnk[a][b] = lnk[b][a] = true;
	}
	
	for (i=1; i<=n; i++)
		for (j=1; j<=n; j++)
			if (i!=j && lnk[i][j])
			{
				n1 = n2 = n3 = 0;
				for (k=1; k<=n; k++)
				{
					if (lnk[i][k] && lnk[j][k]) n2++;
					if (lnk[i][k] && !lnk[j][k] && k!=j) n1++;
					if (lnk[j][k] && !lnk[i][k] && k!=i) n3++;
				}
				for (a=0; a<=3; a++)
					for (b=0; b<=2; b++)
						ans = (ans + (Calc(n2,a) * Calc(n1, 3-a) % mod) * (Calc(n2-a, b) * Calc(n3, 2-b) % mod) % mod) % mod;
				//printf("%d %d (%d %d %d) %lld\n", i, j, n1,n2,n3, ans);
			}
	
	ans %= mod;
	printf("%I64d\n", ans);
	
	return 0;
}
