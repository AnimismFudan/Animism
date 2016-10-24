#include <bits/stdc++.h>
#define INF (1 << 30)
using namespace std;

struct str { int v,nex,cap; } edge[1010000];

const int x_[4] = { 0, 0, -1, 1 };
const int y_[4] = { 1,-1,  0, 0 };

char S[20][20];
int mark[1010][1010];
int fst[101000],que[101000],quex[101000],quey[101000],d[101000],vis[101000],Vis[22][22],dis[22][22];
int Dis[1010][210];
int top,Js,e,cl,N,M,s,t,T;

void init() {
    top = Js = 0;
}

void bfs(int X,int Y) {
    if (S[X][Y] != 'D') return;
    top++; dis[X][Y] = 0;
    cl++; Vis[X][Y] = cl;
    int L = 0, R = 0;
    quex[++R] = X;
    quey[R] = Y;
    while (L < R) {
	int x = quex[++L];
	int y = quey[L];
	for (int t = 0; t < 4; t++) {
	    int a = x + x_[t], b = y + y_[t];
	    if (a > N || a < 1 || b > M || b < 1) continue;
	    if (S[a][b] == 'X' || S[a][b] == 'D') continue;
	    if (Vis[a][b] == cl) continue;
	    dis[a][b] = dis[x][y] + 1;
	    quex[++R] = a;
	    quey[R] = b;
	    Vis[a][b] = cl;
	}
    }

    for (int i = 1; i <= Js; i++)
	Dis[i][top] = INF;
    int js = 0;
    for (int i = 1; i <= N; i++)
	for (int j = 1; j <= M; j++) {
	    if (S[i][j] != '.') continue;
	    js++;
	    if (Vis[i][j] == cl)
		Dis[js][top] = dis[i][j];
	}
}

void make_edge(int a,int b,int c) {
    edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b; edge[e].cap = c;
    edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a; edge[e].cap = 0;
}

bool bfs() {
    int L = 0, R = 0;
    que[++R] = s; vis[s] = ++cl; d[s] = 0;
    while (L < R) {
	int u = que[++L];
	for (int i = fst[u]; i; i = edge[i].nex) {
	    int v = edge[i].v;
	    if (edge[i].cap && (vis[v] != cl)) {
		vis[v] = cl;
		que[++R] = v;
		d[v] = d[u] + 1;
	    }
	}
    }
    return (vis[t] == cl);
}

int dfs(int u,int ma) {
    int f, flow = 0;
    if (!ma || u == t) return ma;
    for (int i = fst[u]; i; i = edge[i].nex) {
	int v = edge[i].v;
	if ((d[v] == d[u] + 1) && (f = dfs(v, min(edge[i].cap, ma)))) {
	    flow += f; ma -= f;
	    edge[i].cap -= f; edge[i ^ 1].cap += f;
	    if (!ma) return flow;
	}
    }
    d[u] = INF;
    return flow;
}

bool judge(int mid) {
    e = 1;
    int tp = Js;
    for (int i = 1; i <= top; i++)
	for (int j = 1; j <= mid; j++)
	    mark[i][j] = ++tp;
    s = ++tp; t = ++tp;
    
    for (int i = 1; i <= tp; i++) fst[i] = 0;
    
    for (int i = 1; i <= Js; i++) {
	for (int j = 1; j <= top; j++) {
	    if (Dis[i][j] <= mid)
		make_edge(i, mark[j][Dis[i][j]], 1);
	}
    }
    
    for (int i = 1; i <= top; i++) {
	for (int j = 1; j < mid; j++)
	    make_edge(mark[i][j], mark[i][j + 1], INF);
	for (int j = 1; j <= mid; j++)
	    make_edge(mark[i][j], t, 1);
    }
    
    for (int i = 1; i <= Js; i++)
	make_edge(s, i, 1);
    int ans = 0;
    while (bfs()) ans += dfs(s, INF);
    return (ans == Js);
}

void solve() {
    int L = 0, R = 145;
    while (L < R) {
	int mid = (L + R) >> 1;
	if (judge(mid)) R = mid;
	else L = mid + 1;
    }
    if (L == 145) printf("impossible\n");
    else printf("%d\n",L);
}

int main() {
    for (scanf("%d",&T); T; T--) {
	scanf("%d %d",&N,&M);
	init();
	for (int i = 1; i <= N; i++) {
	    scanf("%s",S[i] + 1);
	    for (int j = 1; j <= M; j++)
		if (S[i][j] == '.') Js++;
	}
	for (int a = 1; a < N; a++) bfs(a, 1);
	for (int b = 1; b < M; b++) bfs(N, b);
	for (int a = N; a > 1; a--) bfs(a, M);
	for (int b = M; b > 1; b--) bfs(1, b);
	solve();
    }
    return 0;
}