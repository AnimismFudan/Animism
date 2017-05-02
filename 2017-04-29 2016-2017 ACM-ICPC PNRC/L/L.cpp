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

int n, q;
int st[120];
int ans[160], p[160], vis[160];
char s[160];

int sig(double a) { return a < -eps ? -1 : (a > eps); }

bool cmp(int a, int b) {
	if (sig(dot[a].x - dot[b].x) == -1) return true;	
	if (sig(dot[a].x - dot[b].x) == 1) return false;
	return (dot[a].y < dot[b].y);
}

int convex(int n) {
	sort(p + 1, p + n + 1, cmp);
	int top = 0;
	for (int i = 1; i <= n; i++) {
		while (top > 1 && (dot[st[top]] - dot[st[top - 1]]) / (dot[p[i]] - dot[st[top]]) < -eps) top--;
		st[++top] = p[i];
	}
	int just = top;
	for (int i = n - 1; i >= 1; i--) {
		while (top > just && (dot[st[top]] - dot[st[top - 1]]) / (dot[p[i]] - dot[st[top]]) < -eps) top--;
		st[++top] = p[i];
	}
	top--;
	return top;
}

int nex(int a, int n) {
	if (a < n) return a + 1;
	else return 1;
}

int pas(int a, int n) {
	if (a == 1) return n;
	else return a - 1;
}

void solve(int now, int bg) {
	int m = 0;
	for (int i = 1; i <= n; i++)
		if (!vis[i]) p[++m] = i;
	m = convex(m);
	if (!bg) {
		bg = st[1];
	}
	ans[++q] = bg;
	vis[bg] = 1;
	int u = 0;
	for (int i = 1; i <= m; i++)
		if (st[i] == bg) u = i;	
	if (s[now] == 'L') solve(now + 1, st[nex(u, m)]);
	else if (s[now] == 'R') solve(now + 1, st[pas(u, m)]);
	else {
		ans[++q] = st[nex(u, m)];
		vis[st[nex(u, m)]] = 1;
		return;
	}
}

int main() {
	freopen("L.in","r",stdin);
	freopen("L.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) dot[i].read();	
	scanf("%s",s + 1);
	solve(1, 0);
	for (int i = 1; i <= n; i++)
		printf("%d ",ans[i]);
	return 0;
}
