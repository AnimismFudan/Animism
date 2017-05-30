#include <bits/stdc++.h>
using namespace std;

const int MaxN = 10000;

int n, m, to, p[10];
int tot, co[MaxN][10];

void DFSse(int x)
{
	if (x > 7)
	{
		for (int i=1; i<=7; i++)
			printf("%d ", p[i]);
		printf("\n");
		return;
	}
	p[x] = x + x - 1;
	DFSse(x+1);
	p[x] = x + x;
	DFSse(x+1);
}

void DFS(int x, int t)
{
	if (x > 7)
	{
		if (t == 0)
		{
			tot++;
			for (int i=0; i<=p[0]; i++)
				co[tot][i] = p[i];
		}
		return;
	}
	DFS(x+1, t);
	p[++p[0]] = x;
	DFS(x+1, t-1);
	p[0]--;
}

int main()
{
	scanf("%d%d", &n, &m);
	if (m == 7)
	{
		printf("128\n");
		DFSse(1);
		return 0;
	}
	int t = 0;
	if (m > 7) t = m - 6;
	else t = m - 1;
	int s = 1;
	for (int i=1; i<=t; i++)
		s = s * (7 - i + 1) / i;
	s = s * 14;
	if (m == 2 || m == 12) s /= 2;
	//cout << m << ' ' << s << endl;
	printf("%d\n", s);
	DFS(1, t);
	for (int i=1; i<=tot; i++)
		for (int j=1; j<=7; j++)
		{
			for (int k=1; k<=co[i][0]; k++)
				printf("%d ", co[i][k]);
			if (m > 7)
			{
				for (int k=1; k<=7; k++)
					if (j!=k) printf("%d ", k+7);
			}
			else printf("%d ", j+7);
			printf("\n");
		}
	if (m == 2 || m == 12) return 0;
	for (int i=1; i<=tot; i++)
		for (int j=1; j<=7; j++)
		{
			for (int k=1; k<=co[i][0]; k++)
				printf("%d ", co[i][k]+7);
			if (m > 7)
			{
				for (int k=1; k<=7; k++)
					if (j!=k) printf("%d ", k);
			}
			else printf("%d ", j);
			printf("\n");
		}
	return 0;
}

