#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, M, pt, len, resp, resx;
LL res;
int st[100010], head[100010], ne[200010], go[200010], l[200010], w[200010];
LL dist[2][200010];
int qq[200010];
int prex[2][200010], prey[2][200010];
bool vis[200010];

class line{
	public:
	int x, y, l, w, t;
}L[200010];

class rec{
	public:
	int i;
	LL d;
}p, pp, q[200010];

void Add(int x, int y, int ll, int ww){
	ne[++pt] =st[x];
	st[x] = pt;
	go[pt] = y;
	l[pt] = ll;
	w[pt] = ww;
}

bool operator < (const rec &A, const rec &B){
	return A.d < B.d;
}

bool operator > (const rec &A, const rec &B){
	return A.d > B.d;
}

priority_queue <rec, vector<rec>, greater<rec> > Heap;

bool cmpLw(const line &A, const line &B){
	return A.w < B.w;
}

bool cmpw(const rec &A, const rec &B){
	return w[A.i] < w[B.i];
}

void doit(int tt){
	for (int i = 1; i <= N; i++)
		head[i] = st[i];
	for (int i = 2; i <= pt; i++){
		p.i = i;
		p.d = dist[tt][i];
		vis[i] = 0;
		Heap.push(p);
	}
	for (int step = 2; step <= pt; step++){
		p = Heap.top();
		Heap.pop();
		if (vis[p.i]) continue;
		vis[p.i] = 1;
		int x = go[p.i];
		for (; head[x]; head[x] = ne[head[x]]){
			int i = head[x];
			if (w[p.i] > w[i]) break;
			if (dist[tt][i] > dist[tt][p.i] + l[i]){
				dist[tt][i] = dist[tt][p.i] + l[i];
				prex[tt][i] = tt;
				prey[tt][i] = p.i;
				pp.i = i;
				pp.d = dist[tt][i];
				Heap.push(pp);
			}
		}
	}
}

int main(){
//	freopen("J.in", "r", stdin);
//	freopen("J.out", "w", stdout);
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= M; i++){
		scanf("%d%d%d%d", &L[i].x, &L[i].y, &L[i].l, &L[i].w);
		L[i].t = i;
	}
	sort(L + 1, L + M + 1, cmpLw);
	pt = 1;
	for (int i = 1; i <= M; i++){
		Add(L[i].x, L[i].y, L[i].l, L[i].w);
		Add(L[i].y, L[i].x, L[i].l, L[i].w);
	}
	for (int i = 2; i <= pt; i++){
		dist[0][i] = 2e18;
		prex[1][i] = 0;
		prey[1][i] = 0;
	}
	for (int i = st[1]; i; i = ne[i]){
		dist[0][i] = l[i];
	}
	doit(0);
	len = 0;
	for (int i = st[2]; i; i = ne[i]){
		++len;
		q[len].i = i ^ 1;
		q[len].d = dist[0][i ^ 1];
	}
	sort(q + 1, q + len + 1, cmpw);
	for (int i = 2; i <= pt; i++){
		dist[1][i] = 2e18;
		prex[1][i] = 0;
		prey[1][i] = 0;
	}
	res = 2e18;
	resp = 0;
	int j = 1;
	for (int i = 1; i <= len; i++){
		while (j <= len && w[q[j].i] <= w[q[i].i]){
			if (res > q[j].d){
				res = q[j].d;
				resp = q[j].i;
			}
			j++;
		}
		dist[1][q[i].i ^ 1] = res + l[q[i].i];
		prex[1][q[i].i ^ 1] = 0;
		prey[1][q[i].i ^ 1] = resp;
	}
	doit(1);
	res = 2e18;
	resx = 1;
	resp = 0;
	for (int i = st[1]; i; i = ne[i])
		if (res > dist[1][i ^ 1]){
			res = dist[1][i ^ 1];
			resp = i ^ 1;
		}
	cout << res << endl;
	len = 0;
	while (resp){
		qq[++len] = resp;
		int x = prex[resx][resp];
		int y = prey[resx][resp];
		resx = x;
		resp = y;
	}
	for (int i = len; i; i--){
		printf("%d", L[qq[i] / 2].t);
		if (i > 1) printf(" ");
	}
}
