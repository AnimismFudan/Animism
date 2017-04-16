#include <bits/stdc++.h>
#define maxn 1010000
using namespace std;

vector<int> vec[maxn], VEC[maxn], L[maxn], R[maxn], len[maxn], LEN[maxn];
int fromfa[maxn], hop_pas[maxn], fa[maxn], hop[maxn], ans[maxn];
int n, m, top;

int proc(int u, int v, int bias) {
	if (v == -1 || v == -2);
	else if (v < bias) v = -2;
	else v -= bias;
	
	if (u == -1) u = v;
	else if (u == -2 || v == -2) u = -2;
	else if (v == -1 || u == v) u = u;
	else u = -2;
	return u;
}

void dfs(int u) {
	int sz = vec[u].size();
	for (int i = 0; i < sz; i++) {
		int v = vec[u][i];
		if (v == fa[u]) continue;
		fa[v] = u;
		VEC[u].push_back(v);
		LEN[u].push_back(len[u][i]);
		dfs(v);
	}
	int sing = hop[u];
	hop_pas[u] = hop[u];
	sz = VEC[u].size();
	for (int i = 0; i < sz; i++) {
		int v = VEC[u][i];
		hop[u] = proc(hop[u], hop[v], LEN[u][i]);
	}
	for (int i = 0; i < sz; i++) {
		L[u].push_back(hop[VEC[u][i]]);
		R[u].push_back(hop[VEC[u][i]]);
	}
	for (int i = 0; i < sz; i++) {
		L[u][i] = proc(sing, L[u][i], LEN[u][i]);
		R[u][i] = proc(sing, R[u][i], LEN[u][i]);
	}
	for (int i = 1; i < sz; i++) {
		L[u][i] = proc(L[u][i], L[u][i - 1], 0);
	}
	for (int i = sz - 2; i >= 0; i--) {
		R[u][i] = proc(R[u][i], R[u][i + 1], 0);
	}
	return;
}

void DFS(int u) {
	fromfa[u] = proc(fromfa[u], hop_pas[u], 0);
	int sz = VEC[u].size();
	int sing = proc(fromfa[u], hop[u], 0);
	if (sing == 0 || sing == -1) ans[++top] = u;
	for (int i = 0; i < sz; i++) {
		int v = VEC[u][i];
		int l = -1, r = -1;
		if (i > 0) l = L[u][i - 1];
		if (i < sz - 1) r = R[u][i + 1];
		fromfa[v] = proc(l, r, 0);
		fromfa[v] = proc(fromfa[v], fromfa[u], 0);
		fromfa[v] = proc(-1, fromfa[v], LEN[u][i]);
		DFS(v);
	}
	return;
}

int main() {
	//freopen("A.in","r",stdin);
	//freopen("A.out","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i = 1; i < n; i++) {
		int a, b, c;
		scanf("%d %d %d",&a,&b,&c);
		vec[a].push_back(b);
		len[a].push_back(c);
		vec[b].push_back(a);
		len[b].push_back(c);
	}
	for (int i = 1; i <= n; i++) hop[i] = -1;	
	for (int i = 1; i <= m; i++) {
		int a, b;		
		scanf("%d %d",&a,&b);
		hop[a] = b;		
	}
	dfs(1);
	fromfa[1] = -1;
	DFS(1);
	printf("%d\n",top);
	for (int i = 1; i <= top; i++) printf("%d ",ans[i]);
	return 0;
}
