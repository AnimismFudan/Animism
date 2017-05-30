#include <bits/stdc++.h>
#include <sys/timeb.h>
#define maxn 10100
using namespace std;

struct str { int v, nex; } edge[maxn];

int fst[maxn], fa[maxn], dep[maxn];
int n, e, param;

void make_edge(int a, int b) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b;
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
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v;
		fa[v] = u;
		dep[v] = dep[u] + 1;
		dfs(v);
	}
	return;
}

const double bound[10] = { 0, 4.3, 4.8, 5.5, 6.6, 10, 20, 25.7, 30, 100 };

int main() {
	struct timeb t; ftime(&t); srand(t.millitm + t.time * 10000);
	scanf("%d",&param);
	for (int T = 20; T; T--) { 
		n = 10000;
		e = 0;
		memset(fst, 0, sizeof(fst));
		memset(dep, 0, sizeof(dep));
		memset(fa, 0, sizeof(fa));
		for (int i = 1; i < n; i++) {
			make_edge(wnext(0, i - 1, param), i);
		}
		dfs(0);
		double ans = 0;
		for (int i = 0; i < n; i++)
			ans += dep[i];
		printf("%.10lf\n", ans / (double) n);
	}
	return 0;
}
