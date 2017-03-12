#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#define maxn 3010
using namespace std;

map<int,int> mpx,mpy;

typedef map<int,int> :: iterator poi;

struct str { int x,y,num; } dot[maxn];

int X[3010],Y[3010];
char C[3010];
int ans,tpx,tpy,n,top,tp,px,py,p;
int pasx[101000],pasy[101000],nexx[101000],nexy[101000];

bool cmp(const str &a, const str &b) {
	return (a.x < b.x || (a.x == b.x && a.y < b.y));
}

bool pmc(const str &a, const str &b) {
	return (a.y < b.y || (a.y == b.y && a.x < b.x));
}

void del(int u) {
	nexx[pasx[u]] = nexx[u];
	pasx[nexx[u]] = pasx[u];
	nexy[pasy[u]] = nexy[u];
	pasy[nexy[u]] = pasy[u];
}

void rec(int u) {
	nexx[pasx[u]] = u;
	pasx[nexx[u]] = u;
	nexy[pasy[u]] = u;
	pasy[nexy[u]] = u;
}

void solve(int u,int st) {
	ans = max(ans, st);
	int v;
	if (C[u] == '>') v = nexx[u];
	else if (C[u] == '<') v = pasx[u];
	else if (C[u] == 'v') v = nexy[u];
	else v = pasy[u];
	if (v > tp) return;
	del(u);
	solve(v, st + 1);
	rec(u);
}

int main() {
	//freopen("B.in","r",stdin);
	//freopen("B.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d %c",&X[i],&Y[i],&C[i]);
		mpx[X[i]] = 1;
		mpy[Y[i]] = 1;		
	}
	tpx = 0; tpy = 0;
	for (poi i = mpx.begin(); i != mpx.end(); i++)
		i -> second = ++tpx;
	for (poi i = mpy.begin(); i != mpy.end(); i++)
		i -> second = ++tpy;
	for (int i = 1; i <= n; i++) {
		dot[i] = (str) { mpx[X[i]], mpy[Y[i]], i };		
	}
	sort(dot + 1, dot + n + 1, pmc);
	tp = top = n; py = 0; p = 0;
	for (int i = 1; i <= n; i++) {
		if (py != dot[i].y) {
			if (p) {
				nexx[p] = ++top;
				pasx[top] = p;
			}
			py = dot[i].y;
			p = ++top;
		}
		nexx[p] = dot[i].num;
		pasx[dot[i].num] = p;
		p = dot[i].num;		
	}
	
	if (p) {
		nexx[p] = ++top;
		pasx[top] = p;
	}
	sort(dot + 1, dot + n + 1, cmp);
	px = 0; p = 0;
	for (int i = 1; i <= n; i++) {
		if (px != dot[i].x) {
			if (p) {
				nexy[p] = ++top;
				pasy[top] = p;
			}
			px = dot[i].x;
			p = ++top;
		}
		nexy[p] = dot[i].num;
		pasy[dot[i].num] = p;
		p = dot[i].num;
	}

	if (p) {
		nexy[p] = ++top;
		pasy[top] = p;
	}
	
	for (int i = 1; i <= n; i++) {
		solve(i, 0);
	}

	printf("%d\n",ans + 1);
	
	return 0;
}
