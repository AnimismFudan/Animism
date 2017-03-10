#include <bits/stdc++.h>
using namespace std;

#define LL long long

const int MaxN = (int)1e5 + 7;
const int MaxM = (int)1e6 + 7;

struct nodetype
{
	int id, flg, x, a, b;
};

int N, Q, L, W;
int rec[MaxN][4], qry[MaxN][2];
LL res, ans[MaxN], tmp[MaxN];
nodetype lin[MaxN << 1];
nodetype ask[MaxN << 1];
int l[MaxM << 2], r[MaxM << 2];
LL s[MaxM << 2], t[MaxM << 2];

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
	
	tmp[0] = 0; LL add = 0;
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

void MakeSeg(int x, int ll, int rr)
{
	l[x] = ll; r[x] = rr;
	s[x] = t[x] = 0;
	if (ll != rr)
	{
		int mi = (ll + rr) >> 1;
		int lc = x << 1;
		MakeSeg(lc, ll, mi);
		MakeSeg(lc+1, mi+1, rr);
	}
}

void Download(int x)
{
	int lc = x<<1, rc = lc+1;
	t[lc] += t[x]; t[rc] += t[x];
	s[lc] += t[x] * (r[lc] - l[lc] + 1);
	s[rc] += t[x] * (r[rc] - l[rc] + 1);
	t[x] = 0;
}

void Update(int x, int ll, int rr, int d)
{
	if (ll <= l[x] && r[x] <= rr)
	{
		t[x] += d;
		s[x] += d * (r[x] - l[x] + 1);
		return;
	}
	int lc = x << 1;
	if (t[x] != 0) Download(x);
	if (ll <= r[lc]) Update(lc, ll, rr, d);
	if (r[lc] < rr) Update(lc+1, ll, rr, d);
}

inline LL Calc(int x, int ll, int rr)
{
	if (ll <= l[x] && r[x] <= rr)
		return s[x];
	int lc = x << 1; LL cac = 0;
	if (t[x] != 0) Download(x);
	if (ll <= r[lc]) cac += Calc(lc, ll, rr);
	if (r[lc] < rr) cac += Calc(lc+1, ll, rr);
	return cac;
}

void Proc2()
{
	for (int i=1; i<=N; i++)
	{
		lin[i].flg = 1; lin[i].x = rec[i][1] + 1;
		lin[i].a = rec[i][0]+1; lin[i].b = rec[i][2];
		
		lin[i+i].flg = -1; lin[i+i].x = rec[i][3] + 1;
		lin[i+i].a = rec[i][0]+1; lin[i+i].b = rec[i][2];
	}
	sort(lin+1, lin+N+1, Comp);
	
	for (int i=1; i<=Q; i++)
	{
		ask[i+i-1].flg = -1; ask[i+i-1].id = i; ask[i+i-1].x = qry[i][0] + 1;
		ask[i+i-1].a = qry[i][1] + 1; ask[i+i-1].b = qry[i][1] + W;
		
		ask[i+i].flg = 1; ask[i+i].id = i; ask[i+i].x = qry[i][0] + L;
		ask[i+i].a = qry[i][1] + 1; ask[i+i].b = qry[i][1] + W;
	}
	sort(ask+1, ask+Q+Q+1, Comp);
	for (int i=1; i<=Q+Q; i++)
		cerr << '*' << ' ' <<		ask[i].id << ' ' << ask[i].x << ' ' << ask[i].a << ' ' << ask[i].b << endl;
	
	MakeSeg(1, 1, (int)1e6);
	
	for (int i=1, j=1, k=1; i<=(int)1e6; i++)
	{
		while (j <= N && lin[j].x == i)
		{
			Update(1, lin[j].a, lin[j].b, lin[j].flg);
			j++;
		}
		
		if (i > 10) break;
		
		while (k <= Q+Q && ask[k].x == i)
		{
			cerr << ask[k].x << ' ' << ask[k].id << " ( " << ask[k].a << ' ' << ask[k].b << " ) " << ' ' << Calc(1, ask[k].a, ask[k].b) << endl;
			if (ask[k].flg == 1)
			{
				ans[ask[k].id] += ask[k].flg * Calc(1, ask[k].a, ask[k].b);
			}
			else
			{
				ans[ask[k].id] += ask[k].flg * Calc(1, ask[k].a, ask[k].b);
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
		res += (LL)(rec[i][2] - rec[i][0]) * (rec[i][3] - rec[i][1]);
	}
	
	cerr << res << endl;
	
	for (int i=1; i<=Q; i++)
	{
		scanf("%d%d", &qry[i][0], &qry[i][1]);
		//ans[i] = res;
	}
	
	//Proc1();
	Proc2();
	
	for (int i=1; i<=Q; i++)
		printf("%lld\n", ans[i]);
	
	return 0;
}

