#include <bits/stdc++.h>
#define INF (1 << 29)
using namespace std;

struct str { int v, nex, cap, cost; } edge[101000];

int e, cl, n, m, c, Q, T, s, t;
int fst[40], vis[40], dis[40], okay[40], pas[40];
int cost[20][20];
int COST[110][110];
int f[110];
int que[1010000];
int sum[20][110];

void make_edge(int a, int b, int cap, int cost) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b; edge[e].cap = cap; edge[e].cost = cost;
	edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a; edge[e].cap = 0;   edge[e].cost = -cost;
}

bool solve(int &res, int &Cost) {
	vis[s] = ++cl;
	int L = 0, R = 0;
	for (int i = 1; i <= t; i++) dis[i] = INF;
	que[++R] = s; dis[s] = 0;
	okay[s] = 1;
	while (L < R) {
		int u = que[++L];
		okay[u] = 0;
		for (int i = fst[u]; i; i = edge[i].nex) {
			if (edge[i].cap && dis[edge[i].v] > dis[u] + edge[i].cost) {
				dis[edge[i].v] = dis[u] + edge[i].cost;
				pas[edge[i].v] = i;
				if (!okay[edge[i].v]) {
					que[++R] = edge[i].v;
					okay[edge[i].v] = 1;
				}
			}
		}
	}
	if (dis[t] == INF) return false;
	res--;
	Cost += dis[t];
	for (int u = t; u != s; u = edge[pas[u] ^ 1].v) {
		edge[pas[u]].cap--;
		edge[pas[u] ^ 1].cap++;
	}
	return true;
}

int prepare(int L, int R) {
	memset(fst, 0, sizeof(fst));
	e = 1;
	s = n + m + 1; t = s + 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (cost[i][j] == INF) make_edge(i, j + n, 1, INF);
			else make_edge(i, j + n, 1, (sum[j][R] - sum[j][L - 1]) * cost[i][j]);
		}
	for (int i = 1; i <= n; i++) make_edge(s, i, 1, 0);
	int cnt = 0;
	for (int i = 1; i <= m; i++)
		if (sum[i][R] - sum[i][L - 1] > 0)
			make_edge(i + n, t, 1, 0), cnt++;
	int ans = 0;
	while (solve(cnt, ans)); 
	if (cnt > 0) return INF;
	return ans;
}

int main() {
	//freopen("I.in","r",stdin);
	//freopen("I.out","w",stdout);
	scanf("%d %d %d",&n,&m,&c);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cost[i][j] = INF;
	for (scanf("%d",&T); T; T--) {
		int a, b, c;
		scanf("%d %d %d",&a,&b,&c);
		cost[a][b] = c;
	}
	scanf("%d",&Q);
	for (int i = 1; i <= Q; i++) {
		for (int j = 1; j <= m; j++) scanf("%d",&sum[j][i]);
		for (int j = 1; j <= m; j++) sum[j][i] += sum[j][i - 1];
	}

	for (int L = 1; L <= Q; L++)
		for (int R = L; R <= Q; R++)
			COST[L][R] = prepare(L, R);

	f[0] = 0;
	for (int i = 1; i <= Q; i++) {
		f[i] = INF;
		for (int j = 0; j < i; j++)
			f[i] = min(f[i], f[j] + COST[j + 1][i] + c);
	}
	printf("%d\n",f[Q]);
	return 0;
}
