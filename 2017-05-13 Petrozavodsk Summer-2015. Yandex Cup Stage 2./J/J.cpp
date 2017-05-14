#include <bits/stdc++.h>
using namespace std;

const int MaxN = 30;
const int MaxM = 60000;

struct nodetype
{
	int X, Y, M;
};

int N, Q, A[MaxN], B[MaxN];
int fg, lim, X, Y, M, cnt[2];
nodetype nod[2][MaxM];
nodetype ask[MaxM], qry[MaxM];
int len, xtmp[MaxM];
int tree[MaxM];

bool Comp(const nodetype A, const nodetype B)
{
	if (A.X == B.X)
		return (A.Y < B.Y);
	return (A.X < B.X);
}

void DFS(int id)
{
	if (id > lim)
	{
		cnt[fg]++;
		nod[fg][cnt[fg]].X = X;
		nod[fg][cnt[fg]].Y = Y;
		nod[fg][cnt[fg]].M = M;
		return;
	}
	DFS(id+1);
	X += A[id]; Y += B[id]; M++;
	DFS(id+1);
	X = X - A[id] + B[id];
	Y = Y - B[id] + A[id];
	DFS(id+1);
	X -= B[id]; Y -= A[id]; M--;
	return;
}

inline int lowbit(int x)
{
	return x & (x ^ (x-1));
}

void Add(int x, int d)
{
	x = lower_bound(xtmp + 1, xtmp + 1 + len, x) - xtmp;
	x = len + 1 - x;
	while (x <= len)
	{
		tree[x] = min(tree[x], d);
		x += lowbit(x);
	}
}

inline int Calc(int x)
{
	//cout << "calc: " << x << ' ' ;
	x = lower_bound(xtmp+1, xtmp + 1 + len, x) - xtmp;
	//cout << x << endl;
	x = len+1-x;
	int s = 1<<20;
	while (x > 0)
	{
		s = min(s, tree[x]);
		x -= lowbit(x);
	}
	return s;
}

void Proc()
{
	xtmp[0] = 0;
	for (int i=1; i<=cnt[0]; i++)
	{
		ask[i] = nod[0][i];
		xtmp[++xtmp[0]] = ask[i].Y;
	}
	for (int i=1; i<=cnt[1]; i++)
	{
		qry[i] = nod[1][i];
	}
	sort(xtmp+1, xtmp+1+xtmp[0]);
	len = 1;
	for (int i=1; i<=xtmp[0]; i++)
		if (xtmp[i] != xtmp[len])
			xtmp[++len] = xtmp[i];

	for (int i=0; i<MaxM; i++)
		tree[i] = 1000;
	int ans = N+1;
	for (int i=cnt[0], j=1; j <= cnt[1]; j++)
	{
		while (i >= 1 && ask[i].X + qry[j].X >= X)
		{
			//cout << "add: " << ask[i].X << ' ' << qry[j].X << ' ' << X << endl;
			//cout << "add--" << ask[i].Y << ' ' << qry[j].Y << ' ' << Y << endl;
			Add(ask[i].Y, ask[i].M); i--;
		}
		ans = min(ans, qry[j].M + Calc(Y - qry[j].Y));
	}
	if (ans == N+1)
		printf("-1\n");
	else printf("%d\n", ans);
	return;
}

int main()
{
	freopen("jeopardy.in", "r", stdin);
	freopen("jeopardy.out", "w", stdout);
	
	scanf("%d", &N);
	for (int i=1; i<=N; i++)
		scanf("%d%d", A+i, B+i);
	fg = 0; lim = N/2;
	X = Y = M = 0;
	DFS(1);
	
	fg = 1; lim = N;
	X = Y = M = 0;
	DFS(N/2+1);
	/*
	cout << cnt[0] << endl;
	for (int i=1; i<=cnt[0]; i++)
		cout << nod[0][i].X << ' ' << nod[0][i].Y <<' ' << nod[0][i].M << endl;
	cout << cnt[1] << endl;
	for (int i=1; i<=cnt[1]; i++)
		cout << nod[1][i].X << ' ' << nod[1][i].Y << ' ' << nod[1][i].M << endl;
	*/
	
	sort(nod[0]+1, nod[0]+cnt[0]+1, Comp);
	sort(nod[1]+1, nod[1]+cnt[1]+1, Comp);
	
	scanf("%d", &Q);
	for (int i=1; i<=Q; i++)
	{
		scanf("%d%d", &X, &Y);
		Proc();
	}
	
	return 0;
}

