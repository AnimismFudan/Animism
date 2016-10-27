#include <bits/stdc++.h>
using namespace std;

const int MaxN = 207;

struct nodetype
{
	int l,r;
};

int n,m,s[MaxN],d[MaxN],l[MaxN],r[MaxN];
nodetype t[MaxN];

bool Comp(const nodetype a, const nodetype b)
{
	return (a.l < b.l);
}

int main()
{
	int i,j;
	scanf("%d", &n); m = 1;
	t[m].l = 0; t[m].r = 0;
	for (i=1; i<=n; i++)
	{
		scanf("%d%d", s+i, d+i);
		for (j=1; j<=m; j++)
		{
			if ((t[j].l <= s[i]+d[i]-1 && s[i] <= t[j].r) || (t[j].l <= s[i]+d[i]-1 && s[i] <= t[j].r)) break;
		}
		if (j>m)
		{
			l[i] = s[i]; r[i] = s[i]+d[i]-1;
			m++; t[m].l = l[i]; t[m].r = r[i];
			sort(t+1, t+m+1, Comp);
		}
		else
		{
			for (j=1; j<m; j++)
				if (t[j].r + d[i] < t[j+1].l) break;
			l[i] = t[j].r + 1;
			r[i] = t[j].r + d[i];
			m++; t[m].l = l[i]; t[m].r = r[i];
			sort(t+1, t+m+1, Comp);
		}
	}
	for (i=1; i<=n; i++)
		printf("%d %d\n",l[i],r[i]);	
	
	return 0;
}

