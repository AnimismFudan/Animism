#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MaxN = (int)5e5 + 7;

struct nodetype
{
	int id, l, r;
};

int N, M, a[MaxN]; ll suma[MaxN];
ll d[MaxN], b[MaxN];
int tp; nodetype stk[MaxN];
ll ans;

int BinS(int l, int r, int id, int i)
{
	int le, ri, mi;
	le = l; ri = r;
	while (le <= ri)
	{
		mi = (le + ri) >> 1;
		if (b[id] + a[mi] * (d[i] - d[id]) > b[i]) ri = mi-1;
		else le = mi+1;
	}
	return le-1;
}

int main()
{
	//freopen("H.in", "r", stdin);
	
	int i;
	
	scanf("%d%d", &N, &M);
	for (i=1; i<=N; i++)
		scanf("%d", a+i);
	sort(a+1, a+N+1);
	for (i=1; i<=N; i++)
		suma[i] = suma[i-1] + a[i];
	
	nodetype tmp;
	tmp.id = 0; tmp.l = 1; tmp.r = N;
	stk[tp=1] = tmp;
	
	for (i=1; i<=M; i++)
	{
		scanf("%lld%lld", d+i, b+i);
		ans = 0;
		while (tp > 0 && b[stk[tp].id] + a[stk[tp].l] * (d[i] - d[stk[tp].id]) >= b[i])
		{
			ans += (b[stk[tp].id] - b[i]) * (stk[tp].r - stk[tp].l + 1) + (suma[stk[tp].r] - suma[stk[tp].l-1]) * (d[i] - d[stk[tp].id]);
			tp--;
		}
		if (tp == 0)
		{
			tmp.id = i;
			tmp.l = 1; tmp.r = N;
			stk[tp=1] = tmp;
		}
		else
		{
			int mi = BinS(stk[tp].l, stk[tp].r, stk[tp].id, i);
			int ri = stk[tp].r;
			//cout << mi << ' ' << N << endl;
			if (mi < N)
			{
				stk[tp].r = mi;
				ans += (b[stk[tp].id] - b[i]) * (ri - mi) + (suma[ri] - suma[mi]) * (d[i] - d[stk[tp].id]);
				//cout << (b[stk[tp].id] - b[i]) * (ri - mi) << ' ' << (suma[ri] - suma[mi]) * (d[i] - d[stk[tp].id]) << endl;
				stk[++tp].l = mi+1;
				stk[tp].r = N;
				stk[tp].id = i;
			}
		}
		
		printf("%lld\n", ans);
	}
	
	return 0;
}

