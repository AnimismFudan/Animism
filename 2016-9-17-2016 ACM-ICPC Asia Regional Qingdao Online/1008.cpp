#include <bits/stdc++.h>
using namespace std;

#define LD double
#define eps (1e-8)
bool tt;
const double pi = acos(-1.0);
const double tpi = 2.0 * pi;
double wp[510][510],pw[510][510],ans[510][510],ans_[510][510],val[510][510],Ans;
int n,m,N;
int rev[2400010];
double r;

class comp {
public:
    LD re, im;
    inline void getdata(LD x, LD y){
	re = x;
	im = y;
    }
    inline comp operator + (const comp &X){
	comp c;
	c.re = re + X.re;
	c.im = im + X.im;
	return c;
    }
    inline comp operator - (const comp &X){
	comp c;
	c.re = re - X.re;
	c.im = im - X.im;
	return c;
    }
    inline comp operator * (const comp &X){
	comp c;
	c.re = re * X.re - im * X.im;
	c.im = re * X.im + im * X.re;
	return c;
    }
}A[1200010], B[1200010], C[1200010], W[2][1200010];

bool ss;
inline void FFT(comp *a, int f){
    comp x, y;
    for (int i = 0; i < N; i++)
	if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int i = 1; i < N; i <<= 1){
	for (int j = 0, t = N/ (i << 1); j < N; j += i << 1)
	    for (int k = 0, l = 0; k < i; l += t, k++){
		x = W[f][l] * a[j + k + i];
		y = a[j + k];
		a[j + k] = y + x;
		a[j + k + i] = y - x;
	    }
    }
    if (f) for (int i = 0; i < N; i++)
	       a[i].re /= N;
}

inline void Solve() {
    for (N = 1; N < n * m * 2; N<<= 1);
    N <<= 1;
    for (int i = 0; i < N; i++){
	int x = i, y = 0;
	for (int k = 1; k < N; x >>= 1, k <<= 1)
	    (y <<= 1) |= x & 1;
	rev[i] = y;
    }
    for (int i = 0; i < N; i++){
	W[0][i].getdata(cos(tpi * i / N), sin(tpi * i / N));
	W[1][i].im = -W[0][i].im;
	W[1][i].re = W[0][i].re;
    }
	
    FFT(A, 0);
    FFT(B, 0);
    for (int i = 0; i < N; i++)
	C[i] = A[i] * B[i];
    FFT(C, 1);
}

inline void solve() {  
    // memset(A, 0, sizeof(A));
    //memset(B, 0, sizeof(B));
    for (int i = 1; i <= n; i++)
	for (int j = 1; j <= m; j++)
	    A[(i - 1) * 2 * m + j - 1].re = val[i][j];
    for (int i = 0; i < n; i++)
	for (int j = 1; j < m; j++) {
	    if (sqrt((double) (i * i + j * j)) + eps >= r) continue;
	    B[i * 2 * m + j].re = 1.0 / (sqrt((double) (i * i + j * j)) + 1.0);
	}
    Solve();
    for (int i = 1; i <= n; i++)
	for (int j = 1; j <= m; j++)
	    ans_[i][j] = C[(i - 1) * 2 * m + j - 1].re; 
    for (int i = 0; i <= N; i++) A[i].re = A[i].im = B[i].re = B[i].im = 0;
}

int main() {
    freopen("1008.in","r",stdin);
    freopen("1008.out","w",stdout);
    while (scanf("%d %d %lf",&n,&m,&r) != EOF) {
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
	for (int i = 1; i <= n; i++)
	    for (int j = 1; j <= m; j++)
		ans[i][j] += ans_[i][j];
	
	
	//-------------------------------------
	for (int i = 1; i <= n; i++)
	    for (int j = 1; j <= m; j++) {
		wp[i][j] = val[m - j + 1][i];
		pw[i][j] = ans[m - j + 1][i];
	    }
	swap(n,m);
	for (int i = 1; i <= n; i++)
	    for (int j = 1; j <= m; j++) {
		val[i][j] = wp[i][j];
		ans[i][j] = pw[i][j];
	    }
	solve();
	for (int i = 1; i <= n; i++)
	    for (int j = 1; j <= m; j++)
	        ans[i][j] += ans_[i][j];

	//-------------------------------------
	for (int i = 1; i <= n; i++)
	    for (int j = 1; j <= m; j++) {
		wp[i][j] = val[m - j + 1][i];
		pw[i][j] = ans[m - j + 1][i];
	    }
	swap(n,m);
	for (int i = 1; i <= n; i++)
	    for (int j = 1; j <= m; j++) {
		val[i][j] = wp[i][j];
		ans[i][j] = pw[i][j];
	    }
	solve();
	for (int i = 1; i <= n; i++)
	    for (int j = 1; j <= m; j++)
	        ans[i][j] += ans_[i][j];

	//-------------------------------------
	for (int i = 1; i <= n; i++)
	    for (int j = 1; j <= m; j++) {
		wp[i][j] = val[m - j + 1][i];
		pw[i][j] = ans[m - j + 1][i];
	    }
	swap(n,m);
	for (int i = 1; i <= n; i++)
	    for (int j = 1; j <= m; j++) {
		val[i][j] = wp[i][j];
		ans[i][j] = pw[i][j];
	    }
	solve();
	for (int i = 1; i <= n; i++)
	    for (int j = 1; j <= m; j++)
	        ans[i][j] += ans_[i][j];

	Ans = 0;
	for (int i = 1; i <= n; i++)
	    for (int j = 1; j <= m; j++)
		Ans = max(Ans,ans[i][j]);
	printf("%.3lf\n",Ans);
    }
    return 0;
}
