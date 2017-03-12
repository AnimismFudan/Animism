#include <bits/stdc++.h>
using namespace std;

register char *_sp __asm__("rsp");

const int MaxN = (int)1e5 + 7;
const int MaxM = (int)1e6 + 7;

int T,n,m,tot; bool flg;
int fir[MaxN],adj[MaxM],nxt[MaxM];
bool vis[MaxM][2];
int tp,stk[MaxN],col[MaxN];

void AddEdge(int a, int b)
{
	tot++; adj[tot] = b; nxt[tot] = fir[a]; fir[a] = tot;
	vis[tot][0] = vis[tot][1] = false;
}

void DFS(int x, int c)
{
	int i,j,k;
	stk[++tp] = x; col[x] = c;
	//printf("%d %d\n",x,col[x]);
	for(i=fir[x]; i; i=nxt[i])
	{
		if(vis[i][col[x]-1]) continue;
		vis[i][col[x]-1] = true;
		j = adj[i];
		//printf("%d %d %d\n",x,j,col[j]);
		if(col[j])
		{
			if(col[j]==col[x])
			{
				printf("1\n");
				for(k=tp; stk[k]!=j; k--);
				printf("%d\n",tp-k+1);
				while(k<=tp)
					printf("%d\n",stk[k++]);
				flg = true;
				return;
			}
		}
		else
		{	
			DFS(j, 3-col[x]);
			if(flg) return;
		}
	}
	
	col[x] = 0; stk[tp--] = 0;
}

int main()
{
	freopen("F.in","r",stdin);
	freopen("F.out","w",stdout);
	
	const int size = 64*1024*1024;
	static char *sys, *mine(new char[size]+size-4096);
	sys = _sp;
	_sp = mine;
	
	int i,a,b;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		tot = 0;
		for(i=1; i<=n; i++) fir[i] = col[i] = 0;
		for(i=1; i<=m; i++)
			scanf("%d%d",&a,&b),
			AddEdge(a,b);
		flg = false; tp = 0;
		for(i=1; i<=n; i++)
		{
			DFS(i,1);
			if(flg) break;
		}
		if(!flg) printf("-1\n");
	}
	
	_sp = sys;
	return 0;
}

