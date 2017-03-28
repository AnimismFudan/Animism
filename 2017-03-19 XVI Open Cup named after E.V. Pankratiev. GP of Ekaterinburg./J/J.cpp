#include <bits/stdc++.h>
using namespace std;

const int MaxN = 200;

int N, M, a[MaxN][MaxN];
vector<int> iv[MaxN], dt[MaxN];
int f[MaxN]; bool vis[MaxN];

bool DFS(int x)
{
	int i, u;
	for (i=0; i<iv[x].size(); i++)
	{
		u = iv[x][i];
		if (!vis[u])
		{
			vis[u] = true;
			f[u] = f[x] + dt[x][i];
			if (!DFS(u)) return false;
		}
		else
		{
			if (f[u] != f[x] + dt[x][i])
				return false;
		}
	}
	return true;
}

int main()
{
	//freopen("J.in", "r", stdin);
	//freopen("J.out", "w", stdout);
	
	scanf("%d", &N);
	for (int i=1; i<=N; i++)
		for (int j=1; j<=N; j++)
			scanf("%d", &a[i][j]);
	scanf("%d", &M);
	for (int i=1; i<=M; i++)
	{
		int s,t,w;
		scanf("%d%d%d", &s, &t, &w);
		iv[s].push_back(t); dt[s].push_back(w);
		iv[t].push_back(s); dt[t].push_back(-w);
	}
	for (int i=1; i<=N; i++)
		if (!vis[i])
		{
			f[i] = 0;
			vis[i] = true;
			if (!DFS(i))
			{
				printf("Impossible\n");
				return 0;
			}
		}
	for (int i=1; i<=N; i++)
	{
		for (int j=1; j<=N; j++)
			printf("%d ", a[i][j] + f[j] - f[i]);
		printf("\n");
	}
	
	return 0;
}

