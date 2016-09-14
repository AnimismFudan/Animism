#include <bits/stdc++.h>
#define INF (1 << 30)
using namespace std;

map<int,map<int,int> > mark;

struct point { double x,y; } dot[10100];

struct str { int v,nex,cap; double cost; } edge[2010000];
double ans,dis[10100];
int e = 1,s,t,n;
int que[1010000],fst[10100],pas[10100];
int top,X,Y;
int A[10100],B[10100],ok[10100],du[10100],ta,tb;

double S(double a) { return a * a; }

void make_edge(int a,int b,int cap,double cost) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b; edge[e].cap = cap; edge[e].cost =  cost;
	edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a; edge[e].cap = 0  ; edge[e].cost = -cost;
}

bool spfa() {
	for (int i = 1; i <= top; i++)
		dis[i] = INF;
	int L = 0, R = 0;
	dis[s] = 0;
	que[++R] = s; ok[s] = 1;
	while (L < R) {
		int u = que[++L];
		ok[u] = 0;
		for (int i = fst[u]; i; i = edge[i].nex) {
			int v = edge[i].v;
			if (edge[i].cap && dis[v] > dis[u] + edge[i].cost) {
				dis[v] = dis[u] + edge[i].cost;
				pas[v] = i;
				if (!ok[v]) que[++R] = v, ok[v] = 1;
			}
		}
	}

	if (dis[t] > INF - 1) return false;
	int flow = INF;
	for (int u = t; u != s; u = edge[pas[u] ^ 1].v) {
		flow = min(flow, edge[pas[u]].cap);		
	}
	ans += (double) flow * dis[t];
	for (int u = t; u != s; u = edge[pas[u] ^ 1].v) {
		edge[pas[u]].cap -= flow;
		edge[pas[u] ^ 1].cap += flow;
	}
	return true;
}

void solve() {
	while (spfa());
}

int main() {
	//freopen("H.in","r",stdin);
	//freopen("H.out","w",stdout);
	scanf("%d",&n);
	scanf("%d %d",&X,&Y);
	mark[X][Y] = ++top;
	
	for (int i = 1; i <= n; i++) {
		int x1,y1,x2,y2;
		scanf("%d %d %d %d",&x1, &y1, &x2, &y2);
		if (!mark[x1][y1]) mark[x1][y1] = ++top;
		if (!mark[x2][y2]) mark[x2][y2] = ++top;
		int a = mark[x1][y1], b = mark[x2][y2];
		du[a]++; du[b]--;
		dot[a] = (point) { (double) x1, (double) y1 };
		dot[b] = (point) { (double) x2, (double) y2 };
		ans += sqrt((double)S(x1 - x2) + (double) S(y1 - y2));
	}
	
	s = ++top; t = ++top;
	for (int i = 1; i <= top; i++) {
		if (du[i] > 0) {
			make_edge(s, i, du[i], 0);
			A[++ta] = i;
		}
		else if (du[i] < 0){
			make_edge(i, t, -du[i], 0);
			B[++tb] = i;
		}
	}

	for (int i = 1; i <= ta; i++)
		for (int j = 1; j <= tb; j++)
			make_edge(A[i], B[j], INF, sqrt(S(dot[A[i]].x - dot[B[j]].x) + S(dot[A[i]].y - dot[B[j]].y)));

	solve();

	printf("%.10lf\n",ans);
	return 0;
}
