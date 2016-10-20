#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double

const int maxn = 200000;
const int temp_maxn = 100000;

const LD pi = 3.141592653589793238462643383l;

int L, M, N;
LL ans, res, a1, b1, c1, a2, b2, c2, a3, b3, c3, fm;
int rev[800010];

class poi{
	public:
	LL x, y;
	bool operator < (const poi &X)const{
		if (x != X.x) return x < X.x;
		return y < X.y;
	}
}A[800010], B[800010], C[800010], p;

map <poi, int> mapA, mapB, mapC;

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
}a[800010], b[800010], c[800010], W[2][800010];

void FFT(comp *a, int f){
	comp x, y;
	for (int i = 0; i < N; i++)
		if (i < rev[i])
			swap(a[i], a[rev[i]]);
	for (int i = 1; i < N; i <<= 1)
		for (int j = 0, t = N / (i << 1); j < N; j += i << 1)
			for (int k = 0, l = 0; k < i; l += t, k++){
				x = W[f][l] * a[j + k + i];
				y = a[j + k];
				a[j + k] = y + x;
				a[j + k + i] = y - x;
			}
	if (f)
		for (int i = 0; i < N; i++)
			a[i].re /= N;
}


void dodododo(){
	for (N = 1; N <= maxn; N <<= 1);
	N <<= 1;
	for (int i = 0; i < N; i++){
		int x = i, y = 0;
		for (int k = 1; k < N; x >>= 1, k <<= 1) (y <<= 1) |= x & 1;
		rev[i] = y;
	}
	for (int i = 0; i < N; i++){
		W[0][i].getdata (cos(2 * pi * i / N), sin(2 * pi * i / N));
		W[1][i].im = -W[0][i].im;
		W[1][i].re = W[0][i].re;
	}
	
	FFT(a, 0);
	FFT(b, 0);
	for (int i = 0; i < N; i++)
		c[i] = a[i] * b[i];
	FFT(c, 1);
}

int LD2int(LD x){
	int y = int (x);
	if (fabs(x - y) > fabs((y + 1 - x)))
		y++;
	if (fabs(x - y) > fabs((y - 1 - x)))
		y++;
	return y;
}

int main(){
	freopen("I.in", "r", stdin);
	freopen("I.out", "w", stdout);
	scanf("%d%d%d", &L, &M, &N);
	for (int i = 1; i <= L; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		x += temp_maxn;
		y += temp_maxn;
		A[i].x = x;A[i].y = y;
		mapA[A[i]]++;
	}
	for (int i = 1; i <= M; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		x += temp_maxn;
		y += temp_maxn;
		B[i].x = x;B[i].y = y;
		mapB[B[i]]++;
	}
	for (int i = 1; i <= N; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		x += temp_maxn;
		y += temp_maxn;
		C[i].x = x;C[i].y = y;
		mapC[C[i]]++;
	}
	sort(A + 1, A + L + 1);
	sort(B + 1, B + M + 1);
	sort(C + 1, C + N + 1);
	a1 = A[L].x - A[1].x; b1 = A[L].y - A[1].y; c1 = -A[1].x * a1 - A[1].y * b1; swap(a1, b1); b1 = -b1;
	a2 = B[M].x - B[1].x; b2 = B[M].y - B[1].y; c2 = -B[1].x * a2 - B[1].y * b2; swap(a2, b2); b2 = -b2;
	a3 = C[N].x - C[1].x; b3 = C[N].y - C[1].y; c3 = -C[1].x * a3 - C[1].y * b3; swap(a3, b3); b3 = -b3;
	if (!a2 && !b2){
		for (int i = 1; i <= max(L, M); i++)
			swap(A[i], B[i]);
		swap(L, M);
	}
	if (!a1 && !b1){
		for (int i = 1; i <= M; i++){
			p.x = (A[1].x + B[i].x);
			if (p.x & 1)continue;
			p.x >>= 1;
			p.y = (A[1].y + B[i].y);
			if (p.y & 1)continue;
			p.y >>= 1;
			res = mapC[p];
			ans += L * res;
		}
		cout << ans << endl;
		return 0;
	}
	if (!a3 && !b3){
		for (int i = 1; i <= L; i++){
			p.x = 2 * C[1].x - A[i].x;
			p.y = 2 * C[1].y - A[i].y;
			res = mapB[p];
			ans += N * res;
		}
		cout << ans << endl;
		return 0;
	}
	if (a1 * b2 == a2 * b1){
		if (A[1].x == A[L].x){
			for (int i = 1; i <= L; i++)a[A[i].y].re++;
			for (int i = 1; i <= M; i++)b[B[i].y].re++;
			dodododo();
			for (int i = 1; i <= N; i++)
				ans += LD2int(c[C[i].y << 1].re);
			cout << ans << endl;
			return 0;
		}else{
			for (int i = 1; i <= L; i++)a[A[i].x].re++;
			for (int i = 1; i <= M; i++)b[B[i].x].re++;
			dodododo();
			for (int i = 1; i <= N; i++)
				ans += LD2int(c[C[i].x << 1].re);
			cout << ans << endl;
			return 0;
		}
	}else{
		for (int i = 1; i <= N; i++){
			if (b1){
				fm = (b1 * a2 - a1 * b2) * b3;
				p.x = (b1 * b2 * c3 * 2 - b1 * c2 * b3 - c1 * b2 * b3 + b1 * 2 * (b2 * a3 - a2 * b3) * C[i].x) / fm;
				p.y = (-c1 - a1 * p.x) / b1;
			}else{
				fm = (b1 * a2 - a1 * b2) * a3;
				p.y = (a1 * a2 * c3 * 2 - c1 * a2 * a3 - a1 * c2 * a3 + a1 * 2 * (a2 * b3 - b2 * a3) * C[i].y) / fm;
				p.x = (-c1 - b1 * p.y) / a1;
			}
			res = mapA[p];
			p.x = C[i].x * 2 - p.x;
			p.y = C[i].y * 2 - p.y;
			res = res * mapB[p];
			ans += res;
		}
		cout << ans << endl;
		return 0;
	}
}
