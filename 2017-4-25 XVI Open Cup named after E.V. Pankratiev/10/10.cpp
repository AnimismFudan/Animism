#include <bits/stdc++.h>
using namespace std;

int N, X, Y;
int x, y;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	scanf("%d", &N);
	scanf("%d%d", &X, &Y);
	for (int i=1; i<=N; i++)
	{
		scanf("%d%d", &x, &y);
		x -= X; y -= Y;
		int t = x;
		x = x + y; y = -t;
		printf("%d %d\n", x+X, y+Y);
	}
	return 0;
}

