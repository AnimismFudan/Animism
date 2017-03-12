#include <bits/stdc++.h>
#define INF (1 << 30)
using namespace std;

struct str { int v,nex,cap; } edge[1010000];

int mark[60][60], val[60][60];
int vis[3010],que[101000],fst[1010],d[1010];
int e,n,m,s,t,T,top,cl,ans,M;

void init() {
    e = 1;
    for (int i = 1; i <= n * m + 10; i++)
	vis[i] = fst[i] = d[i] = 0;
    ans = 0;
    top = 0;
}

void make_edge(int a,int b,int c) {
    edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b; edge[e].cap = c;
    edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a; edge[e].cap = 0;
}

bool bfs() {
    int L = 0, R = 0;
    vis[s] = ++cl; que[++R] = s; d[s] = 0;
    while (L < R) {
	int u = que[++L];
	for (int i = fst[u]; i; i = edge[i].nex) {
	    int v = edge[i].v;
	    if (vis[v] != cl && edge[i].cap) {
		vis[v] = cl;
		que[++R] = v;
		d[v] = d[u] + 1;
	    }
	}
    }
    return (vis[t] == cl);
}

int dfs(int u,int ma) {
    if (u == t || !ma) return ma;
    int f, flow = 0;
    for (int i = fst[u]; i; i = edge[i].nex) {
	int v = edge[i].v;
	if (d[v] == d[u] + 1 && (f = dfs(v, min(edge[i].cap, ma)))) {
	    edge[i].cap -= f;
	    edge[i ^ 1].cap += f;
	    flow += f;
	    ma -= f;
	    if (!ma) return flow;
	}
    }
    d[u] = INF;
    return flow;
}

void dinic() {
    while(bfs())
	ans -= dfs(s, INF);
}

int main() {
    freopen("C.in","r",stdin);
    freopen("C.out","w",stdout);
    for (scanf("%d",&T); T; T--) {
	scanf("%d %d",&n,&m);
	init();
	for (int i = 1; i <= n; i++)
	    for (int j = 1; j <= m; j++) {
		scanf("%d",&val[i][j]);
		ans += val[i][j];
	    }
	for (int i = 1; i <= n; i++)
	    for (int j = (i & 1) + 1; j <= m; j += 2) {
		mark[i][j] = ++top;
	    }
	M = top;
	for (int i = 1; i <= n; i++)
	    for (int j = ((i & 1) ^ 1) + 1; j <= m; j += 2)
		mark[i][j] = ++top;
	s = ++top;
	t = ++top;
	for (int i = 1; i <= n; i++)
	    for (int j = (i & 1) + 1; j <= m; j += 2) {
		make_edge(s, mark[i][j], val[i][j]);
	    }
	for (int i = 1; i <= n; i++)
	    for (int j = ((i & 1) ^ 1) + 1; j <= m; j += 2)
		make_edge(mark[i][j], t, val[i][j]);
	for (int i = 1; i <= n; i++)
	    for (int j = (i & 1) + 1; j <= m; j += 2) {
		if (i > 1) make_edge(mark[i][j], mark[i - 1][j], INF);
		if (i < n) make_edge(mark[i][j], mark[i + 1][j], INF);
		if (j > 1) make_edge(mark[i][j], mark[i][j - 1], INF);
		if (j < m) make_edge(mark[i][j], mark[i][j + 1], INF);
	    }
	dinic();
	printf("%d\n",ans);
    }
    return 0;
}
