#include <bits/stdc++.h>
using namespace std;

int Test, N, M, pt, len, tot, last, num, S, T, tar;
int vis[400010], dfn[400010], low[400010], sta[400010], tx[400010], mark[400010];
int block[4000010], node[4000010], col[4000010], head[4000010];
int st[400010], ne[2000010], go[2000010];

class line{
	public:
	int x, y, dir;
}L[400010];

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

void tarjan(int x){
	vis[x] = 1;
	dfn[x] = low[x] = ++tot;
	sta[++last] = x;
	for (int i = st[x]; i; i = ne[i])
		if (!vis[go[i]]){
			tarjan(go[i]);
			low[x] = min(low[x], low[go[i]]);
			if (low[go[i]] >= dfn[x]){
				mark[x] = 1;
				head[++num] = len + 1;
				for (int j = last; j; j--){
					int y = sta[j];
					block[++len] = y;
					col[len] = num;
					tx[y] ^= num;
					if (x == y)break;
					sta[last--] = 0;
				}
			}
		}else if (vis[go[i]] == 1)
			low[x] = min(dfn[go[i]], low[x]);
}

bool dfs(int x, int p){
	if (x == tar)
		return 0;
	vis[x] = 1;
	bool flag = 1;
	for (int i = st[x]; i; i = ne[i])
		if (L[i >> 1].dir == -1 && vis[go[i]] != 2 && i != (p ^ 1)){
			if (vis[go[i]]){
				L[i >> 1].dir = (i & 1) ^ 1;
				continue;
			}else{
				flag &= dfs(go[i], i);
				L[i >> 1].dir = (i & 1) ^ flag;
			}
		}
	vis[x] = 2;
	return flag;
}

bool work(){
	int up = max(N, M) * 2;
	for (int i = 1; i <= up; i++){
		st[i] = 0;
		tx[i] = 0;
		sta[i] = 0;
		col[i] = 0;
		dfn[i] = 0;
		low[i] = 0;
		vis[i] = 0;
		mark[i] = 0;
		node[i] = 0;
		head[i] = 0;
		block[i] = 0;
	}
	pt = 1;
	last = 0;
	tot = 0;
	num = 0;
	len = 0;
	for (int i = 1; i <= M; i++){
		Add(L[i].x, L[i].y);
		Add(L[i].y, L[i].x);
	}
	tarjan(S);
	mark[T] = 1;
	for (int i = 1; i <= N; i++)
		if (!vis[i])
			return 0;
	for (int i = 1; i <= len; i++)
		if (mark[block[i]])
			node[col[i]]++;
	for (int i = 1; i <= num; i++)
		if (node[i] != 2)return 0;
	len = 0;
	for (int i = 1; i <= up; i++)
		vis[i] = 0;
	for (int x = S; x != T;){
		int c = tx[x];
		tar = 0;
		for (int i = head[c]; col[i] == c; i++)
			if (block[i] != x && mark[block[i]]){
				tar = block[i];
				break;
			}
		dfs(x, 0);
		x = tar;
		tx[x] ^= c;
	}
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

