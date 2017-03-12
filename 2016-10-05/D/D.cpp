#include <bits/stdc++.h>
#define maxn 30100
#define midl ((L + R) >> 1)
#define midr (midl + 1)
#define lk (u << 1)
#define rk (lk | 1)
using namespace std;

struct Proc {
    int x1,x2,y1,y2;
} proc[1010000];

struct pmc {
    bool operator () (int a,int b) {
	return (proc[a].x2 < proc[b].x2 || (proc[a].x2 == proc[b].x2 && a < b));
    }
};
    
set<int,pmc> st;

map<int,int> mpx,mpy;
typedef map<int,int> :: iterator poi;

int top,n,T,tpx,tpy;
int X[maxn],Y[maxn];
int mark[maxn << 2],val[maxn << 2];
bool flag;

void init() {
    tpx = tpy = top = 0;
    mpx.clear();
    mpy.clear();
    flag = false;
}

void add(int x1,int x2,int y1,int y2) {
    proc[++top] = (Proc) { x1, x2, y1, y2 };
}

void prepare() {
    for (int i = 1; i <= n; i++) {
	int x1,x2,y1,y2;
	x1 = X[i], x2 = X[i + 1];
	y1 = Y[i], y2 = Y[i + 1];
	if (x1 == x2) {
	    if (y2 > y1)
		add(x1 + 1, tpx, y1 + 1, y2 - 1);
	    else
		add(1, x1 - 1, y2 + 1, y1 - 1);
	} else {
	    if (x2 > x1)
		add(x1 + 1, x2 - 1, 1, y1 - 1);
	    else
		add(x2 + 1, x1 - 1, y1 + 1, tpy);
	}	
    }
    
    for (int i = 1; i <= n; i++) {
	int x1,x2,x3,y1,y2,y3;
	x1 = X[i]; y1 = Y[i];
	x2 = X[i + 1]; y2 = Y[i + 1];
	x3 = X[i + 2]; y3 = Y[i + 2];
	int vx1,vx2,vy1,vy2;
	vx1 = x2 - x1; vy1 = y2 - y1;
	vx2 = x3 - x2; vy2 = y3 - y2;
	if (vx1 * vy2 - vx2 * vy1 < 0) continue;
	if (vx1 > 0 && !vy1)
	    add(x2, tpx, 1, y2);
	else if (vx1 < 0 && !vy1)
	    add(1, x2, y2, tpy);
	else if (vy1 > 0 && !vx1) {
	    add(x2, tpx, y2, tpy);
	} else
	    add(1, x2, 1, y2);
    }
}

void down(int u, int L, int R) {
    if (!mark[u]) return;
    val[u] += mark[u];
    if (L < R) {
	mark[lk] += mark[u];
	mark[rk] += mark[u];
    }
    mark[u] = 0;
    return;
}

void change(int u, int L, int R, int l, int r, int k) {
    down(u, L, R);
    if (L == l && R == r) {
	mark[u] += k;
	down(u, L, R);
	return;
    }
    if (r < midr) down(rk, midr, R), change(lk, L, midl, l, r, k);
    else if (l > midl) down(lk, L, midl), change(rk, midr, R, l, r, k);
    else {
	change(lk, L, midl, l, midl, k);
	change(rk, midr, R, midr, r, k);
    }
    val[u] = min(val[lk], val[rk]);
}

void build(int u, int L, int R) {
    if (L == R) { val[u] = mark[u] = 0; return; }
    build(lk, L, midl);
    build(rk, midr, R);
    val[u] = mark[u] = 0;
    return;
}

bool cmp(const Proc &a, const Proc &b) {
    return (a.x1 < b.x1);
}

void solve() {
    st.clear();
    flag = false;
    build(1, 1, tpy);
    sort(proc + 1, proc + top + 1, cmp);
    int q = 1;
    for (int t = 1; t <= tpx; t++) {
	for (; q <= top && proc[q].x1 <= t; q++) {
	    st.insert(q);
	    change(1, 1, tpy, proc[q].y1, proc[q].y2, 1);
	}
	while (!st.empty()) {
	    int i = *st.begin();
	    if (proc[i].x2 >= t) break;
	    change(1, 1, tpy, proc[i].y1, proc[i].y2, -1);
	    st.erase(st.begin());
	}
	if (!val[1]) { flag = true; break; }
    }
}

int main() {
    freopen("D.in","r",stdin);
    freopen("D.out","w",stdout);
    for (scanf("%d",&T); T; T--) {
	scanf("%d",&n);
	init();
	for (int i = 1; i <= n; i++) {
	    scanf("%d %d",&X[i],&Y[i]);
	    mpx[X[i]] = 1;
	    mpy[Y[i]] = 1;
	}
	for (poi i = mpx.begin(); i != mpx.end(); i++)
	    i -> second = (tpx += 2);
	for (poi i = mpy.begin(); i != mpy.end(); i++)
	    i -> second = (tpy += 2);

	for (int i = 1; i <= n; i++)
	    X[i] = mpx[X[i]];
	for (int i = 1; i <= n; i++)
	    Y[i] = mpy[Y[i]];
	tpx += 2; tpy += 2;
	X[n + 1] = X[1];
	Y[n + 1] = Y[1];
	X[n + 2] = X[2];
	Y[n + 2] = Y[2];
	prepare();
	solve();
	if (flag)
	    printf("YES\n");
	else
	    printf("NO\n");
    }
    return 0;
}
