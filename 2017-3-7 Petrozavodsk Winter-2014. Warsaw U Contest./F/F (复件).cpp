#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MaxN = (int)1e5 + 7;
const int MaxM = (int)1e6 + 7;

struct nodetype
{
	int id, flg, x, a, b;
};

int N, Q, L, W;
int rec[MaxN][4], qry[MaxN][2];
ll res, ans[MaxN], tmp[MaxN];
nodetype lin[MaxN << 1];
nodetype ask[MaxN << 1];
ll tree[MaxM];

bool Comp(const nodetype A, const nodetype B)
{
	return (A.x < B.x);
}

void Proc1()
{
	for (int i=1; i<=N; i++)
	{
		lin[i+i-1].flg = 1; lin[i+i-1].x = rec[i][1] + 1;
		lin[i+i-1].a = rec[i][0]+1; lin[i+i-1].b = rec[i][2];
		
		lin[i+i].flg = -1; lin[i+i].x = rec[i][3] + 1;
		lin[i+i].a = rec[i][0]+1; lin[i+i].b = rec[i][2];
	}
	sort(lin+1, lin+N+N+1, Comp);
	
	tmp[0] = 0; ll add = 0;
	for (int i=1, j=1; i<=(int)1e6; i++)
	{
		while (j<=N+N && lin[j].x == i)
		{
			add += lin[j].flg * (lin[j].b - lin[j].a + 1);
			j++;
		}
		tmp[i] = tmp[i-1] + add;
		//cerr << i << ' ' << tmp[i] << endl;
		//if (i > 10) break;
	}
	
	for (int i=1; i<=Q; i++)
	{
		ans[i] = tmp[qry[i][1] + W];
		ans[i] -= tmp[qry[i][1]];
		cerr << i << ' ' << qry[i][1]+W << ' '<< qry[i][1] << ' '<< ans[i] << endl;
	}
}

inline int lowbit(int x)
{
	return x & (-x);
}

void Update(int x, int d)
{
	while (x <= (int)1e6)
		tree[x] += d, x += lowbit(x);
}

inline ll Calc(int x)
{
	ll s = 0;
	if (x < 0) return 0;
	while (x)
	{
		s += tree[x];
		x -= lowbit(x);
	}
	return s;
}

void Proc2()
{
	for (int i=1; i<=N; i++)
	{
		lin[i+i-1].flg = 1; lin[i+i-1].x = rec[i][1] + 1;
		lin[i+i-1].a = rec[i][0]+1; lin[i+i-1].b = rec[i][2];
		
		lin[i+i].flg = -1; lin[i+i].x = rec[i][3] + 1;
		lin[i+i].a = rec[i][0]+1; lin[i+i].b = rec[i][2];
	}
	sort(lin+1, lin+N+N+1, Comp);
	
	for (int i=1; i<=Q; i++)
	{
		ask[i+i-1].flg = 1; ask[i+i-1].id = i; ask[i+i-1].x = qry[i][0] + 1;
		ask[i+i-1].a = qry[i][1] + 1; ask[i+i-1].b = qry[i][1] + W;
		
		ask[i+i].flg = -1; ask[i+i].id = i; ask[i+i].x = qry[i][0] + L;
		ask[i+i].a = qry[i][1] + 1; ask[i+i].b = qry[i][1] + L;
	}
	sort(ask+1, ask+Q+Q+1, Comp);
	for (int i=1; i<=Q+Q; i++)
		cerr << '*' << ' ' <<		ask[i].id << ' ' << ask[i].x << ' ' << ask[i].a << ' ' << ask[i].b << endl;
	
	for (int i=1, j=1, k=1; i<=(int)1e6; i++)
	{
		while (j <= N+N && lin[j].x == i)
		{
			Update(lin[j].a, lin[j].flg);
			Update(lin[j].b, -lin[j].flg);
			j++;
		}
		
		for (int i=1; i<=10; i++)
			cerr << tree[i] << ' ';
		cerr << endl;
		
		if (i > 10) break;
		
		while (k <= Q+Q && ask[k].x == i)
		{
			cerr << ask[k].x << ' ' << ask[k].id << " ( " << ask[k].a << ' ' << ask[k].b << " ) " << endl;
			if (ask[k].flg == 1)
			{
				ans[ask[k].id] -= Calc(ask[k].b) - Calc(ask[k].a-1);
				cerr << Calc(ask[k].b) - Calc(ask[k].a - 1) << endl;
			}
			else
			{
				ans[ask[k].id] -= (res - Calc(ask[k].b) + Calc(ask[k].a-1));
				cerr << Calc(ask[k].b) - Calc(ask[k].a - 1) << endl;
			}
			k++;
		}
	}
}

int main()
{
	freopen("F.in", "r", stdin);
	
	scanf("%d%d", &N, &Q);
	scanf("%d%d", &L, &W);
	for (int i=1; i<=N; i++)
	{
		scanf("%d%d%d%d",  &rec[i][0], &rec[i][1], &rec[i][2], &rec[i][3]);
		res += (ll)(rec[i][2] - rec[i][0]) * (rec[i][3] - rec[i][1]);
	}
	
	cerr << res << endl;
	
	for (int i=1; i<=Q; i++)
	{
		scanf("%d%d", &qry[i][0], &qry[i][1]);
		//ans[i] = res;
	}
	
	Proc1();
	Proc2();
	
	for (int i=1; i<=Q; i++)
		printf("%lld\n", ans[i]);
	
	return 0;
}

