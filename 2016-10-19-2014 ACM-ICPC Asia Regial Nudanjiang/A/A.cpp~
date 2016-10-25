#include <bits/stdc++.h>
using namespace std;

const int MaxN = 70;

int T,n,m,a[MaxN],b[MaxN];
long long s1,s2;

int main()
{
	int i;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &m); n--;
		s1 = s2 = 0;
		for (i=1; i<=n; i++)
			scanf("%d", a+i), s1 += a[i];
		if (s1%n == 0) s1 = s1/n-1;
		else s1 = s1/n;
		for (i=1; i<=m; i++)
			scanf("%d", b+i), s2 += b[i];
		s2 = s2 / m + 1;
		printf("%lld %lld\n", s2, s1);
//		cout << s2 << ' ' << s1 << endl;
	}
	return 0;
}
