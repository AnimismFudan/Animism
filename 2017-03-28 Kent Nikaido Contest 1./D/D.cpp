#include <bits/stdc++.h>
using namespace std;

const int pp = (1e9) + 7;
int N, M, ans, len, pt;
bool mark[400010];
int q[400010], du[400010], f[400010], fa[400010];
int st[400010], ne[1000010], go[1000010], w[1000010];

class line{
	public:
	int x, y, w;
} P[500010];

int findset(int x){
	if (f[x] == x) return x;
	return f[x] = findset(f[x]);
}

void Add(int x, int y, int ww){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
	w[pt] = ww;
}

void dfs(int x){
	for (int i = st[x]; i; i = ne[i])
		if (go[i] != fa[x]){
			fa[go[i]] = x;
			dfs(go[i]);
		}
}

void dfs_mark(int x){
	for (int i = st[x]; i; i = ne[i])
		if (go[i] != fa[x]){
			dfs_mark(go[i]);
			mark[x] ^= mark[go[i]];
		}
	if (mark[x])
		for (int i = st[x]; i; i = ne[i])
			if (go[i] == fa[x])
				ans = (ans + w[i]) % pp;
}

int main(){
//	freopen("D.in", "r", stdin);
//	freopen("D.out", "w", stdout);
	scanf("%d%d", &N, &M);
	ans = 0;
	P[0].w = 1;
	for (int i = 1; i <= N; i++)
		f[i] = i;
	for (int i = 1; i <= M; i++){
		scanf("%d%d", &P[i].x, &P[i].y);
		P[i].w = P[i - 1].w * 2 % pp;
		ans = (ans + P[i].w) % pp;
		du[P[i].x]++;
		du[P[i].y]++;
		if (findset(P[i].x) != findset(P[i].y)){
			Add(P[i].x, P[i].y, P[i].w);
			Add(P[i].y, P[i].x, P[i].w);
			f[findset(P[i].x)] = findset(P[i].y);
		}
	}
	dfs(1);
	len = 0;
	for (int i = 1; i <= N; i++)
		if (du[i] & 1)
			q[++len] = i;
	for (int i = 2; i <= len; i += 2){
		int x, y;
		x = q[i - 1];
		y = q[i];
		mark[x] ^= 1;
		mark[y] ^= 1;
	}
	dfs_mark(1);
	printf("%d\n", ans);
}
