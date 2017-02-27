#include <bits/stdc++.h>
using namespace std;

const int MaxN = (int)1e6 + 7;

int N;
char str[MaxN];
double f[MaxN], sf[MaxN];

int main()
{
	freopen("foreign.in", "r", stdin);
	freopen("foreign.out", "w", stdout);
	
	int i; long long C, W;

	scanf("%s", str+1);
	N = strlen(str+1);
	
	C = W = 0LL;
	for (i=N; i>=1; i--)
	{
		if (str[i] == 'C')
		{
			C += (N-i+1);
			f[i] = sf[i+1] + W;
		}
		else
		{
			W += (N-i+1);
			f[i] = sf[i+1] + C;
		}
		f[i] /= (N-i+1);
		sf[i] = sf[i+1] + f[i];
		//cout << i << ' ' << (N-i+1) - f[i] << ' ' << f[i] << endl;;
	}
	
	printf("%.12lf\n", f[1]);
	
	return 0;
}

