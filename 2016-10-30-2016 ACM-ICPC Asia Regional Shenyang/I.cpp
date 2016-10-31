#include <bits/stdc++.h>
#define S(a) ((a) * (a))
#define intl long long
#define maxn 201000
using namespace std;

struct str {
    int v,nex;
    intl len;
} edge[maxn << 1];

intl P,ans;
int n,T,e;
intl dep[maxn],f[maxn];
int mark[maxn],g[maxn],fa[maxn],fst[maxn],son[maxn];

void make_edge(int a,int b,intl c) {
    edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b; edge[e].len = c;
}

bool bet(int j, int k, int i) {
    return (f[j] - f[k] + S(dep[j]) - S(dep[k]) <= 2LL * dep[i] * (dep[j] - dep[k]));
}

bool judge(int a,int b,int c) {
    intl x1 = dep[b] - dep[a];
    intl y1 = (f[b] + S(dep[b])) - (f[a] + S(dep[a]));
    intl x2 = dep[c] - dep[b];
    intl y2 = (f[c] + S(dep[c])) - (f[b] + S(dep[b]));
    return (x1 * y2 - x2 * y1 <= 0LL);
}

intl trans(int j, int i) {
    return P + S(dep[i] - dep[j]) + f[j];
}

void dfs(int u) {
    int js,sj;
    for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v;
		fa[v] = u; 
		mark[v] = mark[u];
		dep[v] = dep[u] + edge[i].len;
		while(mark[v] != u && bet(son[mark[v]], mark[v], v))
			mark[v] = son[mark[v]];
		f[v] = trans(mark[v], v);
		g[v] = u;
		sj = mark[v];
		while (g[v] != 1 && judge(g[g[v]],g[v],v)) {
			g[v] = g[g[v]];
			//if (dep[g[v]] < dep[mark[v]]) mark[v] = g[v];
		}
		js = son[g[v]]; son[g[v]] = v;
		dfs(v);
		son[g[v]] = js;
		mark[v] = sj;
    }
}

void init() {
    for (int i = 1; i <= n; i++) f[i] = dep[i] = 0;
    for (int i = 1; i <= n; i++) mark[i] = g[i] = fa[i] = fst[i] = son[i] = 0;
    e = 0; mark[1] = 1;
}

int main() {
	freopen("I.in","r",stdin);
	freopen("I.out","w",stdout);
    for (scanf("%d",&T); T; T--) {
		scanf("%d %lld",&n,&P);
		init();
		for (int i = 1; i < n; i++) {
			int a,b; intl c;
			scanf("%d %d %lld",&a,&b,&c);
			if (a > b) swap(a, b);
			make_edge(a, b, c);
		}
		dfs(1);
		ans = 0LL;
		for (int i = 1; i <= n; i++)
			ans = max(ans, f[i]);
		printf("%lld\n",ans - P);
    }
    return 0;
}
