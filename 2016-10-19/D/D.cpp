#include <bits/stdc++.h>
using namespace std;

const int MaxN = 51;
const int MaxM = 2501;

int n,m,t,T;
double res,ans,p[MaxM],f[MaxM][MaxN][MaxN];

void Pretreat()
{
	int i,j,k; t = n*m;
	for (k=1; k<=t; k++)
		for (i=1; i<=n; i++)
			for (j=1; j<=m; j++)
				f[k][i][j] = 0.0;
	f[1][1][1] = 1.0;
	for (k=1; k<=t; k++)
		for (i=1; i<=n; i++)
			for (j=1; j<=m; j++)
			{
				//printf("%d %d %d %lf\n",k,i,j,f[k][i][j]);
				if (i==n && j==m) continue;
				if (f[k][i][j] > 0.5)
				{
					if (i*j < k) f[k+1][i][j] += f[k][i][j] * (i*j - k);
					if (i<n) f[k+1][i+1][j] += f[k][i][j] * (n-i) * j;
					if (j<m) f[k+1][i][j+1] += f[k][i][j] * i * (m-j);
					if (i<n && j<m) f[k+1][i+1][j+1] += f[k][i][j] * (n-i) * (m-j);
				}
			}
	res = ans = 0.0;
	while (f[t][n][m] < 0.5) t--;
	for (i=1; i<=t; i++)
		ans += i * f[i][n][m] * p[t - i + 1],
		res += f[i][n][m] * p[t - i + 1];
	printf("%.10lf\n", ans / res);
}

int main()
{
	int i; p[0] = 1.0;
	for (i=1; i<=2500; i++)
		p[i] = p[i-1] * i;
	scanf("%d", &T);
	while (T--)
	{
		scanf ("%d%d", &n, &m);
		Pretreat();
	}
	return 0;
}

