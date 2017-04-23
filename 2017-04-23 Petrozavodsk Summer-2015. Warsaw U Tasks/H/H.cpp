#include <bits/stdc++.h>
using namespace std;

int N, T, ans, pt;
int C[50010], R[50010];
int S[50010][230], fa[50010][230];
int st[50010], ne[100010], go[100010], dep[100010];

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

void dfs(int x){
	for (int i = st[x]; i; i = ne[i])
		if (go[i] != fa[x][1]){
			fa[go[i]][1] = x;
			dep[go[i]] = dep[x] + 1;
			dfs(go[i]);
		}
}

void get_all_fa(){
	for (int i = 1; i <= N; i++)
		for (int j = 2; j <= T; j++)
			fa[i][j] = fa[fa[i][j - 1]][1];
}

void get_S(int x){
	for (int i = 1; i <= T; i++){
		S[x][i] = C[x];
		if (fa[x][i])
			S[x][i] += S[fa[x][i]][i];
	}
	for (int i = st[x]; i; i = ne[i])
		if (go[i] != fa[x][1])
			get_S(go[i]);
}

int get_lca(int x, int y){
	if (dep[x] < dep[y])
		swap(x, y);
	for (int i = T; i > 0; i--)
		while (dep[fa[x][i]] >= dep[y])
			x = fa[x][i];
	if (x == y) return x;
	for (int i = T; i > 0; i--)
		while (fa[x][i] != fa[y][i]){
			x = fa[x][i];
			y = fa[y][i];
		}
	return fa[x][1];
}

int get_fa(int x, int p){
	for (int i = T; i > 0; i--)
		for (; p >= i; p -= i)
			x = fa[x][i];
	return x;
}

int main(){
//	freopen("H.in", "r", stdin);
//	freopen("H.out", "w", stdout);
	scanf("%d", &N);
	T = sqrt(N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &C[i]);
	for (int i = 1; i < N; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		Add(x, y);
		Add(y, x);
	}
	dep[1] = 1;
	dfs(1);
	get_all_fa();
	get_S(1);
	for (int i = 1; i <= N; i++)
		scanf("%d", &R[i]);
	for (int i = 1; i < N; i++){
		int t;
		scanf("%d", &t);
		int x = R[i], y = R[i + 1];
		int lca = get_lca(x, y);
		ans = 0;
		if (t <= T){
			int dx = dep[x] - dep[lca];
			int dy = dep[y] - dep[lca];
			dx = dx / t * t;
			dy = dy / t * t;
			int hx = get_fa(x, dx);
			int hy = get_fa(y, dy);
			ans = S[x][t] - S[hx][t] + S[y][t] - S[hy][t];
			ans += C[hx];
			if (hx != hy) ans += C[hy];
		}
		else{
			while (dep[x] > dep[lca] || dep[y] > dep[lca]){
				if (dep[x] < dep[y])
					swap(x, y);
				if (dep[x] > dep[lca])
					ans += C[x];
				x = get_fa(x, t);
			}
			if (x == lca && y == lca)
				ans += C[x];
		}
		printf("%d\n", ans);
	}
	return 0;
}

