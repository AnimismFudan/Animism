#include <bits/stdc++.h>
using namespace std;

int a,b,c,d,s;

int Calc(int a, int b, int c, int d)
{
	int s = 0;
	if (a<c || b<d) return 1<<30;
	while (c<a) s++, c<<=1;
	while (d<b) s++, d<<=1;
	return s;
}

int main()
{
	freopen("folding.in", "r", stdin);
	freopen("folding.out", "w", stdout);
	
	scanf("%d%d", &a, &b);
	scanf("%d%d", &c, &d);
	s = 1<<30;
	
	s = min(s, Calc(a,b,c,d));
	s = min(s, Calc(b,a,c,d));
	
	if (s == (1<<30)) printf("-1\n");
	else printf("%d\n",s);
	
	return 0;
}

