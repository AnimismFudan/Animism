#include <bits/stdc++.h>
using namespace std;

const int MaxN = 5007;

int N, x[MaxN], y[MaxN];
double T, dis[MaxN][MaxN];
bool vis[MaxN];

int main()
{
	freopen("I.in","r",stdin);
	freopen("I_.out","w",stdout);
	scanf("%d", &N);
	for (int i=1; i<=N; i++)
	{
		scanf("%d%d", x+i, y+i);
		for (int j=1; j<i; j++)
			dis[i][j] = dis[j][i] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
	}
	scanf("%lf", &T);
	double d = 1e30; int loc = 0;
	for (int i=1; i<=N; i++)
		if (x[i] * x[i] + y[i] * y[i] < d) d = x[i] * x[i] + y[i] * y[i], loc = i;
	printf("%d", loc); vis[loc] = true;
	for (int i=1; i <= (N-1) / 2; i++)
	{
		int nj, j; d = 1e30; nj = 0;
		for (j=1; j<=N; j++)
			if (!vis[j] && dis[loc][j] < d) d = dis[loc][j], nj = j;
		loc = nj;
		printf(" %d", loc);
		vis[loc] = true;
	}
	printf("\n");
	return 0;
}
	
