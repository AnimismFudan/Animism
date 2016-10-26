#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MaxN = (int)2e5 + 7;

int n; ll s,r,T,D;
int l[MaxN],t[MaxN];
int d[MaxN],d_[MaxN];

int main()
{
	int i,j;
	scanf("%d", &n);
	scanf("%I64d", &r);
	for (i=1; i<=n; i++)
		scanf("%d", l+i);
	for (i=1; i<=n; i++)
		scanf("%d", t+i);
	
	for (i=1; i<=n; i++)
		if (t[i] < l[i])
		{
			printf("-1\n");
			return 0;
		}
		else
		{
			d[i] = max(l[i] + l[i] - t[i], 0);
			d_[i] = d[i];
		}
	
	D = 0;
	for (i=1; i<=n; i++)
	{
		if (D >= l[i]) D -= l[i];
		else
		{
			if (d[i] <= D) D = 0;
			else
			{
				d[i] -= D;
				s += d[i]/r;
				if (d[i] % r != 0)
				{
					s ++;
					D = r - d[i]%r;
				}
				else D = 0;
			}
		}
	}
	printf("%I64d\n", s);
	if (s != 0 && s <= (int)1e5)
	{
		D = T = 0;
		for (i=1; i<=n; i++)
		{
			if (D >= l[i]) D -= l[i], T += l[i];
			else
			{
				d[i] = d_[i];
				if (d[i] <= D) {T += l[i] + l[i] - D; D = 0;}
				else
				{
					T += D; d[i] -= D;
					T += (t[i] - l[i]) * 2;
					for (j=1; j<=d[i]/r; j++)
					{
						printf("%I64d ", T); T += r;
					}
					if (d[i] % r != 0)
					{
						printf("%I64d ", T);
						T += d[i]%r;
						D = r - d[i]%r;
					}
					else D = 0;
				}
			}	
		}
		printf("\n");
	}
	return 0;
}

