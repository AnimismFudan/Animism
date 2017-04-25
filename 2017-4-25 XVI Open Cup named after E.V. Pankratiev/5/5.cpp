#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MaxN = 57;
const int MaxM = 207;
const int mod = (int)1e9 + 7;

int N, P, M;
ll f[MaxN][MaxM], g[MaxN][MaxM];

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int i, j, l1, a, b;
	
	scanf("%d%d%d", &N, &P, &M);
	
	for (i=0; i < P && i < 10; i++) f[1][i] = g[1][i] = 1;
	for (i=10; i < P && i < 100; i++) f[2][i] = g[2][i] = 1;
	for (i=100; i < P; i++) f[3][i] = g[3][i] = 1;
	
	for (i=1; i<=N; i++)
		for (j=0; j<P; j++)
		{
			if (i > 2)
			{
				f[i][j] = (f[i][j] + f[i-2][j]) % mod; //(j)
				g[i][j] = (g[i][j] + f[i-2][j]) % mod;
			}
			
			for (a=0; a<P; a++)
			{
				b = (P + j - a) % P; // j = a+b
				//cout << '+' << a << ' ' << b << ' ' << j << endl;
				for (l1 = 1; l1 + 1 < i; l1++)
					f[i][j] = (f[i][j] + g[l1][a] * f[i-1-l1][b]) % mod;
				b = (j + a) % P; // j = b-a
				//cout << '-' << a << ' ' << b << ' ' << j << endl;
				for (l1 = 1; l1 + 1 < i; l1++)
					f[i][j] = (f[i][j] + g[l1][a] * f[i-1-l1][b]) % mod;
			}
			//cout << i << ' ' << j << ' ' << f[i][j] << endl;
		}
	printf("%lld\n", f[N][M] % mod);
	
	return 0;
}

