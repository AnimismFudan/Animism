#include <bits/stdc++.h>
using namespace std;

#define LL long long

int Test, N, M, pt;
LL ans;
int l, r;
int st[100010], ne[100010], go[100010], w[100010];
int W[100010];
class line{
	public:
	int x, y, w;
}P[100010];
int q[10000010];
LL dist[100010];
bool vis[100010];

void Add(int x, int y, int ww){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
	w[pt] = ww;
}

int main(){
	freopen("F.in", "r", stdin);
	freopen("F.out", "w", stdout);
	scanf("%d", &Test);
	for (int tt = 1; tt <= Test; tt++){
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= N; i++)
			scanf("%d", &P[i].y);
		for (int i = 1; i <= N; i++)
			scanf("%d", &P[i].x);
		for (int i = 1; i <= N; i++)
			scanf("%d", &P[i].w);
		memset(st, 0, sizeof(st));
		pt = 0;
		for (int i = 1; i <= N; i++)
			Add(P[i].x, P[i].y, P[i].w);
		for (int i = 1; i <= M; i++)
			scanf("%d", &W[i]);
		l = 1; r = 0;
		for (int i = 1; i <= M; i++)
			if (W[i] == 0){
				q[++r] = i;
				dist[i] = 0;
				vis[i] = 1;
			}
			else dist[i] = 2e18, vis[i] = 0;
		for (; l <= r; l++){
			int x = q[l];
			vis[x] = 0;
			for (int i = st[x]; i; i = ne[i])
				if (dist[go[i]] > dist[x] + w[i]){
					dist[go[i]] = dist[x] + w[i];
					if (!vis[go[i]]){
						q[++r] = go[i];
						vis[go[i]] = 1;
					}
				}
		}
		ans = 0;
		for (int i = 1; i <= M; i++)
			if (W[i] == 2 && ans != -1){
				if (dist[i] != 2e18)
					ans += dist[i];
				else ans = -1;
			}
		printf("Case #%d: ", tt);
		cout << ans << endl;
	}
}