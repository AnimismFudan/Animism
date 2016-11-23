#pragma GCC push_options
#pragma GCC optimize("O2")
#include <bits/stdc++.h>
#define maxn 110
#define maxm 301000
#define eps (1e-6)
using namespace std;


struct str {
	int v,nex,cap;
	double cost;
} edge[maxm];

int cl;
int fst[maxn],pas[maxn],okay[maxn],que[1010000],vis[maxn];
double ans,dis[maxn];
int T,e,n,m,s,t;

struct cmp {
	bool operator () (int a,int b) {
		if (dis[a] > dis[b] + eps) return true;
		if (dis[a] < dis[b] - eps) return false;
		return a < b;
	}
};
	
set<int,cmp> st;

int sig(double a) {
	return (a < -eps ? -1 : (a > eps));
}

void make_edge(int a,int b,int cap,double cost) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b; edge[e].cap = cap; edge[e].cost =  cost;
	edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a; edge[e].cap = 0;   edge[e].cost = -cost;
}

bool bfs() {
	for (int i = 1; i <= t; i++) dis[i] = -1000000000.0;
	dis[s] = 0;
	for (int i = 1; i <= t; i++) okay[i] = 0;
	int L = 0, R = 0;
	que[++R] = s;
	while (L < R) {
		int u = que[++L];
		okay[u] = 0;
		for (int i = fst[u]; i; i = edge[i].nex) {
			int v = edge[i].v;
			if (edge[i].cap && dis[v] + eps < dis[u] + edge[i].cost) {
				dis[v] = dis[u] + edge[i].cost;
				pas[v] = i;
				if (!okay[v]) que[++R] = v;
				okay[v] = 1; 
			}
		}
	}
	return (dis[t] > (-1000000000.0 + 1.0));
}

double dfs(int u, int ma) {
	if (vis[u]) return 0;
	if (u == t || !ma) return ma;
	vis[u] = 1;
	int f, flow = 0;
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v;
		if (!sig(dis[v] - (dis[u] + edge[i].cost)) && (f = dfs(v, min(edge[i].cap, ma)))) {
			flow += f;
			ma -= f;
			edge[i].cap -= f;
			edge[i ^ 1].cap += f;
			if (!ma) {
				vis[u] = 0;
				return flow;
			}
		}
	}
	vis[u] = 0;
	dis[u] -= 1000000000.0;
	return flow;
}

void solve() {
	while (bfs()) {
		int flow = dfs(s, 1 << 30);
		ans += (double) flow * dis[t];
		//if (dis[t] < -eps) return;
	}
}

bool Solve() {
	for (int i = 1; i <= n + 2; i++)
		dis[i] = -100000000000.0;
	dis[s] = 0;
	st.insert(s);
	okay[s] = 1;
	int k = 0;
	while (!st.empty()) {
		int u = *st.begin();
		st.erase(st.begin());
		okay[u] = 0;
		for (int i = fst[u]; i; i = edge[i].nex) {
			int v = edge[i].v;
			k++;
			if (edge[i].cap && dis[v] + eps < dis[u] + edge[i].cost) {
				dis[v] = dis[u] + edge[i].cost;
				pas[v] = i;
				if (!okay[v]) st.insert(v);
				okay[v] = 1; 
			}
		}
	}
	if (dis[t] < (-100000000000.0 + 1.0)) return false;
	int flow = 1 << 30;
	for (int u = t; u != s; u = edge[pas[u] ^ 1].v) {
		flow = min(flow, edge[pas[u]].cap);
	}
	//printf("%d\n",flow);
	ans += flow * dis[t];
	for (int u = t; u != s; u = edge[pas[u] ^ 1].v) {
		edge[pas[u]].cap -= flow;
		edge[pas[u] ^ 1].cap += flow;
	}
	cl++;
	//printf("%d\n",k);
	return true;
}

void init() {
	e = 1;
	for (int i = 1; i <= n + 2; i++)
		fst[i] = 0;
}

int main() {
	for (scanf("%d",&T); T; T--) {
		scanf("%d %d",&n,&m);
		init();
		s = n + 1; t = n + 2;
		for (int i = 1; i <= n; i++) {
			int a, b;
			scanf("%d %d",&a,&b);
			if (a > b) make_edge(s, i, a - b, 0);
			if (a < b) make_edge(i, t, b - a, 0);
		}
		for (int i = 1; i <= m; i++) {
			int a, b, c;
			double p;
			scanf("%d %d %d %lf",&a,&b,&c, &p);
			make_edge(a, b, 1, 0);
			if (c > 1)
				make_edge(a, b, c - 1, log(1.0 - p));
		}
		ans = 0;
		solve();
		//while (Solve());
		printf("%.2lf\n",1.0 - exp(ans));
		//printf("%d\n",cl);
	}
	return 0;
}

#pragma GCC pop_options
