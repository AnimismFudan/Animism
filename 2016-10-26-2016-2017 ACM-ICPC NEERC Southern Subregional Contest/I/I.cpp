#include <bits/stdc++.h>
using namespace std;

struct str { int v,nex,cap,cost; } edge[101000];
int e = 1;
int n,s,t,a,b,A,B,cl,ans;
int fst[5010],que[1010000],okay[5010],dis[5010],vis[5010];
int pas[5010],ansa[5010],ansb[5010],ta,tb;

void make_edge(int a,int b,int cap,int cost) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b; edge[e].cap = cap; edge[e].cost = cost;
	edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a; edge[e].cap = 0; edge[e].cost = -cost;
}

bool solve() {
	dis[s] = 0; cl++;
	int L = 0, R = 0;
	que[++R] = s; okay[s] = cl; vis[s] = cl;
	while (L < R) {
		int u = que[++L];
		okay[u] = 0;
		for (int i = fst[u]; i; i = edge[i].nex) {
			int v = edge[i].v;
			if (edge[i].cap && (vis[v] != cl || (vis[v] == cl && dis[v] < dis[u] + edge[i].cost))) {
				dis[v] = dis[u] + edge[i].cost;
				vis[v] = cl;
				pas[v] = i;
				if (okay[v] != cl) que[++R] = v, okay[v] = cl;
			}
		}
	}
	if (vis[t] != cl) return false;
	int cap = 1 << 30;
	for (int u = t; u != s; u = edge[pas[u] ^ 1].v) {
		cap = min(cap, edge[pas[u]].cap);
	}
	for (int u = t; u != s; u = edge[pas[u] ^ 1].v) {
		edge[pas[u]].cap -= cap;
		edge[pas[u] ^ 1].cap += cap;
	}
	ans += dis[t] * cap;
	return true;
}

int main() {
	freopen("I.in","r",stdin);
	freopen("I.out","w",stdout);
	scanf("%d %d %d",&n,&A,&B);
	s = n + 1;
	t = n + 2;
	a = n + 3;
	b = n + 4;
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%d",&x);
		make_edge(i, a, 1, x);
	}

	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%d",&x);
		make_edge(i, b, 1, x);
	}

	make_edge(a, t, A, 0);
	make_edge(b, t, B, 0);
	for (int i = 1; i <= n; i++)
		make_edge(s, i, 1, 0);

	while(solve());

	printf("%d\n",ans);

	for (int i = 1; i <= n; i++) {
		for (int j = fst[i]; j; j = edge[j].nex) {
			if (edge[j].v == a && !edge[j].cap) ansa[++ta] = i;
			if (edge[j].v == b && !edge[j].cap) ansb[++tb] = i;
		}
	}

	for (int i = 1; i <= ta; i++)
		printf("%d ",ansa[i]);
	putchar('\n');
	for (int i = 1; i <= tb; i++)
		printf("%d ",ansb[i]);	
	return 0;
}
