#include <bits/stdc++.h>
#define eps (1e-6)
#define INF (1e9)
using namespace std;

struct point {
	double x, y;
	void read() {
		scanf("%lf %lf",&x,&y);
	}

	point(double x = 0, double y = 0) : x(x), y(y) {}
} dot[60], Dot[60];

struct Line { point p, v; };

double operator / (point a, point b) { return a.x * b.y - a.y * b.x; }
double operator * (point a, point b) { return a.x * b.x + a.y * b.y; }
point operator - (point a, point b) { return point(a.x - b.x, a.y - b.y); }
point operator + (point a, point b) { return point(a.x + b.x, a.y + b.y); }
point operator * (point a, double b) { return point(a.x * b, a.y * b); }

int n;
int ans[60], p[60];
int nex[110], pas[110];
int dir[51][51][51];
int mark[51][51][51][51];
char s[60];

int sig(double a) { return a < -eps ? -1 : (a > eps); }

point cross_line(Line a, Line b) {
	point u = a.p - b.p;
	if (!sig(a.v / b.v)) return point(INF, INF);
	double t = (b.v / u) / (a.v / b.v);
	return a.p + a.v * t;
}

bool inhere(point a, point b, point c) {
	return ((a - c) * (b - c) < eps);
}

bool dfs(int u) {
	if (u > n) {
		return true;
	}
	for (int i = nex[0]; i < n + 1; i = nex[i]) {
		if (u <= 2) {
			ans[u] = i;
			pas[nex[i]] = pas[i];
			nex[pas[i]] = nex[i];
			if (dfs(u + 1)) return true;
			pas[nex[i]] = i;
			nex[pas[i]] = i;
		} else {
			if (!((s[u - 2] == 'L' && dir[ans[u - 2]][ans[u - 1]][i] == 1) ||
				  (s[u - 2] == 'R' && dir[ans[u - 2]][ans[u - 1]][i] == -1)))
				continue;
			bool flag = true;
			for (int x = 1; x < u - 1; x++) {
				if (mark[ans[x]][ans[x + 1]][ans[u - 1]][u]) {
					flag = false;
					break;
				}
			}
			if (!flag) continue;
			ans[u] = i;
			pas[nex[i]] = pas[i];
			nex[pas[i]] = nex[i];
			if (dfs(u + 1)) return true;
			pas[nex[i]] = i;
			nex[pas[i]] = i;			
		}
	}
	return false;
}

int main() {
	//freopen("L.in","r",stdin);
	//freopen("L.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) p[i] = i;
	random_shuffle(p + 1, p + n + 1);
	for (int i = 1; i <= n; i++) Dot[i].read();
	for (int i = 1; i <= n; i++) dot[i] = Dot[p[i]];
	scanf("%s",s + 1);
	for (int a = 1; a <= n; a++)
		for (int b = 1; b <= n; b++)
			for (int c = 1; c <= n; c++) {
				if (a == b || a == c || b == c) continue;
				point A = dot[b] - dot[a];
				point B = dot[c] - dot[b];
				if (A / B > eps) dir[a][b][c] = 1;			
				if (A / B < -eps) dir[a][b][c] = -1;
			}
	for (int a = 1; a <= n; a++)
		for (int b = 1; b <= n; b++)
			for (int c = 1; c <= n; c++)
				for (int d = 1; d <= n; d++) {
					if (a == b || c == d) continue;
					if (a == c || a == d) continue;
					if (b == c || b == d) continue;
					point A = cross_line((Line) { dot[a], dot[b] - dot[a] }, (Line) { dot[c], dot[d] - dot[c]});
					if (inhere(dot[a], dot[b], A) && inhere(dot[c], dot[d], A)) {
						mark[a][b][c][d] = 1;
					}
				}

	for (int i = 0; i <= n; i++) {
		nex[i] = i + 1;
		pas[i + 1] = i;
	}
	dfs(1);
	for (int i = 1; i <= n; i++) printf("%d ",p[ans[i]]);
	return 0;
}
