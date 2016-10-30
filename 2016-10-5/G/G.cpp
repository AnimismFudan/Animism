#include <bits/stdc++.h>
using namespace std;

int Test, N, M, r;
double ans, res;

class poi{
	public:
	double x, y;
	poi operator - (const poi &X)const{
		poi C;
		C.x = x - X.x;
		C.y = y - X.y;
		return C;
	}
}P[100010], p;

class que{
	public:
	int x;
	double d;
}Q[100010];

int b[100010];
double d[100010];



double dist(const poi &A, const poi &B){
	double res = (A.x - B.x) * (A.x - B.x);
	res += (A.y - B.y) * (A.y - B.y);
	return sqrt(res);
}

double xet(poi A, poi B){
	return A.x * B.y - B.x * A.y;
}

double cross(poi A, poi B, poi C){
	return xet(B - A, C - A);
}

bool cmpxd(const que &A, const que &B){
	if (A.x != B.x)return A.x > B.x;
	return A.d > B.d;
}

void get_p(int i, int j){
	p = P[i];
	if (P[i].x == P[i + 1].x){
		if (P[i + 1].y > P[i].y)p.y += Q[j].d;
		else p.y -= Q[j].d;
	}else{
		if (P[i + 1].x > P[i].x)p.x += Q[j].d;
		else p.x -= Q[j].d;
	}
}

int main(){
	freopen("G.in", "r", stdin);
	freopen("G.out", "w", stdout);
	scanf("%d", &Test);
	while (Test--){
		scanf("%d", &N);
		N--;
		for (int i = 0; i <= N; i++)
			scanf("%lf%lf", &P[i].x, &P[i].y);
		scanf("%d", &M);
		for (int i = 1; i <= M; i++)
			scanf("%d%lf", &Q[i].x, &Q[i].d);
		sort(Q + 1, Q + M + 1, cmpxd);
		int j = 1;
		ans = 0;
		while (j <= M && Q[j].x == N){
			get_p(N, j);
			ans += dist(P[0], p);
			j++;
		}
		b[1] = 0;
		b[r = 2] = N;
		d[1] = 0;
		d[2] = dist(P[N], P[0]);
		for (int i = N - 1; i; i--){
			while (j <= M && Q[j].x == i){
				get_p(i, j);
				while (r > 1 && cross(P[b[r - 1]], P[b[r]], p) <= 0)
					b[r--] = 0;
				res = d[r] + dist(P[b[r]], p);
				ans += res;
				j++;
			}
			
			while (r > 1 && cross(P[b[r - 1]], P[b[r]], P[i]) <= 0)
				b[r--] = 0;
			b[++r] = i;
			d[r] = d[r - 1] + dist(P[b[r]], P[b[r - 1]]);
		}
		printf("%.1lf\n", ans);
	}
}
