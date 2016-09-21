#include <bits/stdc++.h>
#define maxn 1010000
#define eps (1e-8)
using namespace std;

struct str {
	double s, p, w;
	double P, po;
	void read() {
		scanf("%lf %lf %lf",&s,&p,&w);
		P = s * p;
		po = w * s;
	}
} wir[maxn],dot[maxn];

int n,top,D;

bool cmp(const str &a, const str &b) {
	return (a.po > b.po);
}

bool judge(double mid) {
	double res = 0, wei = mid;
	for (int u = top; u; u--) {
		double t = dot[u].po - wei;
		if (t < eps) continue;
		res += t / dot[u].P;
		wei = dot[u].po;
	}
	return (res > (double) D);
}

int main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d %d",&D,&n);
	for (int i = 1; i <= n; i++) {
		wir[i].read();
	}
	sort(wir + 1, wir + n + 1, cmp);
	int pas = 0;
	for (int i = 1; i <= n; i++) {
		if (pas && wir[i].P >= wir[pas].P);
		else {
			pas = i;
			dot[++top] = wir[i];
		}		
	}
	double L = 0, R = 1000000000.0;
	while (R - L > eps) {
		double mid = (L + R) / 2.0;
		if (judge(mid)) L = mid;
		else R = mid;
	}
	printf("%.8lf\n",(R + L) / 2.0);
	return 0;
}
