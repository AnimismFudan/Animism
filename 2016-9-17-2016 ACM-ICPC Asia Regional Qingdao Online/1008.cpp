#include <bits/stdc++.h>
using namespace std;
#define comp complex<double>
#define LD double
#define eps (1e-8)
bool tt;
const double pi = acos(-1.0);
const double tpi = 2.0 * pi;
double wp[510][510],pw[510][510],ans[510][510],ans_[510][510],val[510][510],Ans;
int n,m,N,R;
int rev[2400010];
double r;

comp A[2400010], B[2400010], C[2400010], js[2400010];

bool ss;

void FFT(comp a[],int n,int sign) {
    if (n == 1) return;
    for (int i = 0; i < n; i++) js[i] = a[i];
    int N = n >> 1;
    for (int i = 0; i < N; i++) a[i] = js[i << 1],a[i + N] = js[i << 1 | 1];
 
    FFT(a,N,sign); FFT(a + N,N,sign);
    double p = 2.0 * pi / n * sign;
    comp u = 1, base = comp(cos(p), sin(p));
 
    for (int i = 0; i < N; i++) {
        js[i] = a[i] + a[i + N] * u;
        js[i + N] = a[i] - a[i + N] * u;
        u = u * base;
    }
 
    for (int i = 0; i < n; i++) a[i] = js[i];
}

inline void Solve() {
    for (N = 1; N < (n + R + R + 1) * (m + R + R + 1); N <<= 1);
    FFT(A, N, 1);
	FFT(B, N, 1);

	for (int i = 0; i < N; i++) C[i] = A[i] * B[i];
	FFT(C, N, -1);
	for (int i = 0; i < N; i++) C[i] /= N;
}

inline void solve() {  
    //memset(A, 0, sizeof(A));
    //memset(B, 0, sizeof(B));
    for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			A[(i - 1) * (m + 2 * R + 1) + j - 1] = val[i][j];
    for (int i = -R; i < R; i++)
		for (int j = -R; j < R; j++) {
			if (sqrt((double) (i * i + j * j)) + eps >= r) continue;
			B[(i + R) * (m + 2 * R + 1) + (j + R)] = 1.0 / (sqrt((double) (i * i + j * j)) + 1.0);
		}
    Solve();
    for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			ans_[i][j] = C[(i - 1 + R) * (m + 2 * R + 1) + j - 1 + R].real(); 
    for (int i = 0; i <= N; i++) A[i] = B[i] = 0;
}

int main() {
    freopen("1008.in","r",stdin);
    freopen("1008.out","w",stdout);
    while (scanf("%d %d %lf",&n,&m,&r) != EOF) {
		R = (int) (r) + 1;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				scanf("%lf",&val[i][j]);
				ans[i][j] = val[i][j];
			}
		if (r < eps) {
			printf("0.000\n");
			continue;
		}
		//-------------------------------------
		solve();
		Ans = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				Ans = max(Ans, ans_[i][j]);
		printf("%.3lf\n",Ans);
    }
    return 0;
}
