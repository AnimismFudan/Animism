#include <bits/stdc++.h>
using namespace std;

#define LL long long

bool stt;

const int maxn = 15000000;

int N, ansx, ansy, Q;
int xl, xr, yl, yr, xt, yt;
int lenx, leny, len, tot;
int lx[50010], ly[50010];

class poi{
	public:
	int x, y, xp, yp;
} P[50010];

class segleaf{
	public:
	int lson, rson;
} seg[maxn];
int root[200010];

int ptx, pty;
int stx[maxn], nex[maxn], gox[maxn];
int sty[maxn], ney[maxn], goy[maxn];
int Head[maxn], Tail[maxn];
int Qx[maxn], Qy[maxn];

bool enn;

void Addx(int x, int y){
	nex[++ptx] = stx[x];
	stx[x] = ptx;
	gox[ptx] = y;
}

void Addy(int x, int y){
	ney[++pty] = sty[x];
	sty[x] = pty;
	goy[pty] = y;
}

bool cmpxy (const poi &A, const poi &B){
	if (A.x != B.x) return A.x < B.x;
	return A.y < B.y;
}

bool cmpyx (const poi &A, const poi &B){
	if (A.y != B.y) return A.y < B.y;
	return A.x < B.x;
}

void Init2(int &x, int l, int r, const poi &X){
	if (!x) x = ++tot;
	Addx(x, X.xp);
	Addy(x, X.yp);
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (X.y <= mid) Init2(seg[x].lson, l, mid, X);
	else Init2(seg[x].rson, mid + 1, r, X);
}

void Init1(int x, int l, int r, const poi &X){
	Init2(root[x], 1, leny, X);
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (X.x <= mid) Init1(x << 1, l, mid, X);
	else Init1((x << 1) + 1, mid + 1, r, X);
}

int ask_x(int x, int xp){
	int l = Head[x], r = Tail[x] + 1;
	while (l < r){
		int mid = (l + r) >> 1;
		if (Qx[mid] >= xp) r = mid;
		else l = mid + 1;
	}
	return l - Head[x];
}

int ask_y(int x, int yp){
	int l = Head[x], r = Tail[x] + 1;
	while (l < r){
		int mid = (l + r) >> 1;
		if (Qy[mid] >= yp) r = mid;
		else l = mid + 1;
	}
	return l - Head[x];
}

void ask2(int x, int l, int r, int ll, int rr){
	if (!x) return;
	if (l == ll && r == rr){
		ansx += ask_y(x, yt);
		ansy += ask_x(x, xt);
		return;
	}
	int mid = (l + r) >> 1;
	if (rr <= mid) ask2(seg[x].lson, l, mid, ll, rr);
	else if (ll > mid) ask2(seg[x].rson, mid + 1, r, ll, rr);
	else ask2(seg[x].lson, l, mid, ll, mid), ask2(seg[x].rson, mid + 1, r, mid + 1, rr);
}

void ask1(int x, int l, int r, int ll, int rr){
	if (l == ll && r == rr)
		return ask2(root[x], 1, leny, yl, yr);
	int mid = (l + r) >> 1;
	if (rr <= mid) ask1(x << 1, l, mid, ll, rr);
	else if (ll > mid) ask1((x << 1) + 1, mid + 1, r, ll, rr);
	else ask1(x << 1, l, mid, ll, mid), ask1((x << 1) + 1, mid + 1, r, mid + 1, rr);
}

int main() {
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++){
		scanf("%d%d", &P[i].x, &P[i].y);
		lx[++lenx] = P[i].x;
		ly[++leny] = P[i].y;
	}
	sort(lx + 1, lx + lenx + 1);
	sort(ly + 1, ly + leny + 1);
	lenx = unique(lx + 1, lx + lenx + 1) - lx - 1;
	leny = unique(ly + 1, ly + leny + 1) - ly - 1;
	for (int i = 1; i <= N; i++){
		P[i].x = lower_bound(lx + 1, lx + lenx + 1, P[i].x) - lx;
		P[i].y = lower_bound(ly + 1, ly + leny + 1, P[i].y) - ly;
	}
	sort(P + 1, P + N + 1, cmpxy);
	len = 1;
	for (int i = 2; i <= N; i++)
		if (P[i].x != P[len].x || P[i].y != P[len].y)
			P[++len] = P[i];
	N = len;
	len = 0;
	for (int i = 2; i <= N; i++)
		if (P[i].x == P[i - 1].x) P[i].yp = P[i - 1].y;
		else P[i].yp = 0;
	sort(P + 1, P + N + 1, cmpyx);
	for (int i = 2; i <= N; i++)
		if (P[i].y == P[i - 1].y) P[i].xp = P[i - 1].x;
		else P[i].xp = 0;
	tot = 0;
	for (int i = 1; i <= N; i++)
		Init1(1, 1, lenx, P[i]);
	
	for (int i = 1; i <= tot; i++){
		int t = 0;
		for (int j = stx[i]; j; j = nex[j]){
			++t;
			Qx[len + t] = gox[j];
		}
		t = 0;
		for (int j = sty[i]; j; j = ney[j]){
			++t;
			Qy[len + t] = goy[j];
		}
		Head[i] = len + 1;
		Tail[i] = len + t;
		sort(Qx + Head[i], Qx + Tail[i] + 1);
		sort(Qy + Head[i], Qy + Tail[i] + 1);
		len += t;
	}
	scanf("%d", &Q);
	for (int i = 1; i <= Q; i++){
		scanf("%d%d%d%d", &xl, &yl, &xr, &yr);
		xl = lower_bound(lx + 1, lx + lenx + 1, xl) - lx;
		xr = upper_bound(lx + 1, lx + lenx + 1, xr) - lx - 1;
		yl = lower_bound(ly + 1, ly + leny + 1, yl) - ly;
		yr = upper_bound(ly + 1, ly + leny + 1, yr) - ly - 1;
		ansx = ansy = 0;
		if (xl <= xr && yl <= yr){
			yt = yl;
			xt = xl;
			ask1(1, 1, lenx, xl, xr);
		}
		printf("%d %d\n", ansx, ansy);
		fflush(stdout);
	}
	return 0;
}
