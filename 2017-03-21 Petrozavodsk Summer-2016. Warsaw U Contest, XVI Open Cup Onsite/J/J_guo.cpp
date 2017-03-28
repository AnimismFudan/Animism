#include <bits/stdc++.h>
using namespace std;

#define LL long long

double pi = acos(-1.0);
double eps = 1e-9;
double leps = 1e-5;
int N, len, ans;
LL A, B;

class poi{
	public:
	int x, y;
	double d, l;
}P[2010], a[4010];
 
bool cmpdl(const poi &A, const poi &B){
	if (fabs(A.d - B.d) > eps)
		return A.d < B.d;
	return A.l < B.l;
}

int findl(double al, int l, int r){
	while (l < r){
		int mid = (l + r) >> 1;
		if (a[mid].l >= al - eps) r = mid;
		else l = mid + 1;
	}
	return l;
}

int findr(double ar, int l, int r){
	while (l < r){
		int mid = (l + r + 1) >> 1;
		if (a[mid].l <= ar + eps) l = mid;
		else r = mid - 1;
	}
	return r;
}

LL dot(const poi &x, const poi &y){
	return (LL)x.x * y.x + (LL)x.y * y.y;
}

LL xet(const poi &x, const poi &y){
	return (LL)x.x * y.y - (LL)y.x * x.y;
}

int check(poi x, poi y){
	if (x.d - y.d < pi / 2 - leps) return -1;
	if (x.d - y.d > pi / 2 + leps) return 1;
	LL t = dot(x, y);
	if (t > 0) return -1;
	if (t < 0) return 1;
	return 0;
}

int main(){
	freopen("J.in", "r", stdin);
	freopen("J_.out", "w", stdout);
	scanf("%d", &N);
	cin >> A >> B;
	A = A << 1;
	B = B << 1;
	for (int i = 1; i <= N; i++)
		scanf("%d%d", &P[i].x, &P[i].y);
	for (int i = 1; i <= N; i++){
		len = 0;
		for (int j = 1; j <= N; j++)
			if (j != i){
				++len;
				a[len].x = P[j].x - P[i].x;
				a[len].y = P[j].y - P[i].y;
				a[len].d = atan2(a[len].y, a[len].x);
				a[len].l = sqrt((LL)a[len].x * a[len].x + (LL)a[len].y * a[len].y);
			}
		sort(a + 1, a + len + 1, cmpdl);
		for (int j = 1; j <= len; j++){
			a[len + j] = a[j];
			a[len + j].d += 2 * pi;
		}
		int l = 1, r = 1;
		for (int j = 1; j <= len; j++){
			while (l <= 2 * len && check(a[l], a[j]) < 0) l++;
			if (r < l) r = l;
			while (r < 2 * len && check(a[r + 1], a[j]) == 0) r++;
			if (l <= 2 * len && r <= 2 * len && check(a[l], a[j]) == 0){
				double al = A / a[j].l, ar = B / a[j].l;
				int xl = findl(al, l, r), xr = findr(ar, l, r);
				while (l < xl && a[xl - 1].l >= al - eps) xl--;
				while (xl <= r && a[xl].l < al - eps) xl++;
				while (xr < r && a[xr + 1].l <= ar + eps) xr++;
				while (l <= xr && a[xr].l > ar + eps) xr--;
				ans += xr - xl + 1;
			}
		}
	}
	printf("%d\n", ans);
}
