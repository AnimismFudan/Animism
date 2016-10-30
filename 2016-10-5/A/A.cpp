#include <bits/stdc++.h>
#define maxn 510
#define INF (1 << 29)
using namespace std;

struct str { int v,nex,len; } edge[maxn * maxn];

int d[maxn][maxn];
int fst[maxn],Mark[maxn],vis[maxn],slk[maxn],nex[maxn];
int lp[maxn],rp[maxn],C[maxn],D[maxn];
int nl,nr,ans,n,m,e,T;

void init() {
    nl = nr = ans = e = 0;
    for (int i = 1; i <= n; i++)
	fst[i] = 0;
}
    
void make_edge(int a,int b,int len) {
    edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b; edge[e].len = len;
}

bool path(int u) {
    vis[u] = 1;
    for (int i = fst[u]; i; i = edge[i].nex) {
	int v = edge[i].v;
	if (edge[i].len == Mark[u] + Mark[v]) {
	    if (vis[v]) continue;
	    vis[v] = 1;
	    if (!nex[v] || path(nex[v])) {
		nex[v] = u, nex[u] = v;
		return true;
	    }
	} else {
	    slk[v] = min(slk[v], edge[i].len - Mark[u] - Mark[v]);
	}
    }
    return false;
}

void km() {
    for (int i = 1; i <= nl; i++) Mark[lp[i]] = INF;
    for (int i = 1; i <= nr; i++) Mark[rp[i]] = 0;
    for (int i = 1; i <= n; i++) nex[i] = 0;
    for (int i = 1; i <= nl; i++) {
	int u = lp[i];
	for (int j = fst[u]; j; j = edge[j].nex) {
	    Mark[u] = min(Mark[u], edge[j].len);
	}
    }

    for (int i = 1; i <= nl; i++) {
	int u = lp[i];
	for (int j = 1; j <= nr; j++)
	    slk[rp[j]] = 1 << 28;
	for (int j = 1; j <= nl; j++)
	    vis[rp[j]] = vis[lp[j]] = 0;

	while (!path(u)) {
	    int sing = 1 << 28;
	    for (int j = 1; j <= nr; j++) {
		int v = rp[j];
		if (!vis[v]) sing = min(sing, slk[v]);
	    }

	    for (int j = 1; j <= nl; j++)
		if (vis[lp[j]])
		    Mark[lp[j]] += sing;
	    for (int j = 1; j <= nr; j++)
		if (vis[rp[j]])
		    Mark[rp[j]] -= sing;
	    for (int j = 1; j <= nr; j++)
		slk[rp[j]] = 1 << 28, vis[rp[j]] = 0;
	}
    }

    for (int i = 1; i <= nl; i++)
	ans += Mark[lp[i]];
    for (int i = 1; i <= nr; i++)
	ans += Mark[rp[i]];
}

int main() {
    freopen("A.in","r",stdin);
    freopen("A.out","w",stdout);
    for (scanf("%d",&T); T; T--) {
	scanf("%d %d",&n,&m);
	init();
	for (int i = 1; i <= n; i++)
	    for (int j = 1; j <= n; j++)
		if (i == j) d[i][j] = 0;
		else d[i][j] = 1 << 29;
	for (int i = 1; i <= m; i++) {
	    int a,b;
	    scanf("%d %d",&a,&b);
	    d[a][b] = d[b][a] = 1;	    
	}
	for (int k = 1; k <= n; k++)
	    for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	for (int i = 1; i <= n; i++)
	    scanf("%d",&C[i]);
	for (int i = 1; i <= n; i++)
	    scanf("%d",&D[i]);
	for (int i = 1; i <= n; i++) {
	    if (C[i] == 0 && D[i] == 1)
		lp[++nl] = i;
	    if (C[i] == 1 && D[i] == 0)
		rp[++nr] = i;
	}
	for (int i = 1; i <= nl; i++)
	    for (int j = 1; j <= nr; j++)
		if (d[lp[i]][rp[j]] != (1 << 29))
		make_edge(lp[i], rp[j], d[lp[i]][rp[j]]);
	km();
	printf("%d\n",ans);
    }
    return 0;
}
