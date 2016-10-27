#include <bits/stdc++.h>
#define intl long long
using namespace std;

struct str { int v,nex; } edge[20100];

struct ST {
	int city,res,mon;

	void read() {
		scanf("%d %d %d",&city,&res,&mon);
	}
} dot[5010];

int dis[5010][5010];
int fst[5010],vis[5010],que[5010];
int n,m,w,q,e;
int city,res,mon,Res;

bool cmp(const ST &a, const ST &b) {
	return (a.mon < b.mon);
}

void make_edge(int a, int b) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b;
	edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a;
}

void bfs(int u) {
	int U = u;
	dis[u][u] = 0;
	for (int i = 1; i <= n; i++) vis[i] = 0;
	vis[u] = 1;
	int L = 0, R = 0;
	que[++R] = u;
	while (L < R) {
		u = que[++L];
		for (int i = fst[u]; i; i = edge[i].nex) {
			int v = edge[i].v;
			if (vis[v]) continue;
			dis[U][v] = dis[U][u] + 1;
			vis[v] = 1;
			que[++R] = v;
		}
	}
	return;
}

bool judge(int mid) {
	intl Mon = 0;
	for (int i = 1; i <= w; i++) {
		if (dis[city][dot[i].city] > mid) continue;
		if (res > dot[i].res) {
			Mon += (intl) dot[i].res * (intl) dot[i].mon;
			res -= dot[i].res;
		} else {
			Mon += (intl) res * (intl) dot[i].mon;
			res = 0;
			break;
		}
	}
	if (res) return false;
	return (Mon <= (intl) mon);
}


int main() {
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d",&a,&b);
		make_edge(a, b);
	}

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (i != j) dis[i][j] = 1 << 29;
	for (int i = 1; i <= n; i++)
		bfs(i);

	scanf("%d",&w);
	for (int i = 1; i <= w; i++) {
		dot[i].read();
	}

	sort(dot + 1, dot + w + 1, cmp);
	for (scanf("%d",&q); q; q--) {
		scanf("%d %d %d",&city,&Res,&mon);
		int L = 0, R = 5001;
		while (L < R) {
			res = Res;
			int mid = (L + R) >> 1;
			if (judge(mid)) R = mid;
			else L = mid + 1;
		}
		if (L == 5001) printf("-1\n");
		else printf("%d\n",L);
	}
	return 0;
}
