#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-4;
const double eps_ = 1e-7;

int Test, N[2];
double ans;
class poi{
	public:
	double x, y;
}P[2][1010];

poi getcross(poi pl, poi pr, double y, bool &flag){
	poi pm;
	pm.x = pm.y = 0;
	flag = 0;
	if (pl.y > pr.y)
		swap(pl, pr);
	if (pl.y < y && pr.y >= y){
		pm.y = y;
		if (fabs(pr.x - pl.x) > eps)
			pm.x = pl.x + (pr.x - pl.x) / (pr.y - pl.y) * (y - pl.y);
		else	pm.x = pl.x;
		flag = 1;
	}
	return pm;
}

double f(double y){
	poi p1, p2, p3, pl, pr;
	bool flag;
	double res = 1;
	for (int t = 0; t < 2; t++){
		p1.x = p1.y = p2.x = p2.y = 0;
		for (int i = 1; i <= N[t]; i++){
			pl = P[t][i];
			pr = P[t][i % N[t] + 1];
			p3 = getcross(pl, pr, y, flag);
			if (flag){
				p2 = p1;
				p1 = p3;
			}
		}
		res = res * fabs(p2.x - p1.x);
	}
	return res;
}

double Simpson(double a, double b){
	if (fabs(a-b) < eps_) return 0.0;
	double c = (a + b) / 2;
	return (f(a) + 4 * f(c) + f(b)) / 6 * (b - a);
}

double AdativeSimipson(double a, double b, double eps){
	//cout << a << ' ' << b << endl;
	double c = (a + b) / 2;
	double S = Simpson(a, b);
	double S1 = Simpson(a, c);
	double S2 = Simpson(c, b);
	if (fabs(S1 + S2 - S) < 15 * eps) return S;
	else return AdativeSimipson(a, c, eps / 2) + AdativeSimipson(c, b, eps / 2);
}

int main(){
	freopen("A.in", "r", stdin);
	//freopen("A1.out", "w", stdout);
	scanf("%d", &Test);
	while (Test--){
		double l = 2e9, r = -2e9;
		for (int t = 0; t < 2; t++){
			scanf("%d", &N[t]);
			for (int i = 1; i <= N[t]; i++){
				scanf("%lf%lf", &P[t][i].x, &P[t][i].y);
				l = min(l, P[t][i].y);
				r = max(r, P[t][i].y);
			}
		}
		ans = AdativeSimipson(l, r, eps);
		printf("%.2lf\n", ans);
	}
	return 0;
}
