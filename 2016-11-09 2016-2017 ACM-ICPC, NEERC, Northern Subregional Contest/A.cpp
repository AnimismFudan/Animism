#include <bits/stdc++.h>
using namespace std;

int w,h,ax,ay,bx,by;

int main()
{
	freopen("anniversary.in", "r", stdin);
	freopen("anniversary.out", "w", stdout);
	
	scanf("%d%d%d%d%d%d", &w, &h, &ax, &ay, &bx, &by);
	if (ax == bx)
		printf("%d %d %d %d\n", 0, ay, w, by);
	else
		printf("%d %d %d %d\n", ax, 0, bx, h);
	return 0;
}

