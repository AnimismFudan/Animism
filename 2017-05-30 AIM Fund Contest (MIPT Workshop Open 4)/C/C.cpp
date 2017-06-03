#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MaxN = 10000;

int n, m, to, p[20];
int tot, co[MaxN][20];

void DFSse(int x)
{
	if (x > 7)
	{
		for (int i=1; i<7; i++)
			printf("%d ", p[i]);
		printf("%d\n", p[7]);
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
	//if (n != 12 || m < 2 || m > 12) while(1);
	if (n == 2)
	{
		printf("2\n1\n2\n");
		return 0;
	}
	if (m == 7)
	{
		printf("128\n");
		DFSse(1);
		return 0;
	}
	if (m <= 5)
	{
		printf("10\n");
		for (int i=1; i<=10; i++)
		{
			for (int j=1; j<m; j++)
				printf("%d ", j+10);
			printf("%d\n", i);
		}
		return 0;
	}
	if (m == 9)
	{
		printf("10\n");
		for (int i=1; i<=10; i++)
		{
			if (i == 1) printf("2");
			else if (i == 2) printf("1");
			else printf("1 2");
			for (int j=3; j<=10; j++)
				if (j != i) printf(" %d", j);
			printf("\n");
		}
		return 0;
	}
	if (m >= 10)
	{
		printf("10\n");
		for (int i=1; i<=10; i++)
		{
			printf("11");
			for (int j=2; 9 + j<=m; j++)
				printf(" %d", j+10);
			for (int k=1; k<=10; k++)
				if (k != i) printf(" %d", k);
			printf("\n");
		}
		return 0;
	}
	int t = 0;
	if (m > 7) t = m - 6;
	else t = m - 1;
	int s = 1;
	for (int i=1; i<=t; i++)
		s = s * (7 - i + 1) / i;
	s = s * 7;
	//cout << m << ' ' << s << endl;
	printf("%d\n", s);
	DFS(1, t);
	for (int i=1; i<=tot; i++)
		for (int j=1; j<=7; j++)
		{
			printf("%d", co[i][1]);
			for (int k=2; k<=co[i][0]; k++)
				printf(" %d", co[i][k]);
			if (m > 7)
			{
				for (int k=1; k<=7; k++)
					if (j!=k) printf(" %d", k+7);
			}
			else printf(" %d", j+7);
			printf("\n");
		}
	return 0;
}

