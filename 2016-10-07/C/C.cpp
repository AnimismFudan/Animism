#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MaxN = (int)1e5 + 7;

int n,c[MaxN];
ll S,D,k,tot;

void Calc(int k)
{
	int i,j; j = 1<<30;
	for(i=1; i<=n; i++)
		j = min(j, (c[i]/k-1)/n);
	tot += j;
}

int main()
{
	int i;
	while(true)
	{
		scanf("%d",&n);
		if(n==0) break;
		S = tot = 0;
		for(i=1; i<=n; i++)
			scanf("%d",c+i), S += c[i];
		D = S;
		for(i=1; i<n; i++)
			if(c[i]!=c[i+1])
				D = __gcd(D, (ll)abs(c[i]-c[i+1]));
		if(D%n!=0) {printf("0\n"); continue;}
		D /= n;
		for(i=1; i<=n; i++)
			D = __gcd(D, (ll)c[i]);
		for(k=1; k*k<=D; k++)
			if(D%k==0)
			{
				Calc(k);
				if(k*k!=D) Calc(D/k);
			}
		printf("%lld\n",tot);
	}
	return 0;
}

