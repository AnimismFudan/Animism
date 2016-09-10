#include <bits/stdc++.h>
#define Pair pair<int,int>
#define Max (41 * 41 * 41)
#define eps 1e-6
using namespace std;

struct point {
	double x,y;

	void read() {
		scanf("%lf %lf",&x,&y);
	}
} dot[310],vec[50];

point operator - (point a, point b) { return (point) { a.x - b.x, a.y - b.y }; }

double length(point a) {
	return sqrt(a.x * a.x + a.y * a.y);
}

int que[10010000];

double val[Max],dis[Max][1 << 6],ok[Max];
int co[310],msk[Max],mark[51][51][51],fst[Max];
int n,m,q,top,e;
double ans;

struct str { int v,nex; double len; } edge[10000100];

void make_edge(int a,int b,double len) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b; edge[e].len = len;	
}

double cr(point a,point b) {
	return (a.x * b.y - a.y * b.x);
}

int sig(double a) { return a < -eps ? -1 : (a > eps); }

int Mark(int a,int b,int c) {
	if (b > c) swap(b, c);
	if (b < a) swap(b, a);
	if (b > c) swap(b, c);
	return mark[a][b][c];
}

void spfa() {
	ans = 1 << 30;
	for (int i = 1; i <= top; i++)
		for (int j = 0; j < (1 << q); j++)
			dis[i][j] = 1 << 30;
	
	for (int i = 1; i <= top; i++) {
		dis[i][msk[i]] = val[i];
		//que.push(make_pair(i, msk[i]));
		//ok[i][msk[i]] = 1;
	}

	for (int st = 1; st < (1 << q); st++) {
		int L = 0, R = 0;
		for (int i = 1; i <= top; i++) {
			if (dis[i][st] < (1 << 30) - 1) {
				que[++R] = i;
				ok[i] = 1;
			}
		}
		
		while (L < R) {
			int u = que[++L];
			ok[u] = 0;
			if (dis[u][st] < 0) { printf("???"); }
			for (int i = fst[u]; i; i = edge[i].nex) {
				int v = edge[i].v;
				int ts = st | msk[v];
				if (dis[v][ts] > dis[u][st] - edge[i].len + val[v]) {
					dis[v][ts] = dis[u][st] - edge[i].len + val[v];
					if (st == ts && !ok[v]) {
						que[++R] = v;
						ok[v] = 1;
					}
				}
			}
		}
	}
	
	for (int i = 1; i <= top; i++) ans = min(ans,dis[i][(1 << q) - 1]);
}

int dot_R(point a,point b) {
	if (a.x * b.y - a.y * b.x > 0) return 1;
	else return -1;
}

bool judge(point a,point b,point c,point k) {
	int x = dot_R(a - b, k - b);
	int y = dot_R(b - c, k - c);
	int z = dot_R(c - a, k - a);
	if (x ==  1 && y ==  1 && z ==  1) return true;
	if (x == -1 && y == -1 && z == -1) return true;
	return false;
}

int main() {
	//freopen("L.in","r",stdin);
	//freopen("L.out","w",stdout);
	scanf("%d %d %d",&n,&m,&q);
	for (int i = 1; i <= n; i++) {
		dot[i].read();
	}
	for (int i = 1; i <= n; i++)
		scanf("%d",&co[i]);
	for (int i = 1; i <= m; i++) {
		vec[i].read();
	}

	for (int i = 1; i <= m; i++)
		for (int j = i + 1; j <= m; j++)
			for (int k = j + 1; k <= m; k++) {
				//if (i == j || j == k || i == k) continue;
				if (!sig(cr(vec[i] - vec[j], vec[k] - vec[j]))) continue;
				mark[i][j][k] = ++top;
				val[top] = length(vec[i] - vec[j]) + length(vec[j] - vec[k]) + length(vec[i] - vec[k]);
				for (int u = 1; u <= n; u++) {
					if (judge(vec[i], vec[j], vec[k], dot[u]))
						msk[top] |= 1 << (co[u] - 1);
				}
		}

	for (int a = 1; a <= m; a++)
		for (int b = 1; b <= m; b++) {
			if (a == b) continue;
			double Dis = 2.0 * length(vec[a] - vec[b]);
			for (int x = 1; x <= m; x++) {
				if (x == a || x == b) continue;
				for (int y = 1; y <= m; y++) {
					if (y == a || y == b || y == x) continue;
					if (!sig(cr(vec[a] - vec[b], vec[x] - vec[b]))) continue;
					if (!sig(cr(vec[a] - vec[b], vec[y] - vec[b]))) continue;
					make_edge(Mark(x, a, b), Mark(y, a, b), Dis);
				}
			}
		}
	
	spfa();
	if (ans > ((1 << 30) - 1)) printf("-1\n");
	else printf("%.12lf\n",ans);
	return 0;
}
