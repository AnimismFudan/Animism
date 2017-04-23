#include <bits/stdc++.h>
using namespace std;

const int MaxN = 1007;

int Q, N, M, A, B;
char doc[MaxN][MaxN], seal[MaxN][MaxN];
vector<int> iv[2];

int main()
{
	int i, j, x, y;

	scanf("%d", &Q);
	while (Q--)
	{
		scanf("%d%d", &N, &M);
		scanf("%d%d", &A, &B);
		for (i=1; i<=N; i++)
			scanf("%s", doc[i] + 1);
		for (i=1; i<=A; i++)
			scanf("%s", seal[i] + 1);
		x = y = 0;
		iv[0].clear();
		iv[1].clear();
		for (i=1; i<=A; i++)
			for (j=1; j<=B; j++)
				if (seal[i][j] == 'x')
				{
					if (x == 0 && y == 0)
						x = i, y = j;
					else
					{
						iv[0].push_back(i-x);
						iv[1].push_back(j-y);
					}
				}
		bool flag = true;
		for (i=1; flag && i<=N; i++)
			for (j=1; flag && j<=M; j++)
				if (doc[i][j] == 'x')
				{
					doc[i][j] = '.';
					for (int k=0; k<iv[0].size(); k++)
					{
						int nx = i + iv[0][k];
						int ny = j + iv[1][k];
						if (nx < 0 || nx > N || ny < 0 || ny > M || doc[nx][ny] == '.')
						{
							flag = false;
							break;
						}
						else doc[nx][ny] = '.';
					}
				}
		if (flag) printf("TAK\n");
		else printf("NIE\n");
	}
	return 0;
}

