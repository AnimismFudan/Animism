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
int top;
int st[maxn];

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

void dfs(int u, int mark) {
	int mi = 0;
	size[u] = 1;
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v;
		if (fa[u] == v) continue;
		fa[v] = u;
		dep[v] = dep[u] + 1;
		dfs(v, mark);
		size[u] += size[v];
		mi = max(mi, size[v]);
		mdep[u] = max(mdep[u], mdep[v]);
	}
	if (!mark) return;
	//if (dep[u] > anss) top = 0;
	if (dep[u] > anss) {
		rt = u;
		//st[++top] = u;
		anss = dep[u];
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

const double bound[10] = { -1, 12.1, 13.4, 15, 20, 28, 42, 50, 57, 100000 };

int main() {
	struct timeb t; ftime(&t); srand(t.millitm + t.time * 10000);
	freopen("K.in","w",stdout);
	scanf("%d",&param);
	//param = -3;
	int T = 100;
	printf("%d\n", T);
	for (; T; T--) { 
		n = 10000;
		printf("%d ", n);
		e = 0;
		memset(fst, 0, sizeof(fst));
		memset(dep, 0, sizeof(dep));
		memset(fa, 0, sizeof(fa));
		memset(mdep, 0, sizeof(mdep));
		for (int i = 1; i < n; i++) {
			//make_edge(wnext(0, i - 1, param), i);
			printf("%d ",wnext(0, i - 1, param));
		}
		putchar('\n');		
	}
	return 0;
}
