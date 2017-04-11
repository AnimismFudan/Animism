#include <bits/stdc++.h>
using namespace std;

#define LL long long

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
} seg[2000010];
int root[200010];

vector <int > LX[2000010];
vector <int > LY[2000010];

bool cmpxy (const poi &A, const poi &B){
	if (A.x != B.x) return A.x < B.x;
	return A.y < B.y;
}

bool cmpyx (const poi &A, const poi &B){
	if (A.y != B.y) return A.y < B.y;
	return A.x < B.x;
}

void build2(int &x, int l, int r){
	x = ++tot;
	if (l < r){
		int mid = (l + r) >> 1;
		build2(seg[x].lson, l, mid);
		build2(seg[x].rson, mid + 1, r);
	}
}

void build1(int x, int l, int r){
	if (l < r){
		int mid = (l + r) >> 1;
		build1(x << 1, l, mid);
		build1((x << 1) + 1, mid + 1, r);
	}
	build2(root[x], 1, leny);
}

void Init2(int x, int l, int r, const poi &X){
	LX[x].push_back(X.xp);
	LY[x].push_back(X.yp);
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
	int l = 0, r = LX[x].size();
	while (l < r){
		int mid = (l + r) >> 1;
		if (LX[x][mid] >= xp) r = mid;
		else l = mid + 1;
	}
	return l;
}

int ask_y(int x, int yp){
	int l = 0, r = LY[x].size();
	while (l < r){
		int mid = (l + r) >> 1;
		if (LY[x][mid] >= yp) r = mid;
		else l = mid + 1;
	}
	return l;
}

void ask2(int x, int l, int r, int ll, int rr){
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
//	freopen("A.in","r",stdin);
//	freopen("A.out","w",stdout);
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
	build1(1, 1, lenx);
	for (int i = 1; i <= N; i++)
		Init1(1, 1, lenx, P[i]);
	for (int i = 1; i <= tot; i++)
		sort(LX[i].begin(), LX[i].end());
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
