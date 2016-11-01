#include <bits/stdc++.h>
#define lk (u << 1)
#define rk (u << 1 | 1)
#define midl ((L + R) >> 1)
#define midr (midl + 1)
#define maxn 101000
using namespace std;

struct str { int v, nex; } edge[maxn << 1];

char s[21];
int T;
int sum[maxn << 2], mark[maxn << 2];
int fst[maxn],vis[maxn],incir[maxn],cir[maxn],fa[maxn],que[maxn];
int Lf[maxn],Rf[maxn],Ls[maxn],Rs[maxn],pos[maxn];
int e,n,m,top,L,R;

void init() {
	for (int i = 1; i <= n; i++)
		fst[i] = vis[i] = incir[i] = cir[i] = fa[i] = 0;
	for (int i = 1; i <= n; i++)
		Lf[i] = Rf[i] = Ls[i] = Rs[i] = 0;
	e = top = L = R = 0;
}

void make_edge(int a, int b) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b;
	edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a;
}

int find_circle(int u, int pas) {
	vis[u] = 1;
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v;
		if (v == pas) continue;
		if (vis[v]) {
			cir[++top] = u;
			return v;
		}
		int k;
		if ((k = find_circle(v, u))) {
			cir[++top] = u;
			if (u == k) return 0;
			else return k;
		}
	}
	return 0;
}

void bfs(int u) {
	que[++R] = u;
	while (L < R) {
		u = que[++L];
		Lf[u] = Rf[u] = 0;
		for (int i = fst[u]; i; i = edge[i].nex) {
			int v = edge[i].v;
			if (incir[v] || fa[u] == v) continue;
			fa[v] = u;
			que[++R] = v;
			if (!Lf[u]) Lf[u] = R;
			Rf[u] = R;
		}
	}
}

void another_bfs() {
	for (int t = R; t; t--) {
		int u = que[t];
		for (int i = fst[u]; i; i = edge[i].nex) {
			int v = edge[i].v;
			if (incir[v] || fa[u] == v) continue;
			if (!Ls[u]) Ls[u] = Lf[v];
			if (Rf[v]) Rs[u] = Rf[v];
		}
	}
	return;
}

void update(int u) {
	sum[u] = sum[lk] + sum[rk];
}

void build(int u, int L, int R) {
	if (L == R) { mark[u] = sum[u] = 0; return; }
	build(lk, L, midl);
	build(rk, midr, R);
	update(u);
	mark[u] = sum[u] = 0;
}

void down(int u, int L, int R) {
	if (!mark[u]) return;	
	sum[u] += mark[u] * (R - L + 1);
	if (L < R) mark[lk] += mark[u], mark[rk] += mark[u];
	mark[u] = 0;
	return;
}

void change(int u, int L, int R, int l, int r, int val) {
	if (L == l && R == r) {
		mark[u] += val;
		down(u, L, R);
		return;
	}
	down(u, L, R);
	if (r < midr) down(rk, midr, R), change(lk, L, midl, l, r, val);
	else if (l > midl) down(lk, L, midl), change(rk, midr, R, l, r, val);
	else {
		change(lk, L, midl, l, midl, val);
		change(rk, midr, R, midr, r, val);
	}
	update(u);
}

int find(int u, int L, int R, int l, int r) {
	down(u, L, R);
	if (L == l && R == r) return sum[u];
	if (r < midr) return find(lk, L, midl, l, r);
	else if (l > midl) return find(rk, midr, R, l, r);
	else return find(lk, L, midl, l, midl) + find(rk, midr, R, midr, r);	
}

void modify(int u, int d, int val) {
	if (!d) { change(1, 1, n, pos[u], pos[u], val); return; }
	if (d == 1) {
		change(1, 1, n, pos[u], pos[u], val);
		if (Lf[u])
			change(1, 1, n, Lf[u], Rf[u], val);
		if (incir[u]) {
			int v = cir[incir[u] - 1];
			change(1, 1, n, pos[v], pos[v], val);
			v = cir[incir[u] + 1];
			change(1, 1, n, pos[v], pos[v], val);
		} else {
			int v = fa[u];
			change(1, 1, n, pos[v], pos[v], val);
		}
	} else {
		change(1, 1, n, pos[u], pos[u], val);
		if (Lf[u])
			change(1, 1, n, Lf[u], Rf[u], val);
		if (Ls[u])
			change(1, 1, n, Ls[u], Rs[u], val);
		if (incir[u]) {
			int a = cir[incir[u] - 1];
			int b = cir[incir[u] + 1];
			change(1, 1, n, pos[a], pos[a], val);
			if (Lf[a])
				change(1, 1, n, Lf[a], Rf[a], val);
			change(1, 1, n, pos[b], pos[b], val);
			if (Lf[b])
				change(1, 1, n, Lf[b], Rf[b], val);
			int a_ = cir[incir[a] - 1];
			if (a_ != b)
				change(1, 1, n, pos[a_], pos[a_], val);
			int b_ = cir[incir[b] + 1];
			if (b_ != a && b_ != a_)
				change(1, 1, n, pos[b_], pos[b_], val);
		} else if (incir[fa[u]]) {
			int v = fa[u];
			int a = cir[incir[v] - 1];
			int b = cir[incir[v] + 1];
			change(1, 1, n, pos[v], pos[v], val);
			change(1, 1, n, pos[a], pos[a], val);
			change(1, 1, n, pos[b], pos[b], val);
			change(1, 1, n, Lf[v], Rf[v], val);
			change(1, 1, n, pos[u], pos[u], -val);
		} else {
			int f = fa[u];
			change(1, 1, n, pos[f], pos[f], val);
			change(1, 1, n, Lf[f], Rf[f], val);
			change(1, 1, n, pos[u], pos[u], -val);
			f = fa[f];
			change(1, 1, n, pos[f], pos[f], val);
		}
	}
}

int query(int u, int d) {
	int ans = 0;
	if (!d) { return find(1, 1, n, pos[u], pos[u]); }
	if (d == 1) {
		ans += find(1, 1, n, pos[u], pos[u]);
		if (Lf[u])
			ans += find(1, 1, n, Lf[u], Rf[u]);
		if (incir[u]) {
			int v = cir[incir[u] - 1];
			ans += find(1, 1, n, pos[v], pos[v]);
			v = cir[incir[u] + 1];
			ans += find(1, 1, n, pos[v], pos[v]);
		} else {
			int v = fa[u];
			ans += find(1, 1, n, pos[v], pos[v]);
		}
	} else {
		ans += find(1, 1, n, pos[u], pos[u]);
		if (Lf[u])
			ans += find(1, 1, n, Lf[u], Rf[u]);
		if (Ls[u])
			ans += find(1, 1, n, Ls[u], Rs[u]);
		if (incir[u]) {
			int a = cir[incir[u] - 1];
			int b = cir[incir[u] + 1];
			ans += find(1, 1, n, pos[a], pos[a]);
			if (Lf[a])
				ans += find(1, 1, n, Lf[a], Rf[a]);
			ans += find(1, 1, n, pos[b], pos[b]);
			if (Lf[b])
				ans += find(1, 1, n, Lf[b], Rf[b]);
			int a_ = cir[incir[a] - 1];
			if (a_ != b)
				ans += find(1, 1, n, pos[a_], pos[a_]);
			int b_ = cir[incir[b] + 1];
			if (b_ != a && b_ != a_)
				ans += find(1, 1, n, pos[b_], pos[b_]);
		} else if (incir[fa[u]]) {
			int v = fa[u];
			int a = cir[incir[v] - 1];
			int b = cir[incir[v] + 1];
			ans += find(1, 1, n, pos[v], pos[v]);
			ans += find(1, 1, n, pos[a], pos[a]);
			ans += find(1, 1, n, pos[b], pos[b]);		
			ans += find(1, 1, n, Lf[v], Rf[v]);
			ans -= find(1, 1, n, pos[u], pos[u]);
		} else {
			int f = fa[u];
			ans += find(1, 1, n, pos[f], pos[f]);
			ans += find(1, 1, n, Lf[f], Rf[f]);
			ans -= find(1, 1, n, pos[u], pos[u]);
			f = fa[f];
			ans += find(1, 1, n, pos[f], pos[f]);
		}
	}
	return ans;
}

int main() {
	freopen("J.in","r",stdin);
	freopen("J.out","w",stdout);
	for (scanf("%d",&T); T; T--) {
		scanf("%d",&n);
		init();
		for (int i = 1; i <= n; i++) {
			int a, b;
			scanf("%d %d",&a,&b);
			make_edge(a, b);
		}
		find_circle(1, 0);
		for (int i = 1; i <= top; i++)
			incir[cir[i]] = i;
		cir[0] = cir[top]; cir[top + 1] = cir[1];
		for (int i = 1; i <= top; i++) {
			bfs(cir[i]);
		}
		another_bfs();
		build(1, 1, n);

		for (int i = 1; i <= n; i++) pos[que[i]] = i;
		for (scanf("%d",&m); m; m--) {
			scanf("%s",s + 1);
			if (s[1] == 'M') {
				int a, b, c;
				scanf("%d %d %d",&a,&b,&c);
				modify(a,b,c);			
			} else {
				int a, b;
				scanf("%d %d",&a,&b);
				printf("%d\n",query(a, b));
			}
		}
	}
	return 0;
}
