#include <bits/stdc++.h>
#define eps (1e-6)
using namespace std;

const double pi = acos(-1.0);
const double tpi = 2.0 * pi;

struct point {
    double x,y,ang;
    point(double x = 0, double y = 0) : x(x), y(y) {}

    void read() {
	scanf("%lf %lf",&x, &y);
    }
} dot[1010],dot_[1010],bg[1010];
int sig(double a) {
    return (a < -eps ? -1 : (a > eps));
}
point operator + (point a,point b) { return point(a.x + b.x, a.y + b.y); }
point operator - (point a,point b) { return point(a.x - b.x, a.y - b.y); }
double operator *(point a,point b) { return (a.x * b.x + a.y * b.y); }
double operator /(point a,point b) { return (a.x * b.y - a.y * b.x); }
bool operator == (point a,point b) { return (!sig(a.x - b.x) && !sig(a.y - b.y)); }
	
int mark[1010];
int ans,n,m,N,N_;

double length(point a) {
    return sqrt(a * a);
}

bool inv(point a,point b) {
    return !sig(fabs(a.ang - b.ang) - pi);
}

bool shun(point a,point b) {
    return (sig(b / a) > 0 || a == b);
}

bool cmp(point a, point b) {
    return (a.ang < b.ang);
}

int nex(int a) {
    if (a == N) return 1;
    else return a + 1;
}

double fab(double a) {
    if (a < 0.0) return a + tpi;
    return a;
}

void solve(int u) {
    N = 0;
    for (int i = 1; i <= n; i++) {
	if (i == u) continue;
	dot[++N] = bg[i] - bg[u];
    }
    for (int i = 1; i <= N; i++) {
	dot[i].ang = acos(dot[i].x / length(dot[i]));
	if (dot[i].y < 0.0) dot[i].ang = tpi - dot[i].ang;
    }

    for (int i = 1; i <= N; i++)
	mark[i] = 0;
    for (int i = 1; i <= N; i++)
	for (int j = 1; j <= N; j++) {
	    if (!sig(dot[i].ang - dot[j].ang) && length(dot[i]) < length(dot[j]))
		mark[j] = 1;
	}

    N_ = 0;
    for (int i = 1; i <= N; i++)
	if (!mark[i]) dot_[++N_] = dot[i];

    N = N_;
    for (int i = 1; i <= N; i++)
	dot[i] = dot_[i];
    sort(dot + 1, dot + N + 1, cmp);
    for (int a = 1; a <= N; a++) {
	if (dot[a].ang > pi - eps) break;
	int b = a + 1;
	for (; b <= N && sig(fabs(dot[b].ang - dot[a].ang) - pi); b++);
	if (b > N) break;
	int x = nex(a), y = nex(b);
	point pasx = dot[x] - dot[a];
	point pasy = dot[y] - dot[b];
	if (x != b && y != a && inv(dot[x], dot[y])) {
	    ans++;
	}
	while (x != b && y != a) {
	    int X = nex(x), Y = nex(y);
	    if (X != b &&
		(Y == a || dot[x] / dot[y] < eps)) {
		x = nex(x);		
	    } else if (Y != a &&
		       (X == b || dot[y] / dot[x] < eps))
		y = nex(y);
	    else break;
	    if (x == b || y == a) break;
	    if (inv(dot[x], dot[y]) && shun(dot[x] - dot[a], pasx) && shun(dot[y] - dot[b], pasy)) {
		ans++;
	    }
	    if (shun(dot[x] - dot[a], pasx))
		pasx = dot[x] - dot[a];
	    if (shun(dot[y] - dot[b], pasy))
		pasy = dot[y] - dot[b];	    
	}
    }
}

int main() {
    freopen("K.in","r",stdin);
    freopen("K.out","w",stdout);
    scanf("%d",&n);
    for (int i = 1; i <= n; i++)
	bg[i].read();
    for (int i = 1; i <= n; i++)
	solve(i);
    printf("%d\n",ans);
    return 0;
}
