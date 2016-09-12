#include <bits/stdc++.h>
using namespace std;

queue <int> que;

void spfa() {
    for (int i = 1; i <= n; i++) dis[i] = 1 << 29;
    dis[1] = 0;
    que.push(1); ok[1] = 1;
    while (!que.empty()) {
	int u = que.front(); que.pop();
	ok[u] = 0;
	for (int i = fst[u]; i; i = edge[i].nex) {
	    int v = edge[i].v;
	    if (dis[v] <= dis[u] + edge[i].len) continue;
	    dis[v] = dis[u] + edge[i].len;
	    if (!ok[v]) {
		ok[v] = 1;
		que.push(v);
	    }
	}
    }

    for (int i = 1; i <= n; i++) p[i] = i, f[i] = 0;
    sort(p + 1,p + n + 1,cmp);
    f[1] = 1;
    for (int i = 1; i <= n; i++) {
	int u = p[i];
	if (f[u] >= X) mark[u] = 1;
	for (int i = fst[u]; i; i = edge[i].nex) {
	    int v = edge[i].v;
	    if (dis[v] == dis[u] + edge[i].len) {
		mark[v] |= mark[u];
		f[v] += f[u];
	    }
	}
    }
}

void afps() {
    for (int i = 1; i <= n; i++) sid[i] = 1 << 29;
    sid[n] = 0;
    que.push(n); ok[n] = 1;
    while (!que.empty()) {
	int u = que.front(); que.pop();
	ok[u] = 0;
	for (int i = fst[u]; i; i = edge[i].nex) {
	    int v = edge[i].v;
	    if (sid[v] <= sid[u] + edge[i].len) continue;
	    sid[v] = sid[u] + edge[i].len;
	    if (!ok[v]) {
		ok[v] = 1;
		que.push(v);
	    }
	}
    }

    for (int i = 1; i <= n; i++) p[i] = i, g[i] = 0;
    sort(p + 1,p + n + 1,pmc);
    g[n] = 1;
    for (int i = 1; i <= n; i++) {
	int u = p[i];
	if (g[u] >= X) kram[u] = 1;
	for (int i = fst[u]; i; i = edge[i].nex) {
	    int v = edge[i].v;
	    if (sid[v] == sid[u] + edge[i].len) {
		kram[v] |= kram[u];
		g[v] += g[u];
	    }
	}
    }
}

int main() {
    freopen("1003.in","r",stdin);
    freopen("1003.out","w",stdout);
    while (scanf("%d %d",&n,&m) != EOF && n) {
	scanf("%d",&X);
	for (int i = 1; i <= m; i++) {
	    int a,b,c;
	    scanf("%d %d %d",&a,&b,&c);
	    make_edge(a, b, c);
	}
    }

    spfa();
    afps();

    for (int i = 1; i <= n; i++) p[i] = i;
    sort(p + 1,p + n + 1,cmp);
    for (int i = 1; i <= n; i++) {
	int u = p[i];
	if ()
    }
    return 0;
}

