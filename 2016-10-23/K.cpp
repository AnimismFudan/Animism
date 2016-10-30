#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);
const double eps = 1e-7;

int Test, N, ans, sum, r;

class rec{
	public:
	double s;
	int d;
}t1, t2, q[10010];

class poi{
	public:
	double x, y;
}P;

class line{
	public:
	poi s, t;
}L[10010];

bool cmpsd(const rec &A, const rec &B){
	if (fabs(A.s - B.s) < eps)	return A.d > B.d;
	return A.s < B.s;
}

int main(){
	freopen("K.in", "r", stdin);
	freopen("K.out", "w", stdout);
	scanf("%d", &Test);
	while (Test--){
		scanf("%d", &N);
		scanf("%lf%lf", &P.x, &P.y);
		r = 0;
		for (int i = 1; i <= N; i++){
			scanf("%lf%lf", &L[i].s.x, &L[i].s.y);
			scanf("%lf%lf", &L[i].t.x, &L[i].t.y);
			t1.s = atan2(L[i].s.y - P.y, L[i].s.x - P.x);
			t2.s = atan2(L[i].t.y - P.y, L[i].t.x - P.x);
			if (t1.s > t2.s)
				swap(t1, t2);
			if (t1.s > eps)t1.s = 0;
			if (t2.s > eps)t2.s = 0;
			t1.d = 1;
			t2.d = -1;
			q[++r] = t1;
			q[++r] = t2;
		}
		sort(q + 1, q + r + 1, cmpsd);
		sum = 0;
		ans = 0;
		if (fabs(q[1].d + pi) > eps)
			ans++;
		for (int i = 1; i <= r; i++){
			int j = i;
			while (j <= r && fabs(q[j].s - q[i].s) < eps){
				sum += q[j].d;
				j++;
			}
			i = j - 1;
			if (!sum && fabs(q[i].s) > eps)
				ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}
