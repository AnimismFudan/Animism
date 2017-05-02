#include <bits/stdc++.h>
#define maxn 2010
using namespace std;

struct str { int v, nex; } edge[maxn * maxn];

int st[maxn];
int fst[maxn], dfn[maxn], low[maxn], okay[maxn], fa[maxn];
int n, m, cl, e, top, l;
int A[maxn], B[maxn];

void make_edge(int a, int b) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b;
}

void dfs(int u) {
	okay[u] = 1;
	st[++top] = u;
	dfn[u] = low[u] = ++cl; 
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v;
		if (dfn[v] && okay[v]) low[u] = min(low[u], dfn[v]);
		else if (!dfn[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
	}
	if (dfn[u] == low[u]) {
		while (st[top] != u) {
			okay[st[top]] = 0;
			fa[st[top--]] = u;
		}
		okay[st[top]] = 0;
		fa[st[top--]] = u;
	}
}

int main() {
	freopen("F.in","r",stdin);
	freopen("F.out","w",stdout);
	scanf("%d %d %d",&n,&l,&m);
	for (int i = 1; i <= m; i++)
		scanf("%d %d",&A[i],&B[i]);
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= m; j++) {
			if (i == j) continue;
			if (A[i] == A[j] && B[i] == B[j]) {
				printf("NO\n");
				exit(0);
			}
			if (A[i] == A[j]) {
				if (abs(B[i] - B[j]) <= 2 * l) make_edge(i * 2, j * 2 + 1);
			}
			if (B[i] == B[j]) {
				if (abs(A[i] - A[j]) <= 2 * l) make_edge(i * 2 + 1, j * 2);
			}
		}

	for (int i = 1; i <= 2 * m + 1; i++)
		if (!dfn[i]) dfs(i);
	bool flag = true;
	for (int i = 1; i <= m; i++)
		if (fa[i * 2] == fa[i * 2 + 1]) flag = false;
	if (flag) printf("YES\n");
	else printf("NO\n");
	return 0;
}
