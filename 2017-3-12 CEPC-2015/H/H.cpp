#include <bits/stdc++.h>
#define INF 100000000
#define eps (1e-8)
using namespace std;

struct point {
	double x, y;
	point (double x = 0, double y = 0) : x(x), y(y) {}
	void read() {
		scanf("%lf %lf",&x,&y);
	}
} dot[5], dt[100];

struct Line { point p, v; };

point operator + (point a, point b) { return point(a.x + b.x, a.y + b.y); }
point operator - (point a, point b) { return point(a.x - b.x, a.y - b.y); }
double operator * (point a, point b) { return a.x * b.x + a.y * b.y; }
double operator / (point a, point b) { return a.x * b.y - a.y * b.x; }
point operator * (point a, double b) { return point(a.x * b, a.y * b); }
point operator / (point a, double b) { return point(a.x / b, a.y / b); }
double ans;

int sig(double a) {
	return (a < -eps ? -1 : (a > eps));
}

point cross_line(Line a, Line b) {
	point u = a.p - b.p;
	if (!sig(a.v / b.v)) return point(INF, INF);
	double t = (b.v / u) / (a.v / b.v);
	return a.p + a.v * t;
}

point cross_seg(Line A, point a, point b) {
	point ans = cross_line(A, (Line) { a, b - a });
	if (ans.x > INF - 1) return ans;
	if ((ans - a) * (ans - b) > -eps) return point(INF, INF);
	return ans;
}

double query(Line A) {
	int top = 0;
	for (int i = 0; i < 4; i++) {
		if ((dot[i] - A.p) / A.v > -eps)
			dt[top++] = dot[i];
		point cr = cross_seg(A, dot[i], dot[(i + 1) % 4]);
		if (cr.x < INF - 1.0 && ((cr - A.p) / A.v > -eps))
			dt[top++] = cr;
	}
	double ans = 0;
	for (int i = 0; i < top; i++)
		ans += (dt[(i + 1) % top] / dt[i]);
	ans = fabs(ans) / 2.0;
	return ans;
}

int main() {
	//freopen("H.in","r",stdin);
	//freopen("H.out","w",stdout);
	for (int i = 0; i < 4; i++) dot[i].read();
	ans += query((Line) { point(0.5, 0), point(0, 1) }) * 3.0 * 5.0;
	ans += query((Line) { point(0, 0.5), point(-1, 0)}) * 6.0 * 5.0;
	ans += query((Line) { point(-0.5, 0),point(0,-1) }) * 4.0 * 5.0;
	ans += query((Line) { point(0, -0.5),point(1, 0) }) * 1.0 * 5.0;
	ans += 4.0 * 5.0 * 5.0 * 5;
	ans /= (5.0 * 5.0 * 5.0 - 1.0);
	printf("%.12lf\n",ans);
	return 0;
}
