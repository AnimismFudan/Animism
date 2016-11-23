#include <bits/stdc++.h>
using namespace std;

const int MaxN = 20;
const int MaxM = 107;

int T,N,M,cnt[MaxN];
double p[MaxN];
double die[MaxN][MaxM];

inline double quickpow(double a, int b)
{
	double s = 1.0;
	while (b)
	{
		if (b&1) s = s*a;
		a = a*a; b>>=1;
	}
	return s;
}

int main()
{
	
	int i,j,k; double sum, temp, temp1, temp2;
	
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &N); M = 100;
		for (i=1; i<=N; i++)
		{
			scanf("%d%lf", cnt+i, p+i);
			p[i] = 1.0-p[i];
		}
		for (i=1; i<=N; i++)
		{
			temp = 1.0;
			for (j=0; j<=M; j++)
			{
				die[i][j] = 1 - temp;
				temp *= (1-p[i]);
			}
		}
		for (i=1; i<=N; i++)
		{
			sum = 0.0;
			for (j=1; j<=M; j++)
			{
				temp = 1 - quickpow(die[i][j], cnt[i]);
				temp1 = temp2 = 1.0;
				for (k=1; k<=N; k++)
					if (k!=i)
					{
						temp1 *= quickpow(die[k][j], cnt[k]);
						temp2 *= quickpow(die[k][j-1], cnt[k]);
					}
				sum += temp * (temp1 - temp2);
			}
			if (N==1) sum = 1 - quickpow(die[i][j], cnt[i]);
			if (i!=N) printf("%.6lf ", sum);
			else printf("%.6lf", sum);
		}
		printf("\n");
	}
	
	return 0;
}
