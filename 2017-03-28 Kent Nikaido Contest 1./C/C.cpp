#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MaxN = 10;

int N = 7;
ll C[MaxN], deg[MaxN], X[MaxN], Y[MaxN];
bool vis[MaxN];

void DFS(int x)
{
	if (vis[x]) return;
	vis[x] = true;
	if (X[x]) DFS((x+N-2) % N + 1);
	if (Y[x]) DFS(x % N + 1);
}

bool Check(ll d)
{
	X[1] = d; Y[1] = deg[1] - X[1];
	int i = 1, j = 0;
	
	ll a = 1, b = 0;
	
	while (j < N)
	{
		int k = i-1;
		if (k==0) k = 7;
		
		a = -1; b = deg[k] - b;
		
		int fk = k;
		
		k = k-1;
		if (k==0) k = 7;
		Y[k] = deg[fk] - X[i];
		
		a = 1; b = deg[k] - b;
		X[k] = deg[k] - Y[k];
		
		i = k;
		j ++;
	}
	
	for (int i=1; i<=N; i++)
		if (X[i] < 0 || Y[i] < 0) return false;
	
	for (int i=1; i<=N; i++)
		vis[i] = false;
	DFS(1);
	for (int i=1; i<=N; i++)
		if (!vis[i] && deg[i] != 0)
			return false;
	return true;
}

int main()
{
	for (int i=1; i<=N; i++)
		cin >> C[i];
	deg[1] = C[1] - 1;
	for (int i=2; i<=N; i++)
		deg[i] = C[i];
	
	ll minnum, maxnum, a, b;
	
	minnum = 0; maxnum = 1LL << 60;
	a = 1; b = 0;
	
	int i = 1, j = 0;
	
	while (j < N)
	{
		int k = i-1;
		if (k==0) k = 7;
		
		a = -1; b = deg[k] - b;
		maxnum = min(maxnum, b);
		
		k = k-1;
		if (k==0) k = 7;
		
		a = 1; b = deg[k] - b;
		minnum = max(minnum, -b);
		
		i = k;
		j ++;
	}
	
	if (a != 1 || b != 0 || minnum > maxnum)
	{
		printf("NO\n");
		return 0;
	}
	else
	{
		if (maxnum - minnum > 1)
			printf("YES\n");
		else if (Check(maxnum) || Check(minnum))
			printf("YES\n");
		else printf("NO\n");	
	}
	
	return 0;
}

