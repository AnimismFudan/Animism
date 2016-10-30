#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-3;

int Test, N[2], len;
double ans;
double q[10010];
class poi{
	public:
	double x, y;
}P[2][1010];

double getcross(poi pl, poi pr, double y, bool &flag){
	double res = 0;
	flag = 1;
	if (pl.y > pr.y)
		swap(pl, pr);
	if (fabs(pl.y - y) < eps)
		return pl.x;
	if (fabs(pr.y - y) < eps)
		return pr.x;
	if (pl.y < y && pr.y > y){
		if (fabs(pr.x - pl.x) > eps)
			res = pl.x + (pr.x - pl.x) / (pr.y - pl.y) * (y - pl.y);
		else	res = pl.x;
		return res;
	}
	flag = 0;
	return res;
}

double f(int t, double y){
	poi pl, pr;
	double l, r, m;
	bool flag;
	double res = 0;
	l = 2e9;
	r = -2e9;
	for (int i = 1; i <= N[t]; i++){
		pl = P[t][i];
		pr = P[t][i % N[t] + 1];
		m = getcross(pl, pr, y, flag);
		if (flag){
			l = min(l, m);
			r = max(r, m);
		}
	}
	if (l + eps < r)
		res = fabs(r - l);
	return res;
}

int main(){
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
	scanf("%d", &Test);
	while (Test--){
		len = 0;
		for (int t = 0; t < 2; t++){
			scanf("%d", &N[t]);
			for (int i = 1; i <= N[t]; i++){
				scanf("%lf%lf", &P[t][i].x, &P[t][i].y);
				q[++len] = P[t][i].y;
			}
		}
		sort(q + 1, q + len + 1);
		len = unique(q + 1, q + len + 1) - q - 1;
		ans = 0;
		for (int i = 1; i < len; i++){
			double x0 = f(0, q[i]);
			double x1 = f(0, q[i + 1]);
			double y0 = f(1, q[i]);
			double y1 = f(1, q[i + 1]);
			double res = x0 * y0;
			res += ((x1 - x0) * y0 + (y1 - y0) * x0) / 2;
			res += (x1 - x0) * (y1 - y0) / 3;
			ans += res;
		}
		printf("%.2lf\n", ans);
	}
	return 0;
}
