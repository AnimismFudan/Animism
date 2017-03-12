#include <bits/stdc++.h>
using namespace std;

const int MaxN = (int)2e5 + 7;

int n,odd[MaxN],even[MaxN];
int idx,l,r,p[2][MaxN][2];

void Init()
{
	int i,j;
	scanf("%d", &n);
	for (i=1; i<=n; i++)
	{
		scanf("%d", &j);
		if (j&1) odd[++odd[0]] = j;
		else even[++even[0]] = j;
	}
	sort(odd+1, odd+1+odd[0]);
	sort(even+1, even+1+even[0]);
	for (i=1; i<=odd[0]; i++)
		if (l!=0 && p[1][l][1] + 2 == odd[i])
			p[1][l][1] += 2;
		else
		{
			l++;
			p[1][l][0] = p[1][l][1] = odd[i];
		}
	for (i=1; i<=even[0]; i++)
		if (r!=0 && p[0][r][1] + 2 == even[i])
			p[0][r][1] += 2;
		else
		{
			r++;
			p[0][r][0] = p[0][r][1] = even[i];
		}
/*
	for (i=1; i<=r; i++)
		printf("%d - %d\n", p[0][i][0], p[0][i][1]);
	printf("\n");
	for (i=1; i<=l; i++)
		printf("%d - %d\n", p[1][i][0], p[1][i][1]);
	printf("\n");
*/
}

void Print(int a, int b)
{
	if (idx != 0) printf(",");
	idx++;
	if (p[a][b][0] == p[a][b][1])
		printf("%d",p[a][b][0]);
	else
	{
		printf("%d",p[a][b][0]);
		printf("%c",a?'#':'%');
		printf("%d",p[a][b][1]);
	}
}

inline int Calc(int d)
{
	int s = 0;
	while(d) s++,d/=10;
	return s;
}

void Solve()
{
	int a,b,c,d; bool flg, tmp1;
	a = b = 1;
	while (a<=r && b<=l)
	{
		c = a; d = b;
		if (abs(p[0][a][0] - p[1][b][0]) == 1 || abs(p[0][a][0] - p[1][b][0]) == 3)
		{
			flg = true;
			if (abs(p[0][a][0] - p[1][b][0]) == 3)
			{
				if (p[0][a][0] < p[1][b][0] && p[0][a][0] == p[0][a][1])
				{
					Print(0,a); a++; continue;
				}
				if (p[0][a][0] > p[1][b][0] && p[1][b][0] == p[1][b][1])
				{
					Print(1,b); b++; continue;
				}
				tmp1 = true;
			}
			else tmp1 = false;
			while (flg)
			{
				if ( abs(p[0][a][1] - p[1][b][1]) == 1) break;
				if (p[0][a][1] < p[1][b][1])
				{
					if ( a<=r && p[0][a+1][0] == p[0][a][1] + 4)
						a++;
					else flg = false;
				}
				else if(p[0][a][1] > p[1][b][1])
				{
					if ( b<=l && p[1][b+1][0] == p[1][b][1] + 4)
						b++;
					else flg = false;
				}
			}
			if (flg)
			{
				int st = min(p[0][c][0], p[1][d][0]);
				if (tmp1)
				{
					if (idx!=0) printf(",");
					idx++;
					printf("%d",st);
					st += 2;
				}
				while (c<=a && d<=b)
				{
					if (idx!=0) printf(",");
					idx++;
					printf("%d-", st);
					st = min(p[0][c][1], p[1][d][1]) + 1;
					printf("%d", st); st += 2;
					if (st > p[0][c][1]) c++;
					if (st > p[1][d][1]) d++;
				}
			}
			else if( abs(p[0][a][1] - p[1][b][1]) == 3)
			{
				int st = min(p[0][c][0], p[1][d][0]);
				int ed = max(p[0][a][1], p[1][b][1]);
				if (tmp1 && Calc(st+2) + Calc(ed-2) >= Calc(st+3) + Calc(ed-3))
				{
					while (c<=a) Print(0,c), c++;
					while (d<=b) Print(1,d), d++;
				}
				else
				{
					if (tmp1)
					{
						if (idx!=0) printf(",");
						idx++;
						printf("%d",st);
						st += 2;
					}
					while (c<=a && d<=b)
					{
						if (idx!=0) printf(",");
						idx++;
						printf("%d-", st);
						st = min(p[0][c][1], p[1][d][1]) + 1;
						printf("%d", st); st +=2;
						if (st > p[0][c][1]) c++;
						if (st > p[1][d][1]) d++;
					}
					printf(",%d", max(p[0][a][1], p[1][b][1]));
				}
			}
			else
			{
				while (c<=a) Print(0,c), c++;
				while (d<=b) Print(1,d), d++;
			}
			a++; b++;
		}
		else if (p[0][a][0] < p[1][b][0])
		{
			Print(0,a); a++;
		}
		else if (p[0][a][0] > p[1][b][0])
		{
			Print(1,b); b++;
		}
	}
	while (a<=r) Print(0,a), a++;
	while (b<=l) Print(1,b), b++;
	printf("\n");
}

int main()
{
	freopen("E.in","r",stdin);
	Init();
	Solve();
	return 0;
}

