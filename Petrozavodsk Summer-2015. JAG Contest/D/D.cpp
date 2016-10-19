#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MaxN = 2007;
const int MaxM = 4e6 + 7;

int n,m,tot,s[MaxN];
vector<int> iv[MaxN],dt[MaxN];
int nxt[MaxN],d[MaxN];
ll siz, ans, res[MaxM];

void Make(int x, int fa)
{
	int i, tmpd; nxt[x] = -1; tmpd = d[x];
	for (i=0; i<iv[x].size(); i++)
		if(iv[x][i] != fa)
		{
			d[iv[x][i]] = tmpd+dt[x][i];
			Make(iv[x][i], x);
			if(d[iv[x][i]] > d[x])
				d[x] = d[iv[x][i]], nxt[x] = iv[x][i];
		}
	//printf("%d %d %d\n",x,d[x],nxt[x]);
}

void Calc(int x, int fa, ll len)
{
	int i;
	if(iv[x].size() == 1 && fa != 0)
	{
		res[++tot] = siz * len;
		//printf("%d %lld %lld\n",x,siz,len);
		return;
	}
	for (i=0; i<iv[x].size(); i++)
		if(iv[x][i] != fa)
		{
			if(iv[x][i] == nxt[x])
				Calc(iv[x][i], x, len+dt[x][i]);
			else Calc(iv[x][i], x, dt[x][i]);
		}
}

int main()
{
	//freopen("D.in","r",stdin);
	//freopen("D.out","w",stdout);
	
	int i,a,b,c;
	
	scanf("%d%d",&n,&m);
	for (i=1; i<n; i++)
		scanf("%d%d%d",&a,&b,&c),
		iv[a].push_back(b), dt[a].push_back(c),
		iv[b].push_back(a), dt[b].push_back(c);
	for (i=1; i<=n; i++)
		scanf("%d",s+i);
	for (i=1; i<=n; i++)
	{
		d[i] = 0; siz = s[i];
		Make(i,0);
		Calc(i,0,0);
	}
	sort(res+1, res+1+tot);
	//for(i=tot; i>=1; i--)
	//	printf("%lld ",res[i]); printf("\n");
	for (i=tot, a=1; i>=1 && a<=m; i--, a++)
		ans += res[i];
	printf("%lld\n",ans);
	
	return 0;
}

