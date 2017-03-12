#include <bits/stdc++.h>
using namespace std;
#define LL long long

int M, Q, len, pt;
int data[40010], dep[40010], S[40010][2];
int f[40010], ls[40010];
int st[40010], ne[40010], go[40010], w[40010];
int fa[16][40010];
bool vis[40010], know[40010];

class line{
	public:
	int x, y, w;
	bool used;
}L[10010];

void Add(int x, int y, int ww){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
	w[pt] = ww;
}

int findset(int x){
	if (f[x] == x)return x;
	return f[x] = findset(f[x]);
}

void dfs(int x){
	vis[x] = 1;
	for (int i = st[x]; i; i = ne[i]){
		int y = go[i];
		if (y != fa[0][x]){
			fa[0][y] = x;
			dep[y] = dep[x] + 1;
			S[y][0] = S[x][1] + w[i];
			S[y][1] = S[x][0] - w[i];
			dfs(go[i]);
		}
	}
}

void get_Twice(){
	for (int step = 1; step <= 15; step++)
		for (int i = 1; i <= len; i++)
			fa[step][i] = fa[step - 1][fa[step - 1][i]];
}

void get_data(int x, int p){
	know[x] = 1;
	for (int i = st[x]; i; i = ne[i])
		if (go[i] != p){
			data[go[i]] = w[i] - data[x];
			get_data(go[i], x);
		}
}

int get_lca(int x, int y){
	if (dep[x] < dep[y])
		swap(x, y);
	for (int step = 15; step >= 0; step--)
		if (dep[fa[step][x]] >= dep[y])
			x = fa[step][x];
	if (x == y)return x;
	for (int step = 15; step >= 0; step--)
		if (fa[step][x] != fa[step][y]){
			x = fa[step][x];
			y = fa[step][y];
		}
	return fa[0][x];
}

int main(){
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
	scanf("%d%d", &M, &Q);
	while (M || Q){
		for (int i = 1; i <= M; i++){
			scanf("%d%d%d", &L[i].x, &L[i].y, &L[i].w);
			L[i].used = 0;
			ls[i] = L[i].x;
			ls[i + M] = L[i].y;
		}
		sort(ls + 1, ls + 2 * M + 1);
		len = unique(ls + 1, ls + 2 * M + 1) - ls - 1;
		for (int i = 1; i <= M; i++){
			L[i].x = lower_bound(ls + 1, ls + len + 1, L[i].x) - ls;
			L[i].y = lower_bound(ls + 1, ls + len + 1, L[i].y) - ls;
		}
		for (int i = 1; i <= len; i++){
			st[i] = 0;
			vis[i] = 0;
			f[i] = i;
			know[i] = 0;
			data[i] = 0;
			dep[i] = 0;
			S[i][0] = S[i][1] = 0;
			for (int j = 0; j <= 15; j++)
				fa[j][i] = 0;
		}
		pt = 1;
		for (int i = 1; i <= M; i++)
			if (findset(L[i].x) != findset(L[i].y)){
				f[findset(L[i].x)] = findset(L[i].y);
				L[i].used = 1;
				Add(L[i].x, L[i].y, L[i].w);
				Add(L[i].y, L[i].x, L[i].w);
			}
		for (int i = 1; i <= len; i++)
			if (i == findset(i)){
				dep[i] = 1;
				dfs(i);
			}
		get_Twice();
		for (int i = 1; i <= M; i++)
			if (!L[i].used){
				int x = L[i].x, y = L[i].y;
				if (know[x])continue;
				if (x != y){
					int t = get_lca(x, y);
					int ll = dep[x] - dep[t] + dep[y] - dep[t];
					if (ll & 1)continue;
					int res = S[x][0] + S[y][1] - S[t][0] - S[t][1];
					data[x] = (res + L[i].w) / 2;
				}else data[x] = L[i].w;
				get_data(x, 0);
			}
		for (int i = 1; i <= Q; i++){
			int cx, cy, x, y;
			scanf("%d%d", &cx, &cy);
			x = lower_bound(ls + 1, ls + len + 1, cx) - ls;
			y = lower_bound(ls + 1, ls + len + 1, cy) - ls;
			if (ls[x] != cx || ls[y] != cy){
				printf("*\n");
				continue;
			}
			if (x == y){
				if (know[x])printf("%d\n", data[x]);
				else printf("*\n");
				continue;
			}
			if (know[x] && know[y]){
				printf("%d\n", data[x] + data[y]);
				continue;
			}
			int t = get_lca(x, y);
			if (!t){
				printf("*\n");
				continue;
			}
			int ll = dep[x] - dep[t] + dep[y] - dep[t];
			if (ll & 1){
				int res = S[x][0] + S[y][0];
				res = res - S[t][0] - S[t][1];
				printf("%d\n", res);
			}else printf("*\n");
		}
		scanf("%d%d", &M, &Q);
		printf("-\n");
	}
	return 0;
}
