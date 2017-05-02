#include <bits/stdc++.h>
#define eps (1e-9)
using namespace std;

double x[201000];
int n, N;

double judge(double X) {
	double ans = 0;
	for (int i = 1; i <= N; i++) {
		double t = X + (double)(i - 1);
		ans += sqrt(1 + (x[i] - t) * (x[i] - t));
	}
	return ans;
}

int main() {
	freopen("make-a-row.in","r",stdin);
	freopen("make-a-row.out","w",stdout);
	scanf("%d",&n);
	N = n * 2;
	for (int i = 1; i <= N; i++) {
		scanf("%lf",&x[i]);
	}
	sort(x + 1, x + N + 1);
	double L = -2000000.0;
	double R = 1000000.0;
	while ((R - L) / max(R, 1.0) > eps) {
		double t = (R - L) / 3.0;
		double l = L + t;
		double r = R - t;
		if (judge(l) > judge(r)) {
			L = l;
		} else
			R = r;
	}

	printf("%.12lf\n",judge((L + R) / 2.0));
	return 0;
}
