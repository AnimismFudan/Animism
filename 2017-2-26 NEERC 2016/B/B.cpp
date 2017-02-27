#include <bits/stdc++.h>
#define INF (1 << 30)
using namespace std;

int dfs(int u, int Anc) {
	anc[u] = Anc;
	L[u] = R[u] = ++top;
	if (size[nex[u][0]] > size[nex[u][1]])
		son[u] = nex[u][0];
	else son[u] = nex[u][1];
	if (son[u]) R[u] = dfs(son[u], anc[u]);
	if ((son[u] ^ 1)) R[u] = dfs(son[u] ^ 1, son[u] ^ 1);
}

void tarjan(int u) {
	st[++top] = u;
	dfn[u] = low[u] = ++cl;
	int v;
	while (dfn[v = findmin(u)] == 0) {
		tarjan(v);
		low[u] = min(low[u], low[v]);
	}	
	low[u] = min(low[u], dfn[v]);
	if (dfn[u] == low[u]) {
		do {
			int v = st[top--];
			f[v] = u;
			change(1, 1, tot, v, INF);
			du[v] = INF;
		} while (u != v);
		du[u] = 0;
	}
	return;
}

void solve() {
	int u;
	node sing;
	for (sing = querymin(1, 1, tot, 1, tot); sing.v == 0; sing = querymin(1, 1, tot, 1, tot)) {
		u = sing.p;
		
	}
}

int main() {
	freopen("binary.in","r",stdin);
	freopen("binary.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) {
		bg[i] = bg[i - 1] + len[i - 1] + 1;
		scanf("%s",s + bg[i]);
		len[i] = strlen(s + bg[i]);
	}
	tot = 1;
	for (int t = 1; t <= n; t++) {
		int u = 1;
		for (int i = bg[t]; i < bg[t] + len[t]; i++) {
			if (s[i] == '?') u = add(u, 0);
			else u = add(u, s[i] - '0');
		}
		cast[t][0] = u;
		u = 1;
		for (int i = bg[t]; i < bg[t] + len[t]; i++) {
			if (s[i] == '?') u = add(u, 1);
			else u = add(u, s[i] - '0');
		}
		cast[t][1] = u;
	}
	dfs(1);
	for (int i = 1; i <= tot; i++) dfn[i] = low[i] = INF;
	for (int i = 1; i <= n; i++) {
		dfn[cast[i][0]] = dfn[cast[i][1]] = 0;
	}

	build(1, 1, tot);

	top = 0;
	for (int i = 1; i <= tot; i++) {
		if (!dfn[i]) tarjan(i);
	}

	for (int i = 1; i <= tot; i++) {
		if (L[i] < R[i])
			add(1, 1, tot, L[i] + 1, R[i], 1);
		for (int u = fa[i]; u; u = fa[anc[u]])
			add(1, 1, tot, L[anc[u]], L[u], 1);
		add(1, 1, tot, L[f[u]], L[f[u]], -1);
	}

	solve();
	return 0;
}
