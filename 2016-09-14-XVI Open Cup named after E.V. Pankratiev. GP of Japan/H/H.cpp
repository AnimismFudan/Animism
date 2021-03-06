#include <bits/stdc++.h>
#define INF (1 << 30)
using namespace std;

map<int,map<int,int> > mark;

struct point { double x,y; } dot[10100];

struct str { int v,nex; double len; } edge[2010000];
double ans,dis[10100];
int e = 1,s,t,n,tp,sou[10100];
int que[1010000],fst[10100],pas[10100];
int top,X,Y,vis[10100],nex[10100];
int A[10100],B[10100],ok[10100],du[10100],lp[10100],rp[10100],nl,nr,ta,tb;
double Mark[10100],slk[10100];

double S(double a) { return a * a; }

void make_edge(int a,int b, double cost) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b; edge[e].len =  cost;
	edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a; edge[e].len = -cost;
}

int sig(double a) { return fabs(a) < (1e-8); }

bool path(int u) {
	vis[u] = 1;
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v;
		if (sig(edge[i].len - Mark[u] - Mark[v])) {
			if (vis[v]) continue;
			vis[v] = 1;
			if (!nex[v] || path(nex[v])) {
				nex[v] = u, nex[u] = v;
				return true;
			}
		} else {
			slk[v] = min(slk[v], edge[i].len - Mark[u] - Mark[v]);
		}
	}
	return false;
}

void km() {
	for (int i = 1; i <= nl; i++) Mark[lp[i]] = INF;
	for (int i = 1; i <= nr; i++) Mark[rp[i]] = 0;
	for (int i = 1; i <= nl; i++) {
		int u = lp[i];
		for (int j = fst[u]; j; j = edge[j].nex) {
			Mark[u] = min(Mark[u], edge[j].len);
		}
	}

	for (int i = 1; i <= nl; i++) {
		int u = lp[i];
		for (int j = 1; j <= nr; j++)
			slk[rp[j]] = 1 << 28;
		for (int j = 1; j <= nl; j++)
			vis[rp[j]] = vis[lp[j]] = 0;

		while (!path(u)) {
			double sing = 1 << 28;
			for (int j = 1; j <= nr; j++) {
				int v = rp[j];
				if (!vis[v]) sing = min(sing, slk[v]);
			}

			for (int j = 1; j <= nl; j++) if (vis[lp[j]]) Mark[lp[j]] += sing;
			for (int j = 1; j <= nr; j++) if (vis[rp[j]]) Mark[rp[j]] -= sing;
			for (int j = 1; j <= nr; j++) slk[rp[j]] = 1 << 28, vis[rp[j]] = 0;
		}
	}

	for (int i = 1; i <= nl; i++) ans += Mark[lp[i]];
	for (int i = 1; i <= nr; i++) ans += Mark[rp[i]];
	
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
	tp = 0;
	for (int i = 1; i <= top; i++) {
		if (du[i] > 0)
			for (int j = 1; j <= du[i]; j++)
				lp[++nl] = ++tp, sou[tp] = i;
		else if (du[i] < 0)
			for (int j = 1; j <= -du[i]; j++)
				rp[++nr] = ++tp, sou[tp] = i;
	}

	for (int i = 1; i <= nl; i++)
		for (int j = 1; j <= nr; j++)
			make_edge(lp[i], rp[j], sqrt(S(dot[sou[lp[i]]].x - dot[sou[rp[j]]].x) + S(dot[sou[lp[i]]].y - dot[sou[rp[j]]].y)));

	km();

	printf("%.10lf\n",ans);
	return 0;
}
