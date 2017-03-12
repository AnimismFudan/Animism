#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define LD long double

const LL P1 = 1004535809;
const LL P2 = 998244353;
const LL G = 3;

int N, len, Test;
LL P;
LL ans;
int a[300010], b[300010], rev[300010];
LL A[300010], B[300010], W[2][300010];
LL H1[300010], H2[300010];

inline LL quick_Multi(LL x, LL y, LL pp){
	LL s = 0, t = x;
	for (; y; y >>= 1){
		if (y & 1)s = (s + t) % pp;
		t = (t + t) % pp;
	}
	return s;
}

inline LL quick(LL x, LL y, LL pp){
	LL s = 1, t = x;
	for (; y; y >>= 1){
		if (y & 1)s = (s * t) % pp;
		t = (t * t) % pp;
	}
	return s;
}

inline void FFT(LL *a, int f){
	for (int i = 0; i < N; i++)
		if (i < rev[i])
			swap(a[i], a[rev[i]]);
	for (int i = 1; i < N; i <<= 1){
		for (int j = 0, t = N / (i << 1); j < N; j += i << 1)
			for (int k = 0, l = 0; k < i; l += t, k++){
				LL x, y;
				x = W[f][l] * a[j + k + i] % P;
				y = a[j + k];
				a[j + k] = (y + x) % P;
				a[j + k + i] = (y - x + P) % P;
			}
	}
	if (f)
		for (int i = 0, x = quick(N, P - 2, P); i < N; i++)
			a[i] = a[i] * x % P;
}

inline void work(){
	for (int i = 0; i < N; i++)
		A[i] = B[i] = 0;
	for (int i = 0; i < len; i++){
		A[len - 1 - i] = a[i];
    	B[len + i] = B[i] = b[i];
  	}
  	
    for (int i = 0; i < N; i++){
		int x = i, y = 0;
		for (int k = 1; k < N; x >>= 1, k <<= 1)
			(y <<= 1) |= x & 1;
		rev[i] = y;
	}
	W[0][0] = W[1][0] = 1;
	LL x = quick(G, (P - 1) / N, P), y = quick(x, P - 2, P);
	for (int i = 1; i < N; i++){
		W[0][i] = x * W[0][i - 1] % P;
		W[1][i] = y * W[1][i - 1] % P;
	}
	
	FFT(A, 0);
	FFT(B, 0);
	for (int i = 0; i < N; i++)
		A[i] = A[i] * B[i];
	FFT(A, 1);
}

inline void get_Ans(){
	LL t1, t2, res, M;
	M = P1 * P2;
	t1 = quick(P2, P1 - 2, P1);
	t2 = quick(P1, P2 - 2, P2);
	t1 = t1 * P2 % M;
	t2 = t2 * P1 % M;
	for (int i = 0; i < N; i++){
		res = (quick_Multi(t1, H1[i], M) + quick_Multi(t2, H2[i], M)) % M;
		ans = max(ans, res);
	}
}

int main() {
    freopen("F.in","r",stdin);
    freopen("F.out","w",stdout);
    scanf("%d", &Test);
    while (Test--){
    	scanf("%d", &len);
    	for (int i = 0; i < len; i++)
    		scanf("%d", &a[i]);
    	for (int i = 0; i < len; i++)
    		scanf("%d", &b[i]);
    	for (N = 1; N < len << 1; N <<= 1);
    	N <<= 1;
    	
    	P = P1;
    	work();
    	for (int i = 0; i < N; i++)
    		H1[i] = A[i];
    	
    	P = P2;
    	work();
    	for (int i = 0; i < N; i++)
    		H2[i] = A[i];
    	
    	ans = 0;
    	get_Ans();
    	ans = -ans * 2;
    	for (int i = 0; i < len; i++){
    		ans += (LL)a[i] * a[i];
    		ans += (LL)b[i] * b[i];
    	}
    	cout << ans << endl;
    }
    return 0;
}
