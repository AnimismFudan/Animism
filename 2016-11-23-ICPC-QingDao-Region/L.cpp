#include <bits/stdc++.h>
using namespace std;

bool stt;

int Test, N, Q, pt, len, ans;
int st[100010], ne[200010], go[200010], w[200010];
int dis[100010], dep[100010], fa[100010];
int Log[100010];
int dfn[100010], in[100010], out[100010];

class line{
	public:
	int x, y, w;
}L[100010];

class rec{
	public:
	int l, r, c;
}q[10];

int STM[18][100010];

class segleaf{
	public:
	int a[2];
	int d;
	void clear(){
		a[0] = a[1] = d = 0;
	}
}STS[18][100010];

bool enn;

inline void Add(int x, int y, int ww){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
	w[pt] = ww;
}

inline int get_lca(int x, int y){
	if (x == y) return x;
	if (in[x] > in[y]) swap(x, y);
	if (out[x] >= out[y]) return x;
	int delta = in[y] - in[x];
	int t = Log[delta];
	int t1 = STM[t][in[x]];
	int t2 = STM[t][in[y] - (1 << t) + 1];
	int t3;
	if (dep[t1] > dep[t2]) t3 = t2;
	else t3 = t1;
	return fa[t3];
}

inline int dist(int x, int y){
	int t = get_lca(x, y);
	return dis[x] - dis[t] + dis[y] - dis[t];
}

inline segleaf operator + (const segleaf &A, const segleaf &B){
	if (!A.a[0] && !A.a[1])
		return B;
	segleaf C;
	C = A;
	if (C.d < B.d)
		C = B;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			if (C.d < dist(A.a[i], B.a[j])){
				C.a[0] = A.a[i];
				C.a[1] = B.a[j];
				C.d = dist(A.a[i], B.a[j]);
			}
	return C;
}

void dfs(int x){
	dfn[++len] = x;
	in[x] = len;
	for (int i = st[x]; i; i = ne[i])
		if (go[i] != fa[x]){
			dis[go[i]] = dis[x] + w[i];
			dep[go[i]] = dep[x] + 1;
			fa[go[i]] = x;
			dfs(go[i]);
		}
	out[x] = len;
}

inline void get_Twice(){
	for (int i = 1; i <= N; i++)
		STM[0][i] = dfn[i];
	for (int t = 1, s = 1; t <= 17; t++, s <<= 1)
		for (int i = 1; i <= N; i++){
			int x = STM[t - 1][i];
			if (i + s <= N){
				int y = STM[t - 1][i + s];
				if (dep[x] > dep[y])
					x = y;
			}
			STM[t][i] = x;
		}
	for (int i = 1; i <= N; i++){
		segleaf p;
		p.a[0] = p.a[1] = dfn[i];
		p.d = 0;
		STS[0][i] = p;
	}
	for (int t = 1, s = 1; t <= 17; t++, s <<= 1)
		for (int i = 1; i <= N; i++){
			STS[t][i] = STS[t - 1][i];
			if (i + s <= N)
				STS[t][i] = STS[t][i] + STS[t - 1][i + s];
		}
}

inline void Cut(int l, int r, int c){
	for (int i = 1; i <= len; i++)
		if (max(q[i].l, l) <= min(q[i].r, r)){
			int ll = q[i].l;
			int rr = q[i].r;
			int cc = q[i].c;
			q[i].l = max(l, ll);
			q[i].r = min(r, rr);
			q[i].c = c;
			if (ll < l){
				++len;
				q[len].l = ll;
				q[len].r = l - 1;
				q[len].c = cc;
			}
			if (r < rr){
				++len;
				q[len].l = r + 1;
				q[len].r = rr;
				q[len].c = cc;
			}
		}
}

inline int Deal(int cc){
	segleaf p1;
	p1.clear();
	for (int i = 1; i <= len; i++)
		if (q[i].c == cc){
			int delta = q[i].r - q[i].l;
			int t = Log[delta];
			p1 = p1 + STS[t][q[i].l];
			p1 = p1 + STS[t][q[i].r - (1 << t) + 1];
		}
	return dist(p1.a[0], p1.a[1]);
}

inline void read(int &x){
	char ch = getchar();
	while (ch < '0' || ch > '9')
		ch = getchar();
	x = 0;
	while (ch >= '0' && ch <= '9'){
		x = x * 10 + ch - '0';
		ch = getchar();
	}
}

register char *_sp __asm__("rsp");

int main() {
	const int size = 64 * 1024 * 1024;
	static char *sys, *mine(new char[size] + size - 4096);
	sys = _sp;
	_sp = mine;
	
	freopen("L.in", "r", stdin);
	freopen("L.out", "w", stdout);
	
	for (int i = 1; i <= 100000; i++){
		Log[i] = Log[i - 1];
		if (i >= (1 << (Log[i] + 1)))
			Log[i]++;
	}
	
	read(Test);
	while (Test--){
		read(N);
		read(Q);
		pt = 0;
		len = 0;
		for (int i = 1; i <= N; i++){
			st[i] = 0;
			fa[i] = 0;
		}
		for (int i = 1; i < N; i++){
			int x, y, w;
			read(x);
			read(y);
			read(w);
			Add(x, y, w);
			Add(y, x, w);
			L[i].x = x;
			L[i].y = y;
			L[i].w = w;
		}
		dis[1] = dep[1] = 1;
		dfs(1);
		for (int i = 1; i < N; i++)
			if (dep[L[i].x] > dep[L[i].y])
				swap(L[i].x, L[i].y);
		get_Twice();
		for (int i = 1; i <= Q; i++){
			int x, y;
			read(x);
			read(y);
			if (dep[L[x].x] > dep[L[y].x])
				swap(x, y);
			len = 1;
			q[1].l = 1;
			q[1].r = N;
			q[1].c = 1;
			Cut(in[L[x].y], out[L[x].y], 2);
			Cut(in[L[y].y], out[L[y].y], 3);
			ans = 0;
			ans = max(ans, Deal(1));
			ans = max(ans, Deal(2));
			ans = max(ans, Deal(3));
			printf("%d\n", ans);
		}
	}
	
	_sp = sys;
	return 0;
}
