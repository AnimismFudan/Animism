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
int l[MaxM << 2], r[MaxM << 2], X, K, B;
LL k[MaxM << 2], b[MaxM << 2], mark[MaxM << 2];

bool Comp(const nodetype A, const nodetype B)
{
	return (A.x < B.x);
}

void MakeSeg(int x, int ll, int rr)
{
	l[x] = ll; r[x] = rr;
	k[x] = b[x] = mark[x] = 0;
	if (ll != rr)
	{
		int mi = (ll + rr) >> 1;
		int lc = x << 1;
		MakeSeg(lc, ll, mi);
		MakeSeg(lc+1, mi+1, rr);
	}
}

void Change(int x, int d)
{
	LL temp = k[x] * X + b[x] + d * (r[x] - l[x] + 1);
	mark[x] += d;
	k[x] += d * (r[x] - l[x] + 1);
	b[x] = temp - k[x] * X;
}

void Download(int x)
{
	Change(x<<1, mark[x]);
	Change((x<<1) + 1, mark[x]);
	mark[x] = 0;
}

void Update(int x, int ll, int rr, int d)
{
	if (ll <= l[x] && r[x] <= rr)
	{
		Change(x, d);
		return;
	}
	int lc = x << 1;
	if (mark[x] != 0) Download(x);
	if (ll <= r[lc]) Update(lc, ll, rr, d);
	if (r[lc] < rr) Update(lc+1, ll, rr, d);
	k[x] = k[lc] + k[lc+1];
	b[x] = b[lc] + b[lc+1];
}

void Calc(int x, int ll, int rr)
{
	if (ll <= l[x] && r[x] <= rr)
	{
		K += k[x]; B += b[x];
		return;
	}
	int lc = x << 1;
	if (mark[x] != 0) Download(x);
	if (ll <= r[lc]) Calc(lc, ll, rr);
	if (r[lc] < rr) Calc(lc+1, ll, rr);
	return;
}

void Proc()
{
	for (int i=1; i<=N; i++)
	{
		lin[i+i-1].flg = 1; lin[i+i-1].x = rec[i][0] + 1;
		lin[i+i-1].a = rec[i][1]+1; lin[i+i-1].b = rec[i][3];
		
		lin[i+i].flg = -1; lin[i+i].x = rec[i][0] + 1;
		lin[i+i].a = rec[i][1]+1; lin[i+i].b = rec[i][3];
	}
	sort(lin+1, lin+N+N+1, Comp);
	for (int i=1; i<=N+N; i++)
		cerr << lin[i].x << ' ' << lin[i].a << ' '<<lin[i].b << endl;
	
	for (int i=1; i<=Q; i++)
	{
		ask[i+i-1].flg = -1; ask[i+i-1].id = i; ask[i+i-1].x = qry[i][0];
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
		X = i;
		while (j <= N+N && lin[j].x == i)
		{
			Update(1, lin[j].a, lin[j].b, lin[j].flg);
			cerr << "Update: " << lin[j].x << ' '<<lin[j].a << ' ' << lin[j].b << endl;
			j++;
		}
		
		if (i > 10) break;
		
		while (k <= Q+Q && ask[k].x == i)
		{
			if (ask[k].flg == 1)
			{
				K = N = 0;
				Calc(1, ask[k].a, ask[k].b);
				ans[ask[k].id] += ask[k].id * (K * X + B);
				cerr << ask[k].x << ' ' << ask[k].a << ' ' << ask[k].b << ' '<< K * X + B << endl;
			}
			else
			{
				K = B = 0;
				Calc(1, ask[k].a, ask[k].b);
				ans[ask[k].id] += ask[k].flg * (K * X + B);
				cerr << ask[k].x << ' ' << ask[k].a << ' ' << ask[k].b << ' '<< K * X + B << endl;
			}
			k++;
		}
		K = B = 0;
		Calc(2, 2, 3);
		cerr << '|' << ' '<<X << ' ' <<K << ' ' << B <<' '<<K*X + B << endl;
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
		//res += (LL)(rec[i][2] - rec[i][0]) * (rec[i][3] - rec[i][1]);
	}
	for (int i=1; i<=Q; i++)
	{
		scanf("%d%d", &qry[i][0], &qry[i][1]);
	}
	
	Proc();
	
	for (int i=1; i<=Q; i++)
		printf("%lld\n", ans[i]);
	
	return 0;
}

