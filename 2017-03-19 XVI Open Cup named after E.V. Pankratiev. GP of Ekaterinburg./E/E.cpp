#include <bits/stdc++.h>
#define maxn 10100
#define eps (1e-10)
#define INF (1e9)
using namespace std;

int n;
double R[maxn];

struct point {
	double x, y;
	point (double x = 0, double y = 0) : x(x), y(y) {}
	void read() { scanf("%lf %lf",&x,&y); }
} A[maxn], B[maxn], C[maxn], O[maxn];

point operator + (point a, point b) { return point(a.x + b.x, a.y + b.y); }
point operator - (point a, point b) { return point(a.x - b.x, a.y - b.y); }
double operator * (point a, point b) { return a.x * b.x + a.y * b.y; }
double operator / (point a, point b) { return a.x * b.y - a.y * b.x; }
point operator * (point a, double b) { return point(a.x * b, a.y * b); }

struct Line { point p, v; };

double sig(double a) {
	return (a < -eps ? -1 : (a > eps));
}

bool operator == (point a, point b) {
	return (!sig(a.x - b.x) && !sig(a.y - b.y));
}

point cross_line(Line a, Line b) {
	point u = a.p - b.p;
	if (!sig(a.v / b.v)) return point(INF, INF);
	double t = (b.v / u) / (a.v / b.v);
	return a.p + a.v * t;
}

bool judge(int u, point v) {
	if (v == A[u] || v == B[u] || v == C[u]) return true;
	if ((v - O[u]) * (v - O[u]) < R[u] - eps) return false;
	return true;
}

int main() {
	//freopen("E.in","r",stdin);
	//freopen("E.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) {
		A[i].read(); B[i].read(); C[i].read();
	}
	for (int i = 1; i <= n; i++) {
		point vecab = point(B[i].y - A[i].y, A[i].x - B[i].x);
		point vecac = point(C[i].y - A[i].y, A[i].x - C[i].x);
		O[i] = cross_line((Line) { (A[i] + B[i]) * 0.5, vecab }, (Line) { (A[i] + C[i]) * 0.5, vecac });
		R[i] = (A[i] - O[i]) * (A[i] - O[i]);
	}

	bool flag = true;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			flag &= judge(i, A[j]);
			flag &= judge(i, B[j]);
			flag &= judge(i, C[j]);
		}			
	}
	if (flag) printf("YES\n");
	else printf("NO\n");
	return 0;
}
