#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, M, Q, tot, root, pt, len, High;
double Xp;
bool bound[400010];
int st[200010], ne[400010], go[400010];
int num[400010], vis[400010], pos[400010];

class poi{
	public:
	double x, y;
}P[200010];

class line{
	public:
	int s, t, pos, rev, n;
	double selta;
}L[400010];

class rec{
	public:
	double x, y;
	int n, ans, temp;
	poi s, t;
}q[600010];

class splay_leaf{
	public:
	int lson, rson, p, sum, n;
	poi s, t;
}spl[600010], temp;

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

double xet (poi A, poi B){
	return A.x * B.y - B.x * A.y;
}

bool cmpxs(const line &A, const line &B){
	if (A.s != B.s)
		return A.s < B.s;
	return A.selta < B.selta;
}

bool cmpxt(const rec &A, const rec &B){
	if (A.x != B.x)
		return A.x < B.x;
	return A.temp < B.temp;
}

bool cmpn(const rec &A, const rec &B){
	return A.n < B.n;
}

void make(int x){
	spl[x].sum = 1;
	int lson = spl[x].lson;
	int rson = spl[x].rson;
	if (lson)spl[x].sum += spl[x].lson;
	if (rson)spl[x].sum += spl[x].rson;
}

void Right(int x){
	int y = spl[x].p, z = spl[y].p;
	if (spl[z].lson == y)spl[z].lson = x;
	else spl[z].rson = x;
	spl[x].p = z;
	spl[y].lson = spl[x].rson;
	spl[spl[y].lson].p = y;
	spl[x].rson = y;
	spl[y].p = x;
	make(y);
	make(x);
}

void Left(int x){
	int y = spl[x].p, z = spl[y].p;
	if (spl[z].lson == y)spl[z].lson = x;
	else spl[z].rson = x;
	spl[x].p = z;
	spl[y].rson = spl[x].lson;
	spl[spl[y].rson].p = y;
	spl[x].lson = y;
	spl[y].p = x;
	make(y);
	make(x);
}

void splay(int x){
	int y, z;
	while (spl[x].p){
		y = spl[x].p;
		z = spl[y].p;
		if (z){
			if (spl[z].lson == y){
				if (spl[y].lson == x)
					Right(y), Right(x);
					else Left(x), Right(x);
			}else{
				if (spl[y].lson == x)
					Right(x), Left(x);
					else Left(y), Left(x);
			}
		}
		else if (spl[y].lson == x)Right(x);
			else Left(x);
	}
	root = x;
}

bool small(const splay_leaf &A, const splay_leaf &B){
	double t1 = A.s.y + double (A.t.y - A.s.y) / (A.t.x - A.s.x) * (Xp - A.s.x);
	double t2 = B.s.y + double (B.t.y - B.s.y) / (B.t.x - B.s.x) * (Xp - B.s.x); 
	return t1 < t2;
}

double calc_y(double x, const line &X){
	return P[X.s].y + (P[X.t].y - P[X.s].y) / (P[X.t].x - P[X.s].x) * (x - P[X.s].x);
}

bool small(double x, double y, const splay_leaf &X){
	double yy = X.s.y + (X.t.y - X.s.y) / (X.t.x - X.s.x) * (x - X.s.x);
	return y < yy;
}

void Insert(rec X){
	int x = root, p = 0;
	temp.s = X.s;
	temp.t = X.t;
	for (; x;){
		p = x;
		spl[x].sum++;
		if (small(temp, spl[x]))
			x = spl[x].lson;
			else x = spl[x].rson;
	}
	x = ++tot;
	spl[x].s = temp.s;
	spl[x].t = temp.t;
	spl[x].sum = 1;
	spl[x].n = X.n;
	spl[x].p = p;
	if (small(temp, spl[p]))
		spl[p].lson = x;
		else spl[p].rson = x;
	splay(x);
}

void Delete(int x){
	splay(x);
	int lson = spl[x].lson;
	int rson = spl[x].rson;
	spl[x].lson = spl[x].rson = spl[lson].p = spl[rson].p = 0;
	if (!lson)root = rson;
	else{
		while (spl[lson].rson)
			lson = spl[lson].rson;
		splay(lson);
		spl[lson].rson = rson;
		spl[rson].p = lson;
		make(lson);
	}
}

void calc(rec &X){
	int x = root, p = 0;
	for (; x;){
		p = x;
		if (small(X.x, X.y, spl[x]))
			x = spl[x].lson;
		else x = spl[x].rson;
	}
	splay(p);
	int res = spl[spl[p].lson].sum;
	if (p && !small(X.x, X.y, spl[p]))
		res++;
	X.ans = res & 1;
}

int Find(rec &X){
	int x = root, p = 0;
	for (; x;){
		p = x;
		if (small(X.x, X.y, spl[x]))
			x = spl[x].lson;
		else x = spl[x].rson;
	}
	if (!p)
		return 0;
	splay(p);
	if (small(X.x, X.y, spl[p]))return -spl[p].n;
	int rson = spl[p].rson;
	while (rson && spl[rson].lson)
		rson = spl[rson].lson;
	return -spl[rson].n;
}

void dfs(int x){
	vis[x] = 1;
	if (!High || P[x].y > P[High].y)
		High = x;
	for (int i = st[x]; i; i = ne[i])
		if (!vis[go[i]])
			dfs(go[i]);
}

register char *_sp __asm__("rsp");

int main(){
	const int size=16*1024*1024;
	static char *sys, *mine(new char[size]+size-4096);
	sys=_sp;
	_sp=mine;
	
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
	
	scanf("%d%d%d", &N, &M, &Q);
	for (int i = 1; i <= N; i++)
		scanf("%lf%lf", &P[i].x, &P[i].y);
	for (int i = 1; i <= M; i++){
		scanf("%d%d", &L[i].s, &L[i].t);
		if (P[L[i].s].x > P[L[i].t].x)
			swap(L[i].s, L[i].t);
		Add(L[i].s, L[i].t);
		Add(L[i].t, L[i].s);
	}
	
	len = 0;
	for (int i = 1; i <= M; i++){
		if (!vis[i]){
			High = 0;
			dfs(i);
			++len;
			q[len].x = P[High].x;
			q[len].y = P[High].y;
			q[len].temp = 0;
			q[len].n = High;
		}
		if (P[L[i].s].x != P[L[i].t].x){
			++len;
			q[len].x = P[L[i].s].x;
			q[len].s = P[L[i].s];
			q[len].t = P[L[i].t];
			q[len].temp = 1;
			q[len].n = -i;
			++len;
			q[len].x = P[L[i].t].x;
			q[len].s = P[L[i].s];
			q[len].t = P[L[i].t];
			q[len].temp = -1;
			q[len].n = -i;
		}
	}
	sort(q + 1,q + len + 1, cmpxt);
	root = 0;
	for (int i = 1; i <= len; i++)
		if (q[i].temp == 1){
			Xp = q[i].x + 0.5;
			Insert(q[i]);
			pos[-q[i].n] = tot;
		}else if (q[i].temp == -1)
			Delete(pos[-q[i].n]);
		else{
			int x = Find(q[i]);
			if (x){
				++N;
				P[N].x = q[i].x;
				P[N].y = calc_y(q[i].x, L[x]);
				++M;
				L[M] = L[x];
				L[x].s = N;
				L[M].t = N;
				++M;
				L[M].s = High;
				L[M].t = N;
			}
		}
	
	memset(st, 0 , sizeof(st));
	pt = 0;
	for (int i = 1; i <= M; i++){
		L[M + i] = L[i];
		swap(L[i].s, L[i].t);
		L[i].n = (i - 1) << 1;
		L[M + i].n = ((i - 1) << 1) + 1;
	}
	M <<= 1;
	for (int i = 0; i < M; i++)L[i] = L[i + 1];
	for (int i = 0; i < M; i++)
		L[i].selta = atan2(P[L[i].t].y - P[L[i].s].y, P[L[i].t].x - P[L[i].s].x);
	sort(L, L + M, cmpxs);
	for (int i = 0; i < M; i++)
		pos[L[i].n] = i;
	for (int i = 0; i < M; i++){
		Add(L[i].s, L[i].t);
		L[i].pos = pt;
		num[pt] = i;
	}
	for (int i = 0; i < M; i++)
		L[i].rev = L[pos[L[i].n ^ 1]].pos;
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < M; i++)
		if (!vis[i]){
			++ tot;
			int x = i;
			double area = 0;
			for (; !vis[x]; ){
				vis[x] = tot;
				area += xet(P[L[x].s], P[L[x].t]);
				if (ne[L[x].rev])
					x = num[ne[L[x].rev]];
				else	x = num[st[L[x].t]];
			}
			if (area < 0)
				bound[tot] = 1;
		}
	
	tot = 0;
	len = 0;
	for (int i = 0; i < M; i++)
		if (bound[vis[i]] && P[L[i].s].x != P[L[i].t].x){
			++len;
			q[len].temp = 1;
			q[len].s = P[L[i].s];
			q[len].t = P[L[i].t];
			if (q[len].s.x > q[len].t.x)
				swap(q[len].s, q[len].t);
			q[len].x = q[len].s.x;
			q[len].n = -i;
			
			++len;
			q[len].temp = 2;
			q[len].s = P[L[i].s];
			q[len].t = P[L[i].t];
			if (q[len].s.x > q[len].t.x)
				swap(q[len].s, q[len].t);
			q[len].x = q[len].t.x;
			q[len].n = -i;
		}
	
	for (int i = 1; i <= Q; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		++len;
		q[len].temp = 0;
		q[len].x = x;
		q[len].y = y;
		q[len].n = i;
	}
	
	memset(pos, 0, sizeof(pos));
	sort(q + 1, q + len + 1, cmpxt);
	root = 0;
	for (int i = 1; i <= len; i++)
		if (q[i].temp == 0)
			calc(q[i]);
		else if (q[i].temp == 1){
			Xp = q[i].x + 0.5;
			Insert(q[i]);
			pos[-q[i].n] = tot;
		}
		else Delete(pos[-q[i].n]);
	
	sort(q + 1, q + len + 1, cmpn);
	
	for (int i = 1; i <= len; i++)
		if (q[i].n > 0){
			if (q[i].ans)printf("Yes\n");
				else printf("No\n");
		}
	
	_sp=sys;
	
	return 0;
}

