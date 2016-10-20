#include <bits/stdc++.h>
#define maxn 201000
#define intl long long
using namespace std;

struct str { int v,nex; } edge[maxn << 1];
typedef int arr32[maxn];
arr32 que,fa,fst,sum,smin,mins,val,Sing,done,size,st,ts;
char s[maxn];
int *sing = Sing + 100010;
int n,tp,e;
intl ans;

void make_edge(int a,int b) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b;
	edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a;
}

int bfs(int base) {
	int L = 0, R = 0;
	que[++R] = base;
	fa[base] = 0;
	while(L < R) {
		int u = que[++L];
		for (int i = fst[u]; i; i = edge[i].nex) {
			int v = edge[i].v;
			if(fa[u] == v || done[v]) continue;
			fa[v] = u;
			que[++R] = v;
		}
	}

	int ans = 0, Ans = 1 << 29;
	for (int j = R; j; j--) {
		int u = que[j];
		size[u] = 1;
		int js = 0;
		for (int i = fst[u]; i; i = edge[i].nex) {
			int v = edge[i].v;
			if (fa[u] == v || done[v])  continue;
			size[u] += size[v];
			js = max(js, size[v]);
		}
		js = max(js, R - size[u]);
		if (js < Ans) Ans = js, ans = u;
	}
	return ans;
}

void dfs(int u, int mark) {
	sum[u] = sum[fa[u]] + val[u];
	smin[u] = min(smin[fa[u]] + val[u], val[u]);
	mins[u] = min(mins[fa[u]], sum[u]);
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v;
		if (fa[u] == v || done[v]) continue;
		fa[v] = u;
		dfs(v, mark);
	}
	st[++tp] = u;
	if (mark) {
		if (sum[u] == 0 && smin[u] >= 0) ans++;
		if (sum[u] == 0 && mins[u] >= 0) ans++;
	}
}

bool cmp(int a,int b) {
	return (sum[a] < sum[b]);
}

bool pmc(int a,int b) {
	return (mins[a] > mins[b]);
}

intl proc(int base) {
	intl ans = 0LL;
	for (int i = 1; i <= tp; i++) ts[i] = st[i];
	sort(st + 1, st + tp + 1, cmp);
	sort(ts + 1, ts + tp + 1, pmc);
	int q = 1;
	for (int i = 1; i <= tp; i++) {
		int u = st[i];
		for (; q <= tp && mins[ts[q]] + sum[u] - val[base] >= 0; q++) {
			sing[sum[ts[q]]]++;
		}
		if (smin[u] >= 0)
			ans += (intl) sing[-(sum[u] - val[base])];
	}
	
	for (q--; q > 0; q--)
		sing[sum[ts[q]]] = 0;

	return ans;
}

void solve(int base) {
	int u = bfs(base);
	fa[u] = 0;
    smin[u] = val[u]; sum[u] = val[u];
	mins[u] = val[u]; tp = 0;
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v;
		if (done[v]) continue;
		fa[v] = u;
		dfs(v, 1);
	}
	ans += proc(u);
	
	for (int i = fst[u]; i; i = edge[i].nex) {
		tp = 0;
		int v = edge[i].v;
		if (done[v]) continue;
		fa[v] = u;
		dfs(v, 0);
		ans -= proc(u);
	}
	done[u] = 1;
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v;
		if (done[v]) continue;
		solve(v);
	}
}

int main() {
	//freopen("A.in","r",stdin);
	//freopen("A.out","w",stdout);
	scanf("%d\n",&n);
	scanf("%s",s + 1);
	for (int i = 1; i <= n; i++)
		val[i] = s[i] == '(' ? 1 : -1;
	for (int i = 1; i < n; i++) {
		int a, b;
		scanf("%d %d",&a,&b);
		make_edge(a, b);
	}
	solve(1);
	cout << ans << endl;
	return 0;
}
