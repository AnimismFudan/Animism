#include <bits/stdc++.h>
#define intl long long
#define maxn 4010
#define eps (1e-8)
using namespace std;

const double tpi = 2.0 * acos(-1.0);
const double pi = acos(-1.0);

struct point {
	int mark;
	intl x, y;
	double ang;
	void read() {
		scanf("%lld %lld",&x,&y);
	}

	point (intl x = 0, intl y = 0) : x(x), y(y) {}

	void make_ang() {
		ang = acos((double) x / sqrt((double) (x * x + y * y)));
		if (y < 0) ang = tpi - ang;
	}
} dot[maxn], sing[maxn], A[maxn], B[maxn];

int n, top;
intl ans;
intl L, R;

point operator + (point a, point b) { return point(a.x + b.x, a.y + b.y); }
point operator - (point a, point b) { return point(a.x - b.x, a.y - b.y); }
intl  operator * (point a, point b) { return a.x * b.x + a.y * b.y; }
intl  operator / (point a, point b) { return a.x * b.y - a.y * b.x; }

intl Length(point a) { return (a * a); }

bool cmp(const point &a, const point &b) {
	if (a.ang < b.ang - eps) return true;
	if (a.ang > b.ang + eps) return false;
	if (a / b > 0) return true;
	if (a / b < 0) return false;
	return (Length(a) < Length(b)); 
}

int main() {
	//freopen("J.in","r",stdin);
	//freopen("J.out","w",stdout);
	scanf("%d %lld %lld",&n,&L,&R);
	L <<= 1; R <<= 1;
	for (int i = 1; i <= n; i++) {
		dot[i].read();
	}
	for (int u = 1; u <= n; u++) {
		top = 0;
		for (int i = 1; i <= n; i++) {
			if (u != i) {
				sing[++top] = dot[i] - dot[u];
				sing[top].mark = 0;
				point just = dot[i] - dot[u];
				sing[++top] = point(-just.y, just.x);
				sing[top].mark = 1;
			}
		}
		for (int i = 1; i <= top; i++) sing[i].make_ang();
		sort(sing + 1, sing + top + 1, cmp);
		for (int l = 1; l <= top; l++) {
			int r = l;
			for (; r <= top && !(sing[l] / sing[r]) && (sing[l] * sing[r] > 0LL); r++);
			r--;
			int tb = 0, ta = 0;
			for (int k = l; k <= r; k++) {
				if (sing[k].mark) B[++tb] = sing[k];
				else A[++ta] = sing[k];
			}
			int lb = 1, rb = 1;
			for (int i = ta; i >= 1; i--) {
				while (lb <= tb && abs(A[i] * B[lb]) < L) lb++;
				while (rb <= tb && abs(A[i] * B[rb]) <= R) rb++;
				ans += (intl) (rb - lb);
			}
			l = r;
		}
	}
	cout << ans << endl;
	return 0;
}
