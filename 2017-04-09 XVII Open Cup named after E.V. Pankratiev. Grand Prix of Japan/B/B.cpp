#include <bits/stdc++.h>
#define maxn 401000
using namespace std;

struct str { int v, nex; } edge[maxn << 1];

typedef int arr32[maxn];

arr32 fst, dfn, low, fa, size;
int cnt[2], e, n, N, cl;
int mark[maxn];
int done[maxn << 1];

void make_edge(int a, int b) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b;
	edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a;
}

int dfs(int u, int rt, int pas) {
	dfn[u] = low[u] = ++cl;
	fa[u] = rt;
	for (int i = fst[u]; i; i = edge[i].nex) {
		if ((i ^ pas) == 1) continue;
		if (!done[i]) size[u]++;
		done[i] = done[i ^ 1] = 1;
		int v = edge[i].v;
		if (dfn[v]) {
			low[u] = min(low[u], dfn[v]);
		} else {
			size[u] += dfs(v, rt, i);
			low[u] = min(low[u], low[v]);
		}
		if (low[v] <= dfn[u]) mark[i / 2] = 1;
		else mark[i / 2] = 0;
	}
	return size[u];
}

int main() {
	//freopen("B.in","r",stdin);
	//freopen("B.out","w",stdout);
	scanf("%d",&n);
	N = 2 * n + 1;
	e = 1;
	for (int i = 1; i <= N; i++) {
		int a, b;
		scanf("%d %d",&a,&b);
		make_edge(a, b + N);
	}

	for (int i = 1; i <= N; i++) {
		if (!dfn[i]) {			
			size[i] = dfs(i, i, 0);
			cnt[size[i] & 1]++;
		}
	}

	for (int i = 1; i <= N; i++) {
		int a = edge[i * 2].v;
		int b = edge[i * 2 + 1].v;
		if (size[a] > size[b]) swap(a, b);
		int cn[2] = { cnt[0], cnt[1] };
		if (!mark[i]) {
			cn[size[fa[a]] & 1]--;
			cn[size[a] & 1]++;
			cn[(size[fa[a]] - size[a] - 1) & 1]++;
		}
		else {
			cn[size[fa[a]] & 1]--;
			cn[(size[fa[a]] - 1) & 1]++;
		}
		if (cn[1]) printf("NG\n");
		else printf("OK\n");
	}
	return 0;
}
