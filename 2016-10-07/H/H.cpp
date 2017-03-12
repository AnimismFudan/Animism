#include <bits/stdc++.h>
using namespace std;
#define LL long long

int R, C, Q, pt, last, tot, num;
int st[10010], ne[200010], go[200010], dep[10010];
int fa[10010], faw[10010];
int dfn[10010], low[10010], sta[10010], vis[10010], mark[10010];

class line{
	public:
	int x, y;
}L[100010];

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

void tarjan(int x, int p){
	dfn[x] = low[x] = ++tot;
	sta[++last] = x;
	vis[x] = 1;
	for (int i = st[x]; i; i = ne[i])
		if ((i ^ p) != 1){
			if (vis[go[i]] == 0){
				tarjan(go[i], i);
				low[x] = min(low[x], low[go[i]]);
			}else if (vis[go[i]] == 1)	low[x] = min(low[x], dfn[go[i]]);
		}
	if (dfn[x] == low[x]){
		++num;
		int p;
		do{
			p = sta[last];
			mark[p] = num;
			vis[p] = 2;
			sta[last--] = 0;
		}while (p != x);
	}
}

void dfs(int x){
	for (int i = st[x]; i; i = ne[i]){
		int y = mark[go[i]];
		if (y != fa[x]){
			fa[y] = x;
			faw[y] = i ^ 1;
			dep[y] = dep[x] + 1;
			dfs(y);
		}
	}
}

int main(){
	freopen("H.in", "r", stdin);
	freopen("H.out", "w", stdout);
	scanf("%d%d%d", &R, &C, &Q);
	while (R || C || Q){
		pt = 1;
		tot = 0;
		num = 0;
		for (int i = 1; i <= R; i++)
			st[i] = dfn[i] = low[i] = vis[i] = mark[i] = fa[i] = faw[i] = 0;
		for (int i = 1; i <= C; i++){
			scanf("%d%d", &L[i].x, &L[i].y);
			Add(L[i].x, L[i].y);
			Add(L[i].y, L[i].x);
		}
		for (int i = 1; i <= R; i++)
			if (!vis[i])
				tarjan(i, 0);
		for (int i = 1; i <= R; i++)
			st[i] = 0;
		pt = 1;
		for (int i = 1; i <= C; i++)
			if (mark[L[i].x] != mark[L[i].y]){
				Add(mark[L[i].x], L[i].y);
				Add(mark[L[i].y], L[i].x);
			}
		for (int i = 1; i <= R; i++)
			if (!fa[i])
				dfs(i);
		for (int i = 1; i <= Q; i++){
			int x, y;
			scanf("%d%d", &x, &y);
			bool flag = 1;
			while (mark[x] != mark[y]){
				if (dep[mark[x]] < dep[mark[y]])
					swap(x, y);
				int t = faw[mark[x]];
				if (go[t ^ 1] != x){
					flag = 0;
					break;
				}
				x = go[t];
			}
			if (x != y)flag = 0;
			flag ? printf("Y\n"):printf("N\n");
		}
		printf("-\n");
		scanf("%d%d%d", &R, &C, &Q);
	}
	return 0;
}
