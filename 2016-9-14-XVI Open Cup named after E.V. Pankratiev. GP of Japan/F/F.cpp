#include <bits/stdc++.h>
using namespace std;

struct str { int v,nex,val,d; } edge[210 * 210];
int fst[210];
double f[210][1100],g[210];
int n,m,p,e;
double ans;

void make_edge(int a,int b,int d,int val) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b; edge[e].val = val; edge[e].d = d;
	edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a; edge[e].val = val; edge[e].d = d;
}

int main() {
	//freopen("F.in","r",stdin);
	//freopen("F.out","w",stdout);
	scanf("%d %d %d",&n,&m,&p);
	
	for (int i = 1; i <= m; i++) {
		int a,b,d,val;
		scanf("%d %d %d %d",&a,&b,&d,&val);
		make_edge(a, b, d, val);
		g[a] = max(g[a], (double) val / (double) d);
		g[b] = max(g[b], (double) val / (double) d);
	}

	for (int i = 1; i <= n; i++)
		for (int t = 0; t <= p; t++)
			f[i][t] = -10000000000000;
	f[1][0] = 0;
	for (int t = 1; t <= p; t++) {
		for (int u = 1; u <= n; u++) {
			f[u][t] = max(f[u][t], f[u][t - 1] + g[u]);
			for (int i = fst[u]; i; i = edge[i].nex) {
				int v = edge[i].v;
				if (t < edge[i].d) continue;
				f[u][t] = max(f[u][t], f[v][t - edge[i].d] + (double) edge[i].val);
			} 
		}		
	}
	
	for (int i = 0; i <= p; i++) ans = max(ans, f[1][i]);
	printf("%.10lf\n",ans);
	return 0;
}
