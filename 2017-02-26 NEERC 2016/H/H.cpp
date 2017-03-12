#include <bits/stdc++.h>
using namespace std;

const int MaxN = 1007;
const int MINN = -32768;
const int MAXN = 32767;

struct nodetype
{
	int l, r;
};

int N;
nodetype pir[MaxN], rse[MaxN];
string str;

bool Comp(const nodetype A, const nodetype B)
{
	if (A.l == B.l) return (A.r < B.r);
	return (A.l < B.l);
}

int main()
{
	freopen("hard.in", "r", stdin);
	freopen("hard.out", "w", stdout);

	int i, j, k, s, l;
	int a, b;

	while (getline(cin, str))
	{
		l = str.size();
		if (l <= 1) continue;
		a = MINN; b = MAXN;
		for (i=0; i+1<l; i++)
			if (str[i] == '>' && str[i+1] == '=')
			{
				s = 1;
				for (j=i+1; j<l; j++)
				{
					if (str[j] == '-') s = -1;
					if (str[j] >= '0' && str[j] <= '9')
					{
						k = 0;
						for (; j<l && (str[j] >= '0' && str[j] <= '9'); j++)
							k = k*10 + (str[j] - '0');
						a = s * k;
						break;
					}
				}
				i = j-1;
			}
			else if (str[i] == '<' && str[i+1] == '=')
			{
				s = 1;
				for (j=i+1; j<l; j++)
				{
					if (str[j] == '-') s = -1;
					if (str[j] >= '0' && str[j] <= '9')
					{
						k = 0;
						for (; j<l && (str[j] >= '0' && str[j] <= '9'); j++)
							k = k*10 + (str[j] - '0');
						b = s * k;
						break;
					}
				}
				i = j-1;
			}
		if (a <= b)
		{
			N++; pir[N].l = a; pir[N].r = b;
		}
	}
	
	if (N==0)
	{
		printf("false\n");
		return 0;
	}
	
	sort(pir+1, pir+N+1, Comp);
	
	//cout << endl;
	for (i=2, j=1; i<=N; i++)
	{
		if (pir[j].r + 1 >= pir[i].l)
		{
			pir[j].r = max(pir[j].r, pir[i].r);
		}
		else
		{
			pir[++j] = pir[i];
		}
	}
	N = j;
	
	if (N==1 && pir[1].l == MINN && pir[1].r == MAXN)
		printf("true\n");
	else
	{
		for (i=1; i<=N; i++)
		{
			if (pir[i].l == MINN)
			{
				printf("x <= %d", pir[i].r);
			}
			else if (pir[i].r == MAXN)
			{
				printf("x >= %d", pir[i].l);
			}
			else printf("x >= %d && x <= %d", pir[i].l, pir[i].r);
			if (i < N)
				printf(" ||\n");
			else printf("\n");
		}
	}
	
	return 0;
}

