#include <bits/stdc++.h>
using namespace std;

const int MaxN = 107;
const int MaxM = (int)1e4 + 7;

struct nodetype
{
	int id,dt;
};

int n,m,r[MaxN],ans,p[MaxM][3];
priority_queue<nodetype, vector<nodetype>, less<nodetype> > mq;

bool operator<(nodetype A, nodetype B)
{
	return (A.dt < B.dt);
}

bool Check (int d)
{
	int i; nodetype a,b;
	while(!mq.empty()) mq.pop();
	for (i=1; i<=n; i++)
	{
		a.id = i; a.dt = r[i]-d;
		if (r[i]>d) mq.push(a);
		if (r[i]<d) return false;
	}
	m = 0;
	while (!mq.empty())
	{
		a = mq.top(); mq.pop();
		if(mq.empty()) return false;
		b = mq.top(); mq.pop();
		m++;
		p[m][0] = a.id; p[m][1] = b.id; p[m][2] = -1;
		a.dt--; b.dt--;
		if (a.dt > 0) mq.push(a);
		if (b.dt > 0) mq.push(b);
		if (a.dt == 0 && mq.size() == 1)
		{
			a = mq.top(); mq.pop();
			p[m][2] = a.id;
		}
	}
	return true;
}

void Print(int a, int b, int c)
{
	int i;
	for (i=1; i<=n; i++)
		if (i==a || i==b || i==c)
			printf("1");
		else printf("0");
	printf("\n");
}

int main()
{
	int i,j,ri;//le,ri,mi;
	scanf("%d", &n);
	//le = 1; 
	ri = 1000;
	for (i=1; i<=n; i++)
		scanf("%d", r+i),
		ri = min(ri, r[i]);
	/*
	while (le <= ri)
	{
		mi = (le+ri) >> 1;
		if(Check(mi)) le = mi+1;
		else ri = mi-1;
	}
	*/
	while (ri && !Check(ri)) ri--;
	ans = ri;
	printf("%d\n", ans);
	if (ans == 0)
	{
		m = 0;
		for (i=1; i<=n; i++)
			m += r[i];
		printf("%d\n", m);
		for (i=1; i<=n; i++)
			for (j=1; j<=r[i]; j++)
				Print(i, i%n+1, -1);
	}
	else
	{
		printf("%d\n", m);
		for (i=1; i<=m; i++)
			Print(p[i][0], p[i][1], p[i][2]);
	}
	return 0;
}

