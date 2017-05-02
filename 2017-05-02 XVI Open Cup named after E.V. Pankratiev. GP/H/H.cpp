#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, len, maxl;
int L[110];
double ans, sum;
double A[110][2], B[110], C[110];

class rec{
	public:
	int l, r;
} P[60];

double calc(double *B, int l, int r){
	for (int i = maxl; i >= 0; i--)
		B[i + 1] = B[i] / (i + 1);
	B[0] = 0;
	double resl = 0;
	double resr = 0;
	double sl = 1;
	double sr = 1;
	for (int i = 1; i <= maxl; i++){
		sl *= l;
		sr *= r;
		resl += B[i] * sl;
		resr += B[i] * sr;
	}
	return resr - resl;
}

void work(int a, int b){
	len = 0;
	for (int i = 1; i <= N; i++){
		L[++len] = P[i].l;
		L[++len] = P[i].r;
	}
	sort(L + 1, L + len + 1);
	len = unique(L + 1, L + len + 1) - L - 1;
	int pl = lower_bound(L + 1, L + len + 1, P[b].l) - L;
	int pr = lower_bound(L + 1, L + len + 1, P[b].r) - L;
	for (int i = pl; i < pr; i++){
		int l = L[i], r = L[i + 1];
		for (int j = 1; j <= N; j++)
			if (j == a){
				if (r <= P[j].l){
					A[j][0] = 1;
					A[j][1] = 0;
				}
				else if (r <= P[j].r){
					A[j][0] = double(P[j].r) / (P[j].r - P[j].l);
					A[j][1] = -1.0 / (P[j].r - P[j].l);
				}
				else{
					A[j][0] = 0;
					A[j][1] = 0;
				}
			}
			else if (j == b){
//				A[j][0] = double(r - l) / (P[j].r - P[j].l);
				A[j][0] = 1.0 / (P[j].r - P[j].l);
				A[j][1] = 0;
			}
			else{
				if (r <= P[j].l){
					A[j][0] = 0;
					A[j][1] = 0;
				}
				else if (r <= P[j].r){
					A[j][0] = double(-P[j].l) / (P[j].r - P[j].l);
					A[j][1] = 1.0 / (P[j].r - P[j].l);
				}
				else{
					A[j][0] = 1;
					A[j][1] = 0;
				}
			}
		for (int j = 1; j <= maxl; j++)
			B[j] = 0;
		B[0] = 1;
		for (int j = 1; j <= N; j++){
			for (int k = 0; k <= maxl; k++)
				C[k] = 0;
			for (int k = 0; k <= maxl; k++){
				C[k] += B[k] * A[j][0];
				C[k + 1] += B[k] * A[j][1];
			}
			for (int k = 0; k <= maxl; k++)
				B[k] = C[k];
		}
		double pn = calc(B, l, r);
		B[0] = 0;
		for (int k = 0; k <= maxl; k++)
			B[k + 1] = C[k];
		sum += pn;
		ans += calc(B, l, r);
	}
}

int main() {
	freopen("secondmax.in","r",stdin);
	freopen("secondmax.out","w",stdout);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d%d", &P[i].l, &P[i].r);
	maxl = N + 2;
	ans = 0;
	sum = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			if (i != j)
				work(i, j);
//	printf("%.10lf\n%.10lf\n", sum, ans);
	if (fabs(sum) < 1e-5){
		for (int i = 1; i <= 100000000; i++)
			printf("- -");
	}
	printf("%.10lf\n", ans);
	return 0;
}
