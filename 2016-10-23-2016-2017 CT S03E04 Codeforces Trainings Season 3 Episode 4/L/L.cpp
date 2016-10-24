#include <bits/stdc++.h>
using namespace std;

int Test, N, M, pt, dist_min, S, T, ans;
int st[2010], ne[40010], go[40010], w[40010];
int dist[2010], q[1000010], in[2010], sum[2010];
bool vis[2010];

class line{
	public:
	int x, y, w;
}P[10010];

void Add(int x, int y, int ww){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
	w[pt] = ww;
}

void spfa(){
	memset(st, 0, sizeof(st));
	pt = 0;
	for (int i = 1; i <= M; i++)
		Add(P[i].x, P[i].y, P[i].w);
	int l, r;
	for (int i = 1; i <= N; i++)
		dist[i] = 2e9;
	dist[S] = 0;
	vis[S] = 1;
	for (q[l = r = 0] = S; l <= r; l++){
		int x = q[l];
		vis[x] = 0;
		for (int i = st[x]; i; i = ne[i]){
			int y = go[i];
			if (dist[y] > dist[x] + w[i]){
				dist[y] = dist[x] + w[i];
				if (!vis[y]){
					vis[y] = 1;
					q[++r] = y;
				}
			}
		}
	}
}

void get_s(){
	memset(in, 0, sizeof(in));
	memset(sum, 0, sizeof(sum));
	memset(st, 0, sizeof(st));
	pt = 0;
	for (int i = 1; i <= M; i++){
		int x = P[i].x, y = P[i].y;
		if (dist[x] + P[i].w == dist[y]){
			Add(x, y, P[i].w);
			in[y]++;
			Add(N + x, N + y, P[i].w);
			in[N + y]++;
		}
		if (dist[x] + P[i].w == dist[y] + 1){
			Add(x, N + y, P[i].w);
			in[N + y]++;
		}
	}
	int l = 1, r = 0;
	q[++r] = S;
	sum[S] = 1;
	q[++r] = N + S;
	sum[N + S] = 0;
	for (; l <= r; l++){
		int x = q[l];
		for (int i = st[x]; i; i = ne[i]){
			int y = go[i];
			sum[y] += sum[x];
			in[y]--;
			if (!in[y])
				q[++r] = y;
		}
	}
	ans = sum[T] + sum[N + T];
}

void work(){
	spfa();
	get_s();
}

int main(){
	scanf("%d", &Test);
	while (Test--){
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= M; i++)
			scanf("%d%d%d", &P[i].x, &P[i].y, &P[i].w);
		scanf("%d%d", &S, &T);
		work();
		printf("%d\n", ans);
	}
	return 0;
}