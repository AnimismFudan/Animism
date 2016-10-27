#include <bits/stdc++.h>
using namespace std;

int Test, N, M, S, T, pt, l, r;
int q[4000010], c[4000010];
int st[400010], ne[2000010], go[2000010];
int fa[400010], faw[400010], dep[400010], vis[400010];

class line{
	public:
	int x, y, dir;
}L[1000010];

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

void dfs(int x){
	vis[x] = 1;
	for (int i = st[x]; i; i = ne[i])
		if (go[i] != fa[x]){
			if (!vis[go[i]]){
				dep[go[i]] = dep[x] + 1;
				fa[go[i]] = x;
				faw[go[i]] = i;
				dfs(go[i]);
			}
		}
}

bool work(){
	for (int i = 1; i <= N; i++){
		st[i] = 0;
		fa[i] = 0;
		dep[i] = 0;
		vis[i] = 0;
	}
	pt = 1;
	for (int i = 1; i <= M; i++){
		Add(L[i].x, L[i].y);
		Add(L[i].y, L[i].x);
	}
	dep[S] = 1;
	dfs(S);
	l = r = 0;
	q[0] = T;
	c[0] = 0;//0 向下 1 向上
	for (int i = 1; i <= N; i++)
		vis[i] = 0;
	for (; l <= r; l++){
		int x = q[l];
		int cc = c[l];
		int t = faw[x] >> 1;
		int y = fa[x];
		if (vis[x])
			continue;
		vis[x] = 1;
		if (t && L[t].dir == -1){
			L[t].dir = (faw[x] & 1) ^ cc;
			q[++r] = y;
			c[r] = cc;
		}
		for (int i = st[y]; i; i = ne[i])
			if (fa[go[i]] != y && fa[y] != go[i] && L[i >> 1].dir == -1){
				L[i >> 1].dir = (i & 1) ^ cc;
				q[++r] = go[i];
				c[r] = cc ^ 1;
			}
	}
	for (int i = 1; i <= M; i++)
		if (L[i].dir == -1)
			return 0;
	return 1;
}

register char *_sp __asm__("rsp");

int main(){
	const int size = 64 * 1024 * 1024;
	static char *sys, *mine(new char[size] + size - 4096);
	sys = _sp;
	_sp = mine;
	
	freopen("K.in", "r", stdin);
	freopen("K.out", "w", stdout);
	scanf("%d", &Test);
	while (Test--){
		scanf("%d%d", &N, &M);
		scanf("%d%d", &S, &T);
		for (int i = 1; i <= M; i++){
			scanf("%d%d", &L[i].x, &L[i].y);
			L[i].dir = -1;
		}
		if (work()){
			printf("Yes\n");
			for (int i = 1; i <= M; i++)
				if (L[i].dir == 0)printf("%d %d\n", L[i].x, L[i].y);
				else if (L[i].dir == 1)printf("%d %d\n", L[i].y, L[i].x);
				else printf("0 0\n");
		}else printf("No\n");
	}
	
	_sp = sys;
	return 0;
}

