#include <bits/stdc++.h>
using namespace std;

const int MaxN = (int)2e5 + 7;

int n,m,a[MaxN];

int main()
{
	int i;
	scanf("%d", &n); m = n+n;
	for (i=1; i<=n; i++)
	{
		scanf("%d", a+i);
		a[i+n] = a[i];
	}
	for (i=2; i<m+m; i++)
		if (a[i-1] < a[i] && a[i] > a[i+1]) break;
	printf("%d %d %d\n",(i-2)%n+1,(i-1)%n+1,i%n+1);
	return 0;
}

