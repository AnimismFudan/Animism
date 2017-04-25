#include <bits/stdc++.h>
using namespace std;

struct str { int v, nex; } edge[101000];

int fst[210], vis[210];
int e, n, m;
bool flag;

void make_edge(int a, int b) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b;
	edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a;
}

bool dfs(int u, int c, int a, int b) {
	vis[u] = c;
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v;
		if (v == a || v == b) continue;
		if (!vis[v]) {
			if (!dfs(v, 3 - c,a,b)) return false;
		}
		else if (vis[v] == vis[u]) return false;
	}
	return true;
}

bool judge(int a, int b) {
	for (int i = 1; i <= n; i++) vis[i] = 0;
	for (int i = 1; i <= n; i++) {
		if (vis[i]) continue;
		if (i != a && i != b && !dfs(i, 1, a, b)) return false;
	}
	return true;
}

int main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	flag = false;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) {
		int k;
		for (scanf("%d",&k); k; k--) {
			int j;
			scanf("%d",&j);
			make_edge(i, j);
		}
	}

	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++) {
			flag |= judge(i, j);
		}
	if (flag) printf("Hurrah!\n");
	else printf("Fired.\n");
	return 0;
}
