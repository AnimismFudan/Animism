#include <bits/stdc++.h>
using namespace std;

const int MaxN = 1007;
const int MaxM = 207;

int N, M, d[MaxN][MaxM];
int sd[MaxN][MaxM];
int cnt[MaxN][MaxM];

int main()
{
	int i, j, k;
	int ansi, ansk;
	ansi = ansk = 0;
	
	scanf("%d%d", &N, &M);
	for (i=1; i<=N; i++)
	{
		for (j=1; j<=M; j++)
			scanf("%d", &d[i][j]);
		for (j=1; j<=M; j++)
			sd[i][j] = d[i][j] - d[i][1];
	}
	
	for (i=1; i<=N; i++)
	{
		for (j=1; j<=N; j++)
		{
			int x = 0;
			for (k=1; k<=N; k++)
				if (sd[i][k] != sd[j][k])
				{
					if (x == 0 && sd[i][k] + 1 == sd[j][k] ) x = k;
					else break;
				}
			if (k>N)
				cnt[i][x] ++;
		}
		k = 1;
		for (j=1; j<=M; j++)
			if (cnt[i][0] + cnt[i][j] > cnt[i][0] + cnt[i][k]) k = j;
		if (cnt[i][0] + cnt[i][k] > cnt[ansi][0] + cnt[ansi][ansk])
			ansi = i, ansk = k;
	}
	
	printf("%d\n", cnt[ansi][0] + cnt[ansi][ansk]);
	for (i=1; i<=N; i++)
	{
		for (j=1; j<=M; j++)
			if (j == ansk && sd[i][j] == sd[ansi][j]+1) continue;
			else if (j != ansk && sd[i][j] == sd[ansi][j]) continue;
			else break;
		
		if (j>M) printf("%d ", i);
	}
	for (i=1; i<=N; i++)
	{
		for (j=1; j<=M; j++)
			if (sd[i][j] != sd[ansi][j]) break;
		if (j > M) printf("%d ", i);
	}
	printf("\n");
	return 0;
}

