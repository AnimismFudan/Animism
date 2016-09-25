#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define LD long double

const double eps = 1e-7;
const LD pi = 3.141592653589793238462643383l;
int N, len, Test;
LL ans;
int a[600010], b[600010], rev[600010];

class comp{
	public:
	LD re, im;
	void getdata(LD x, LD y){
		re = x;
		im = y;
	}
	comp operator + (const comp &X){
		comp c;
		c.re = re + X.re;
		c.im = im + X.im;
		return c;
	}
	comp operator - (const comp &X){
		comp c;
		c.re = re - X.re;
		c.im = im - X.im;
		return c;
	}
	comp operator * (const comp &X){
		comp c;
		c.re = re * X.re - im * X.im;
		c.im = re * X.im + im * X.re;
		return c;
	}
}A[600010], B[600010], W[2][600010];


void FFT(comp *a, int f){
	comp x, y;
	for (int i = 0; i < N; i++)
		if (i < rev[i])
			swap(a[i], a[rev[i]]);
	for (int i = 1; i < N; i <<= 1){
		for (int j = 0, t = N / (i << 1); j < N; j += i << 1)
			for (int k = 0, l = 0; k < i; l += t, k++){
				x = W[f][l] * a[j + k + i];
				y = a[j + k];
				a[j + k] = y + x;
				a[j + k + i] = y - x;
			}
	}
	if (f)
		for (int i = 0; i < N; i++)
			a[i].re /= N;
}

//1004535809 (3)

int main() {
    freopen("F.in","r",stdin);
    freopen("F.out","w",stdout);
    scanf("%d", &Test);
    while (Test--){
    	scanf("%d", &len);
    	memset(A, 0, sizeof(A));
    	memset(B, 0, sizeof(B));
    	for (int i = 0; i < len; i++){
    		scanf("%d", &a[i]);
    		A[len - 1 - i].re = a[i];
    	}
    	for (int i = 0; i < len; i++){
    		scanf("%d", &b[i]);
    		B[len + i].re = B[i].re = b[i];
    	}
    	for (N = 1; N < len << 1; N <<= 1);
    	N <<= 1;
    	for (int i = 0; i < N; i++){
    		int x= i, y = 0;
    		for (int k = 1; k < N; x >>= 1, k <<= 1)
    			(y <<= 1) |= x & 1;
    		rev[i] = y;
    	}
    	for (int i = 0; i < N; i++){
    		W[0][i].getdata(cos(2 * pi * i / N), sin(2 * pi * i / N));
    		W[1][i].im = -W[0][i].im;
    		W[1][i].re = W[0][i].re;
    	}
    	
    	FFT(A, 0);
    	FFT(B, 0);
    	for (int i = 0; i < N; i++)
    		A[i] = A[i] * B[i];
    	FFT(A, 1);
    	ans = 0;
    	for (int i = 0; i < N; i++){
    		LL res = (LL)(A[i].re + eps);
    		ans = max(ans, res);
    	}
    	ans = -ans * 2;
    	for (int i = 0; i < len; i++){
    		ans += (LL)a[i] * a[i];
    		ans += (LL)b[i] * b[i];
    	}
    	cout << ans << endl;
    }
    return 0;
}
