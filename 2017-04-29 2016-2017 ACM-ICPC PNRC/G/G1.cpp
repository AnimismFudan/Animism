#include <bits/stdc++.h>
using namespace std;

int N, M, ans;
char mp[10][10];
bool vis[10][10];
int tmp[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

void FloodFill(int x, int y)
{
	int i, nx, ny;
	vis[x][y] = true;
	for (i=0; i<4; i++)
	{
		nx = x + tmp[i][0];
		ny = y + tmp[i][1];
		if (nx < 1 || nx > N || ny < 1 || ny > M) continue;
		if (!vis[nx][ny] && mp[nx][ny] == 'L')
			FloodFill(nx, ny);
	}
	return;
}	

void DFS(int x, int y)
{
	//cout << x << ' ' << y << endl;
	if (x == N+1)
	{
		int tot = 0;
		for (int i=1; i<=N; i++)
			for (int j=1; j<=M; j++)
				vis[i][j] = false;
		for (int i=1; i<=N; i++)
			for (int j=1; j<=M; j++)
				if (!vis[i][j] && mp[i][j] == 'L')
				{
					FloodFill(i, j); tot++;
				}
		if (tot > ans) ans = tot;
		return;
	}
	if (y == M+1) DFS(x+1, 1);
	else
	{
		if (mp[x][y] == 'C')
		{
			mp[x][y] = 'L';
			DFS(x, y+1);
			mp[x][y] = 'W';
			DFS(x, y+1);
			mp[x][y] = 'C';
		}
		else DFS(x, y+1);
	}
	return;
}

int main()
{
	freopen("G.in", "r", stdin);
	freopen("G1.out", "w", stdout);
	scanf("%d%d", &N, &M);
	for (int i=1; i<=N; i++)
		scanf("%s", mp[i] + 1);
	DFS(1, 1);
	printf("%d\n", ans);
	return 0;
}

