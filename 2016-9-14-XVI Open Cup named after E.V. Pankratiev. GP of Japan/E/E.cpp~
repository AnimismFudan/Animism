#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, M, Q, tot, root, pt, len;

bool bound[100010];
int st[100010], ne[200010], go[200010];
int num[200010], vis[200010], pos[200010];

class poi{
	public:
	LL x, y;
}P[100010];

class line{
	public:
	int x, y, pos, rev, n;
	double selta;
}L[200010];

class rec{
	public:
	LL x, y;
	int n, ans, temp;
	poi s, t;
}q[300010];

class splay_leaf{
	public:
	int lson, rson, p, sum;
	poi s, t;
}spl[200010], temp;

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

LL xet (poi A, poi B){
	return A.x * B.y - B.x * A.y;
}

bool cmpxs(const line &A, const line &B){
	if (A.x == B.x)
		return A.x < B.x;
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
					Right(y), Left(x);
					else Left(x), Left(x);
			}
		}
		else if (spl[y].lson == x)Right(x);
			else Left(x);
	}
	root = x;
}

bool small(const splay_leaf &A, const splay_leaf &B){
	return (A.s.y + A.t.y) < (B.s.y + B.t.y);
}

bool small(LL x, LL y, const splay_leaf &X){
	return (X.t.x - X.s.x) * (y - X.s.y) - (x - X.s.x) * (X.t.y - X.s.y);
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
	if (!small(X.x, X.y, spl[p]))
		res++;
	X.ans = res & 1;
}

int main(){
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
	
	scanf("%d%d%d", &N, &M, &Q);
	for (int i = 1; i <= N; i++)
		scanf("%lld%lld", &P[i].x, &P[i].y);
	for (int i = 1; i <= M; i++){
		scanf("%d%d", &L[i].x, &L[i].y);
		L[M + i] = L[i];
		swap(L[i].x, L[i].y);
		L[i].n = i;
	}
	M <<= 1;
	for (int i = 0; i < M; i++)L[i] = L[i + 1];
	for (int i = 0; i < M; i++)
		L[i].selta = atan2(P[L[i].y].y - P[L[i].x].y, P[L[i].y].x - P[L[i].x].x);
	sort(L, L + M, cmpxs);
	for (int i = 0; i < M; i++){
		Add(L[i].x, L[i].y);
		L[i].pos = pt;
		num[pt] = L[i].n;
	}
	for (int i = 0; i < M; i++)L[i].rev = L[i ^ 1].pos;
	for (int i = 0; i < M; i++)
		if (!vis[i]){
			++ tot;
			int x = i;
			LL area = 0;
			for (; !vis[x]; ){
				vis[x] = tot;
				area += xet(P[L[x].x], P[L[x].y]);
				if (ne[L[x].rev])
					x = ne[L[x].rev];
				else	x = st[L[x].y];
			}
			if (area < 0)
				bound[tot] = 1;
		}
	len = 0;
	for (int i = 0; i < M; i++)
		if (bound[vis[i]] && P[L[i].x].x != P[L[i].y].x){
			++len;
			q[len].temp = 1;
			q[len].s = P[L[i].x];
			q[len].t = P[L[i].y];
			if (q[len].s.x > q[len].t.x)
				swap(q[len].s, q[len].t);
			q[len].x = q[len].s.x;
			q[len].n = -i;
			
			++len;
			q[len].temp = 2;
			q[len].s = P[L[i].x];
			q[len].t = P[L[i].y];
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
	
	sort(q + 1, q + len + 1, cmpxt);
	root = 0;
	for (int i = 1; i <= len; i++)
		if (q[i].temp == 0)
			calc(q[i]);
		else if (q[i].temp == 1){
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
	
	return 0;
}

