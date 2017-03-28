#include <bits/stdc++.h>
using namespace std;

#define LL long long

LL S;
int N, Q, pt, res;
int st[100010], ne[200010], go[200010], w[200010];
int s[200010], dep[200010];
LL ss[200010];
int fa[18][100010], Ts[18][100010];

void Add(int x, int y, int ww){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
	w[pt] = ww;
}

void dfs(int x){
	for (int i = st[x]; i; i = ne[i])
		if (go[i] != fa[0][x]){
			dep[go[i]] = dep[x] + 1;
			fa[0][go[i]] = x;
			if (!(w[i] & 1)) Ts[0][go[i]] = w[i];
			else Ts[0][go[i]] = 2e9;
			s[go[i]] = s[x] + (w[i] & 1);
			ss[go[i]] = ss[x] + w[i];
			dfs(go[i]);
		}
}

void get_Twice(){
	for (int step = 1; step <= 17; step++)
		for (int i = 1; i <= N; i++){
			fa[step][i] = fa[step - 1][fa[step - 1][i]];
			Ts[step][i] = min(Ts[step - 1][i], Ts[step - 1][fa[step - 1][i]]);
		}
}

void get_lca(int x, int y, int &z, int &ME){
	ME = 2e9;
	if (dep[x] < dep[y]) swap(x, y);
	for (int step = 17; step >= 0; step--)
		if (dep[fa[step][x]] >= dep[y]){
			ME = min(ME, Ts[step][x]);
			x =  fa[step][x];
		}
	if (x != y){
		for (int step = 17; step >= 0; step--)
			if (fa[step][x] != fa[step][y]){
				x = fa[step][x];
				y = fa[step][y];
				ME = min(ME, Ts[step][x]);
				ME = min(ME, Ts[step][y]);
			}
		z = fa[0][x];
		ME = min(ME, Ts[0][x]);
		ME = min(ME, Ts[0][y]);
	}
	else z = x;
}

int main(){
//	freopen("G.in", "r", stdin);
//	freopen("G.out", "w", stdout);
	scanf("%d%d", &N, &Q);
	S = 0;
	for (int i = 1; i < N; i++){
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		S += w;
		Add(x, y, w);
	}
	dep[1] = 1;
	dfs(1);
	get_Twice();
	for (int i = 1; i <= Q; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		int z, ME;
		get_lca(x, y, z, ME);
		int dist = dep[x] - dep[z] + dep[y] - dep[z];
		int odd = s[x] - s[z] + s[y] - s[z];
		int even = dist - odd;
		LL use = ss[x] - ss[z] + ss[y] - ss[z];
		LL rest = S - use;
		if (even >= 3){
			printf("2\n");
			continue;
		}
		if (even == 0){
			printf("1\n");
			continue;
		}
		res = 1;
		if (odd > ME && even == 1) res = 2;
		if (odd >= ME && even == 2) res = 2;
		if ((((rest + odd) & 1) == 0) && even > 1) res = 2;
		printf("%d\n", res);
	}
}
