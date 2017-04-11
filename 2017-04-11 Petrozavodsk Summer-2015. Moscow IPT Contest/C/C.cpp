#include <bits/stdc++.h>
#define maxn 201100
//13:47
using namespace std;

struct Per { int l, r, dis; } per[maxn * 5];

struct str {
	int x, l, r, num;
	void read() { scanf("%d %d %d", &x,&l,&r); }
	
} dot[maxn];

int que[maxn], dis[maxn], fa[maxn];
int p[maxn], X[maxn], ans[maxn];
int n, m, rt, top;

int find(int a) {
	return (fa[a] == a ? a : (fa[a] = find(fa[a])));
}

int binary_search(int x) {
	if (dot[n].x < x) return n + 1;
	int L = 1, R = n;
	while (L < R) {
		int u = (L + R) >> 1;
		if (dot[u].x >= x) R = u;
		else L = u + 1;
	}
	return L;
}

void bfs() {
	int L = 0, R = 0;
	for (int i = 1; i <= n + 1; i++) dis[i] = (1 << 30);
	for (int i = 1; i <= n + 1; i++) fa[i] = i;
	for (int i = 1; i <= n; i++) {
		if (dot[i].x == dot[rt].x) {
			fa[i] = i + 1;
			que[++R] = i;
			dis[i] = 0;
		}
	}
	while (L < R) {
		int u = que[++L];
		int v = find(binary_search(dot[u].x + dot[u].l));
		for (; v < n + 1 && dot[v].x <= dot[u].x + dot[u].r; v = find(v)) {
			que[++R] = v;
			dis[v] = dis[u] + 1;
			fa[v] = v + 1;
		}
		v = find(binary_search(dot[u].x - dot[u].r));
		for (; v < n + 1 && dot[v].x <= dot[u].x - dot[u].l; v = find(v)) {
			que[++R] = v;
			dis[v] = dis[u] + 1;
			fa[v] = v + 1;
		}
	}
}

bool cmp(const str &a, const str &b) {
	return (a.x < b.x);
}

bool pmc(const Per &a, const Per &b) {
	return (a.l < b.l);
}

bool cpm(int a, int b) {
	return (X[a] < X[b]);
}

struct st_cmp {
	bool operator () (int a, int b) {
		return (per[a].r < per[b].r || (per[a].r == per[b].r && a < b));
	}
};
	
set<int,st_cmp> st;

struct ts_cmp {
	bool operator () (int a, int b) {
		return (per[a].dis < per[b].dis || (per[a].dis == per[b].dis && a < b));
	}
};

set<int, ts_cmp> ts;

void solve() {	
	for (int i = 1; i <= n; i++) {
		per[++top] = (Per) { dot[i].x - dot[i].r, dot[i].x - dot[i].l, dis[i] + 1 };
		per[++top] = (Per) { dot[i].x + dot[i].l, dot[i].x + dot[i].r, dis[i] + 1 };
		per[++top] = (Per) { dot[i].x, dot[i].x, dis[i] };
	}
	sort(per + 1, per + top + 1, pmc);
	scanf("%d",&m);
	for (int i = 1; i <= m; i++) scanf("%d",&X[i]);
	for (int i = 1; i <= m; i++) p[i] = i;
	sort(p + 1, p + m + 1, cpm);
	int q = 1;
	for (int i = 1; i <= m; i++) {
		int u = p[i];
		while (q <= top && per[q].l <= X[u]) {
			st.insert(q);
			ts.insert(q);
			q++;
		}
		while (!st.empty() && per[*st.begin()].r < X[u]) {
			ts.erase(*st.begin());
			st.erase(st.begin());
		}
		if (!st.empty()) ans[u] = per[*ts.begin()].dis;
		else ans[u] = 1 << 30;
	}
}

int main() {
	//freopen("C.in","r",stdin);
	//freopen("C.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) {
		dot[i].read();
		dot[i].num = i;
	}
	sort(dot + 1, dot + n + 1, cmp);
	for (int i = 1; i <= n; i++) if (dot[i].num == 1) rt = i;
	for (int i = 1; i <= n; i++) fa[i] = i;
	bfs();
	solve();
	for (int i = 1; i <= m; i++) {
		if (ans[i] >= (1 << 30)) printf("-1");
		else printf("%d",ans[i]);
		if (i < m) printf(" ");
		else printf("\n");
	}
	return 0;
}
