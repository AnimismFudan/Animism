#include <bits/stdc++.h>
#include <sys/timeb.h>
#define maxn 10100
using namespace std;

struct str { int v, nex; } edge[maxn << 1];

int size[maxn];
int fst[maxn], fa[maxn], mdep[maxn], dep[maxn];
int n, e, param;
int rt;
int anss;

void make_edge(int a, int b) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b;
	edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a;
}

int random(int a, int b) {
	return a + abs(rand()) % (b - a + 1);	
}

int wnext(int a, int b, int type) {
	int result = random(a, b);
	for (int i = 0; i < type; i++)
		result = max(result, random(a, b));
	for (int i = 0; i < -type; i++)
		result = min(result, random(a, b));
	return result;
}

void dfs(int u) {
	int mi = 0;
	size[u] = 1;
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v;
		if (fa[u] == v) continue;
		fa[v] = u;
		dep[v] = dep[u] + 1;
		dfs(v);
		size[u] += size[v];
		mi = max(mi, size[v]);
		mdep[u] = max(mdep[u], mdep[v]);
	}
	mdep[u] = max(mdep[u], dep[u]);
	mi = max(mi, n - size[u]);
	if (mi < anss) {
		anss = mi;
		rt = u;
	}
	return;
}

int find_rt() {
	int ans = 0;
	int anss = 0;
	for (int i = 1; i <= n; i++) {
		if (min(size[i], n - size[i]) > anss) {
			anss = min(size[i], n - size[i]);
			ans = i;
		}
	}
	return ans;
}

const double bound[10] = { 0, 4.3, 4.8, 5.5, 6.0, 10, 15, 19.5, 23.5, 100 };

int main() {
	struct timeb t; ftime(&t); srand(t.millitm + t.time * 10000);
	scanf("%d",&param);
	//param = -4;
	for (int T = 20; T; T--) { 
		n = 10000;
		e = 0;
		memset(fst, 0, sizeof(fst));
		memset(dep, 0, sizeof(dep));
		memset(fa, 0, sizeof(fa));
		memset(mdep, 0, sizeof(mdep));
		for (int i = 1; i < n; i++) {
			make_edge(wnext(0, i - 1, param), i);
		}
		anss = 1000000;
		dfs(0);
		memset(fa, 0, sizeof(fa));
		memset(dep, 0, sizeof(dep));
		fa[rt] = 0; dep[rt] = 0;		
		//rt = 100;
		dfs(rt);
		double ans = 0;
		for (int i = 0; i < n; i++)
			ans += dep[i];
		printf("%d %.10lf\n", rt, ans / (double) n);
	}
	return 0;
}
