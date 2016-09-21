#include <bits/stdc++.h>
#define maxn 2010000
using namespace std;

struct str { int u,v,c,nex; } edge[maxn];

typedef int arr32[maxn];
arr32 low,dfn,fst,fa,du,que,L,R,st,ok;
int n,m,e,E,top,cl;

void make_edge(int a,int b,int c) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b; edge[e].u = a; edge[e].c = c;
	//edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a; edge[e].u = b; edge[e].c = c;
}

int find(int a) {
	return (fa[a] == a ? a : (fa[a] = find(fa[a])));
}

void dfs(int u) {
	dfn[u] = low[u] = ++cl;
	st[++top] = u; ok[u] = 1;
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v;
		if (!dfn[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if (ok[v]) {
			low[u] = min(low[u], low[v]);
		}
	}
	if (dfn[u] == low[u]) {
		for (; st[top] != u; top--) {
			int v = st[top];
			fa[v] = u;
			ok[v] = 0;
		}
		ok[u] = 0; top--;
		fa[u] = u;
	}
	return;
}

void dp() {
	int l = 0, r = 0;
	for (int i = 1; i <= n; i++) {
		if (find(i) == i && !du[i]) que[++r] = i;
	}

	while (l < r) {
		int u = que[++l];
		for (int i = fst[u]; i; i = edge[i].nex) {
			du[edge[i].v]--;
			if (!du[edge[i].v])
				que[++r] = edge[i].v;
		}
	}

	for (int t = r; t; t--) {
		int u = que[t];
		for (int i = fst[u]; i; i = edge[i].nex) {
			L[u] = max(L[u], L[edge[i].v] + edge[i].c);
		}
	}	
}

int main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d %d",&m,&n);
	for (int i = 1; i <= n; i++)
		L[i] = -2000000000, R[i] = 2000000000;
	bool flag = true;
	for (int i = 1; i <= m; i++) {
		int c; scanf("%d",&c);
		int x,a,b,y;
		scanf("%d %d %d %d",&x,&a,&y,&b);
		if (x && y) {
			if (a + c > b) flag = false;
		} else if (!x && y) {
			R[a] = min(R[a], b - c);
		} else if (x && !y) {
			L[b] = max(L[b], a + c);
		} else {
			make_edge(b, a, c);
		}		
	}
	if (!flag) {
		printf("NO\n");
		return 0;
	}
	for (int i = 1; i <= n; i++) {
		if (!dfn[i]) dfs(i);
	}

	memset(fst,0,sizeof(fst));
	E = e;
	for (int i = 1; i <= E && flag; i++) {
		int a = edge[i].u, b = edge[i].v;
		if ((find(a) == find(b)) && edge[i].c) {
			flag = false;
			break;
		} else if (find(a) != find(b)) {
			make_edge(find(a), find(b), edge[i].c);
			du[fa[b]]++;
		}
	}

	if (!flag) { printf("NO\n"); return 0; }
	
	for (int i = 1; i <= n; i++) {
		if (find(i) == i) continue;
		L[find(i)] = max(L[find(i)], L[i]);
		R[find(i)] = min(R[find(i)], R[i]);
	}

	dp();

	for (int i = 1; i <= n; i++)
		if (L[i] > R[i]) flag = false;

	if (flag) {
		printf("YES\n");
		for (int i = 1; i <= n; i++)
			printf("%d\n",L[find(i)]);
	} else
		printf("NO\n");
	
	return 0;
}
