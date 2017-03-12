#include <bits/stdc++.h>
using namespace std;

const int oo = 1e8;
int N, M, pt, ans, l, r, S, T;
int q[2000010], dist[1010];
bool vis[1010];
int st[1010], ne[200010], go[200010], c[200010];

class line{
	public:
	int x, y, w;
}L[10010];

void Add(int x, int y, int cc){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
	c[pt] = cc;
}

bool build(){
	for (int i = S; i <= T; i++)
		dist[i] = -1;
	dist[S] = 0;
	q[l = r = 0] = S;
	for (; l <= r; l++){
		int x = q[l];
		for (int i = st[x]; i; i = ne[i])
			if (c[i] && dist[go[i]] == -1){
				dist[go[i]] = dist[x] + 1;
				if (go[i] == T)return 1;
				q[++r] = go[i];
			}
	}
	return 0;
}

int dinic(int x, int up){
	if (x == T) return up;
	int w = 0;
	for (int i = st[x]; w < up && i; i = ne[i])
		if (c[i] && dist[go[i]] == dist[x] + 1){
			int t = dinic(go[i], min(up - w, c[i]));
			w += t;
			c[i] -= t;
			c[i ^ 1] += t;
		}
	if (!w)dist[x] = -1;
	return w;
}

void spfa(int head){
	for (int i = 1; i <= N; i++)
		dist[i] = 1e9;
	q[l = r = 0] = head;
	vis[head] = 1;
	dist[head] = 0;
	for (;l <= r; l++){
		int x = q[l];
		vis[x] = 0;
		for (int i = st[x]; i; i = ne[i])
			if (dist[go[i]] > dist[x] + c[i]){
				dist[go[i]] = dist[x] + c[i];
				if (!vis[go[i]]){
					q[++r] = go[i];
					vis[go[i]] = 1;
				}
			}
	}
}

int main(){
	freopen("I.in", "r", stdin);
	freopen("I.out", "w", stdout);
	scanf("%d%d", &N, &M);
	pt = 1;
	for (int i = 1; i <= M; i++){
		scanf("%d%d%d", &L[i].x, &L[i].y, &L[i].w);
		L[i].x++;
		L[i].y++;
		Add(L[i].x, L[i].y, L[i].w);
		Add(L[i].y, L[i].x, L[i].w);
	}
	spfa(1);
	memset(st, 0, sizeof(st));
	pt = 1;
	S = 1;
	T = 2 * N;
	for (int i = 1; i <= N; i++)
		if (i != 1 && i != N){
			Add(i, i + N, 1);
			Add(i + N, i, 0);
		}
		else{
			Add(i, i + N, oo);
			Add(i + N, i, 0);
		}
	for (int i = 1; i <= M; i++){
		if (dist[L[i].x] == dist[L[i].y] + L[i].w){
			Add(L[i].y + N, L[i].x, oo);
			Add(L[i].x, L[i].y + N, 0);
		}
		if (dist[L[i].y] == dist[L[i].x] + L[i].w){	
			Add(L[i].x + N, L[i].y, oo);
			Add(L[i].y, L[i].x + N, 0);
		}
	}
	ans = 0;
	while (build())
		ans += dinic(S, oo);
	if (ans == oo)printf("IMPOSSIBLE\n");
	else printf("%d\n", ans);
	return 0;
}
