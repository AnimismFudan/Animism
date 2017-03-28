#include <bits/stdc++.h>
#define INF (1000000000.0)
#define eps (1e-6)
#define maxn 401000
using namespace std;

struct point {
	double x, y;
	int num;
	point (double x = 0, double y = 0) : x(x), y(y) {}
	void read() {
		scanf("%lf %lf",&x,&y);
	}	
};

int sig(double a) {
	return (a < -eps ? -1 : (a > eps));
}

point operator + (point a, point b) { return point(a.x + b.x, a.y + b.y); }
point operator - (point a, point b) { return point(a.x - b.x, a.y - b.y); }
point operator * (point a, double b){ return point(a.x * b, a.y * b); }
double operator * (point a,point b) { return a.x * b.x + a.y * b.y; }
double operator / (point a,point b) { return a.x * b.y - a.y * b.x; }
bool operator == (point a, point b) { return !sig(a.x - b.x) && !sig(a.y - b.y); }

bool cmp(point a, point b) {
	return (a.x < b.x || (a.x == b.x && a.y < b.y));
}

int top, tp, n;
point st[maxn], dot[maxn];
int ansx[maxn], ansy[maxn];

double length(point a) { return sqrt(a * a); }

bool dot_R(point a, point b) {
	return (a / b > -eps);
}

int nex(int a) {
	return a < top ? a + 1 : 1;
}

void convex() {
	top = 0;
	for (int i = 1; i <= n; i++) {
		while (top > 1 && dot_R(dot[i] - st[top], st[top] - st[top - 1])) top--;
		st[++top] = dot[i];
	}
	int tp = top;
	for (int i = n; i >= 1; i--) {
		while (top > tp && dot_R(dot[i] - st[top], st[top] - st[top - 1])) top--;
		st[++top] = dot[i];
	}
}

void solve() {
	double dis = 0;
	top--;
	int v = 1;
	for (int u = 1; u <= top; u++) {
		while (length(st[nex(v)] - st[u]) > length(st[v] - st[u])) v = nex(v);
		dis = max(dis, length(st[v] - st[u]));
	}
	point o = point(INF, INF);
	v = 1;
	for (int u = 1; u <= top; u++) {
		while (length(st[nex(v)] - st[u]) > length(st[v] - st[u])) v = nex(v);
		if (u > v) break;
		if (length(st[v] - st[u]) > dis - eps) {
			if (o.x < INF - 1) {
				if (!(o == (st[u] + st[v]) * 0.5)) { tp = 0; return; }				
			}
			o = (st[u] + st[v]) * 0.5;
			ansx[++tp] = st[u].num;
			ansy[tp] = st[v].num;
		}
	}
	for (int i = 1; i <= n; i++)
		if (length(dot[i] - o) > dis * 0.5 + eps) { tp = 0; return; }
	return;
}

int main() {
	//freopen("I.in","r",stdin);
	//freopen("I.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) dot[i].num = i;
	for (int i = 1; i <= n; i++) dot[i].read();
	sort(dot + 1, dot + n + 1, cmp);
	convex();
	solve();
	printf("%d\n",tp);
	for (int i = 1; i <= tp; i++)
		printf("%d %d\n",ansx[i], ansy[i]);
	return 0;
}
