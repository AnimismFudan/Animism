#include <bits/stdc++.h>
using namespace std;

bool stt;

int Test, N, M, root;
int id[400010];

class poi{
	public:
	int x, y, c, t, n, ans;
	poi(){}
} P[400010];

bool cmpct(const poi &A, const poi &B){
	if (A.c != B.c) return A.c < B.c;
	return A.t < B.t;
}

bool cmpn(const poi &A, const poi &B){
	return A.n < B.n;
}

class kdleaf{
	public:
	int sx, tx, sy, ty, s;
	int Min_n;
	int l, r;
}kdt[400010];

bool enn;

bool cmpx(const int &x, const int &y){
	return P[x].x < P[y].x;
}

bool cmpy(const int &x, const int &y){
	return P[x].y < P[y].y;
}

void renew(int x, int y){
	if (!y)return;
	kdt[x].sx = min(kdt[x].sx, kdt[y].sx);
	kdt[x].sy = min(kdt[x].sy, kdt[y].sy);
	kdt[x].tx = max(kdt[x].tx, kdt[y].tx);
	kdt[x].ty = max(kdt[x].ty, kdt[y].ty);
	kdt[x].Min_n = min(kdt[x].Min_n, kdt[y].Min_n);
}

int kd_build(int l, int r, int step){
	if (l > r) return 0;
	int mid = (l + r) >> 1;
	nth_element(id + l, id + mid, id + r + 1, step ? cmpx : cmpy);
	int x = id[mid];
	kdt[x].sx = kdt[x].tx = P[x].x;
	kdt[x].sy = kdt[x].ty = P[x].y;
	kdt[x].s = 1;
	kdt[x].Min_n = P[x].n;
	kdt[x].l = kd_build(l, mid - 1, !step);
	renew(x, kdt[x].l);
	kdt[x].s += kdt[kdt[x].l].s;
	kdt[x].r = kd_build(mid + 1, r, !step);
	renew(x, kdt[x].r);
	kdt[x].s += kdt[kdt[x].r].s;
	return x;
}

int rebuild(int head, int step){
	int l, r, x;
	id[l = r = 1] = head;
	for (; l <= r; l++){
		x = id[l];
		if (kdt[x].l) id[++r] = kdt[x].l;
		if (kdt[x].r) id[++r] = kdt[x].r;
	}
	return kd_build(1, r, step);
}

void Insert(int &root, int x, int step){
	if (!root){
		root = x;
		kdt[root].sx = kdt[root].tx = P[x].x;
		kdt[root].sy = kdt[root].ty = P[x].y;
		kdt[root].s = 1;
		kdt[root].Min_n = P[x].n;
		kdt[root].l = kdt[root].r = 0;
		return;
	}
	if (step ? cmpx(x, root) : cmpy(x, root))
		Insert(kdt[root].l, x, !step);
	else Insert(kdt[root].r, x, !step);
	renew(root, x);
	kdt[root].s++;
	if (kdt[kdt[root].l].s > kdt[kdt[root].r].s * 2 + 1 || kdt[kdt[root].r].s > kdt[kdt[root].l].s * 2 + 1)
		root = rebuild(root, step);
}

double dist(poi a, poi b){
//	return abs(a.x - b.x) + abs(a.y - b.y);
	return sqrt(double(a.x - b.x) * (a.x - b.x) + double(a.y - b.y) * (a.y - b.y));
}

/*int Min_dist(poi p, kdleaf t){
	if (p.x < t.sx){
		if (p.y < t.sy)
			return abs(p.x - t.sx) + abs(p.y - t.sy);
		else if (p.y > t.ty)
			return abs(p.x - t.sx) + abs(p.y - t.ty);
		else return abs(p.x - t.sx);
	} else if (t.sx <= p.x && p.x <= t.tx){
		if (p.y < t.sy)
			return abs(p.y - t.sy);
		else if (p.y > t.ty)
			return abs(p.y - t.ty);
		else return 0;
	} else {
		if (p.y < t.sy)
			return abs(p.x - t.tx) + abs(p.y - t.sy);
		else if (p.y > t.ty)
			return abs(p.x - t.tx) + abs(p.y - t.ty);
		else return abs(p.x - t.tx);
	}
}*/

double Min_dist(poi p, kdleaf t){
	if (p.x < t.sx){
		if (p.y < t.sy)
			return sqrt(double(p.x - t.sx) * (p.x - t.sx) + double(p.y - t.sy) * (p.y - t.sy));
		else if (p.y > t.ty)
			return sqrt(double(p.x - t.sx) * (p.x - t.sx) + double(p.y - t.ty) * (p.y - t.ty));
		else return abs(p.x - t.sx);
	} else if (t.sx <= p.x && p.x <= t.tx){
		if (p.y < t.sy)
			return abs(p.y - t.sy);
		else if (p.y > t.ty)
			return abs(p.y - t.ty);
		else return 0;
	} else {
		if (p.y < t.sy)
			return sqrt(double(p.x - t.tx) * (p.x - t.tx) + double(p.y - t.sy) * (p.y - t.sy));
		else if (p.y > t.ty)
			return sqrt(double(p.x - t.tx) * (p.x - t.tx) + double(p.y - t.ty) * (p.y - t.ty));
		else return abs(p.x - t.tx);
	}
}

void ask_min(int root, int x, int step, int &ans){
	if (!root) return;
	if (!ans) ans = root;
	else{
		double d1 = dist(P[root], P[x]);
		double d2 = dist(P[ans], P[x]);
		if (d1 < d2 || (d1 == d2 && P[root].n < P[ans].n))
			ans = root;
	}
	double d2 = dist(P[ans], P[x]);
	double dd = Min_dist(P[x], kdt[root]);
	if (dd > d2 || (dd == d2 && kdt[root].Min_n > P[ans].n))
		return;
	if (step ? cmpx(x, root) : cmpy(x, root)){
		ask_min(kdt[root].l, x, !step, ans);
		ask_min(kdt[root].r, x, !step, ans);
	}else{
		ask_min(kdt[root].r, x, !step, ans);
		ask_min(kdt[root].l, x, !step, ans);
	}
	
}

register char *_sp __asm__("rsp");

int main() {
	const int size = 64 * 1024 * 1024;
	static char *sys, *mine(new char[size] + size - 4096);
	sys = _sp;
	_sp = mine;
	
	scanf("%d", &Test);
	for (int tt = 1; tt <= Test; tt++){
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= N; i++){
			scanf("%d%d%d", &P[i].x, &P[i].y, &P[i].c);
			P[i].t = 0;
			P[i].n = i;
		}
		for (int i = N + 1; i <= N + M; i++){
			scanf("%d%d%d", &P[i].x, &P[i].y, &P[i].c);
			P[i].t = 1;
			P[i].n = i;
		}
		sort(P + 1, P + N + M + 1, cmpct);
		root = 0;
		for (int i = 1; i <= N + M; i++){
			if (P[i].t == 0)
				Insert(root, i, 0);
			else{
				P[i].ans = 0;
				ask_min(root, i, 0, P[i].ans);
				P[i].ans = P[P[i].ans].n;
			}
		}
		sort(P + 1, P + N + M + 1, cmpn);
		for (int i = N + 1; i <= N + M; i++){
			int x = P[i].ans;
			printf("%d %d %d\n", P[x].x, P[x].y, P[x].c);
		}
	}
	
	_sp = sys;
	return 0;
}
