#include <bits/stdc++.h>
using namespace std;

const int oo = 2e9;
int Test, N, M, pt, ans, S, T;
int dist[1010], q[1010];
int st[1010], ne[20010], go[20010], c[20010];

class line{
	public:
	int x, y, c;
}L[10010];

void Add(int x, int y, int cc){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
	c[pt] = cc;
}

void spfa(int head){
	int l, r;
	q[l = r = 1] = head;
	for (int i = 1; i <= N; i++)
		dist[i] = -1;
	dist[head] = 0;
	for (;l <= r; l++){
		int x = q[l];
		for (int i = st[x]; i; i = ne[i])
			if (dist[go[i]] == -1){
				q[++r] = go[i];
				dist[go[i]] = dist[x] + 1;
			}
	}
}

bool build(){
	for (int i = 1; i <= N; i++)
		dist[i] = -1;
	dist[S] = 0;
	int l, r;
	q[l = r = 0] = S;
	for (; l <= r; l++){
		int x= q[l];
		for (int i = st[x]; i; i = ne[i])
			if (c[i] && dist[go[i]] == -1){
				dist[go[i]] = dist[x] + 1;
				if (go[i] == T) return 1;
				q[++r] = go[i];
			}
	}
	return 0;
}

int dinic(int x, int up){
	if (x == T)return up;
	int w = 0;
	for (int i = st[x]; w < up && i; i = ne[i])
		if (c[i] && dist[go[i]] == dist[x] + 1){
			int t = dinic(go[i], min(up - w, c[i]));
			w += t;
			c[i] -= t;
			c[i ^ 1] += t;
		}
	if (!w) dist[x] = -1;
	return w;
}

int main() {
    freopen("1011.in","r",stdin);
    freopen("1011.out","w",stdout);
    scanf("%d",&Test);
    while (Test--){
    	scanf("%d%d",&N,&M);
    	pt = 1;
    	for (int i = 1; i <= N; i++)
    		st[i] = 0;
    	for (int i = 1; i <= M; i++){
    		scanf("%d%d%d", &L[i].x, &L[i].y, &L[i].c);
    		Add(L[i].x, L[i].y, L[i].c);
    		Add(L[i].y, L[i].x, L[i].c);
    	}
    	spfa(N);
    	pt = 1;
    	for (int i = 1; i <= N; i++)
    		st[i] = 0;
    	for (int i = 1; i <= M; i++){
			if (dist[L[i].x] == dist[L[i].y] + 1){
				Add(L[i].y, L[i].x, L[i].c);
				Add(L[i].x, L[i].y, 0);
			}
			if (dist[L[i].y] == dist[L[i].x] + 1){
				Add(L[i].x, L[i].y, L[i].c);
				Add(L[i].y, L[i].x, 0);
			}
		}
    	S = N;
    	T = 1;
    	ans = 0;
    	while (build())
    		ans += dinic(S, oo);
    	printf("%d\n", ans);
    }
    return 0;
}
