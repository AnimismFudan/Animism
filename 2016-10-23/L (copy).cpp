#include <bits/stdc++.h>
using namespace std;

int Test, N, M, pt, dist_min, S, T, ans;
int st[1010], ne[20010], go[20010], w[20010];
int dist[1010], q[1000010], in[1010], sum[1010];
bool vis[1010];
int d[2][1010], s[2][1010];

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

void spfa(int head, bool flag){
	memset(st, 0, sizeof(st));
	pt = 0;
	for (int i = 1; i <= M; i++){
		int x = P[i].x, y = P[i].y;
		if (flag)swap(x, y);
		Add(x, y, P[i].w);
	}
	int l, r;
	for (int i = 1; i <= N; i++)
		dist[i] = 2e9;
	dist[head] = 0;
	vis[head] = 1;
	for (q[l = r = 0] = head; l <= r; l++){
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

void get_s(int head, bool flag){
	memset(in, 0, sizeof(in));
	memset(sum, 0, sizeof(sum));
	memset(st, 0, sizeof(st));
	pt = 0;
	for (int i = 1; i <= M; i++){
		int x = P[i].x, y = P[i].y;
		if (flag)swap(x, y);
		if (dist[x] + P[i].w == dist[y]){
			Add(x, y, P[i].w);
			in[y]++;
		}
	}
	int l = 1, r = 0;
	q[++r] = head;
	sum[head] = 1;
	for (; l <= r; l++){
		int x = q[l];
		for (int i = st[x]; i; i = ne[i]){
			sum[go[i]] += sum[x];
			in[go[i]]--;
			if (!in[go[i]])
				q[++r] = go[i];
		}
	}
}

void work(int S, int flag){
	spfa(S, flag);
	get_s(S, flag);
	for (int i = 1; i <= N; i++){
		d[flag][i] = dist[i];
		s[flag][i] = sum[i];
	}
}

int main(){
	freopen("L.in", "r", stdin);
	freopen("L.out", "w", stdout);
	scanf("%d", &Test);
	while (Test--){
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= M; i++)
			scanf("%d%d%d", &P[i].x, &P[i].y, &P[i].w);
		scanf("%d%d", &S, &T);
		work(S, 0);
		work(T, 1);
		ans = s[0][T];
		dist_min = d[0][T];
		for (int i = 1; i <= M; i++){
			int x = P[i].x;
			int y = P[i].y;
			int l = d[0][x] + d[1][y] + P[i].w;
			if (l == dist_min + 1)
				ans += s[0][x] * s[1][y];
		}
		printf("%d\n", ans);
	}
	return 0;
}
