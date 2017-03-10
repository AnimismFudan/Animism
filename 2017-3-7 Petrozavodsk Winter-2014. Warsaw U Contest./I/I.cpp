#include <bits/stdc++.h>
using namespace std;

int N, ans, len, pt;
int st[500010], ne[1000010], go[1000010];
int A[500010], dep[500010], fa[500010];
int in[500010], out[500010], t[500010];
bool vis[500010];

class rec{
	public:
	int s;
}seg[5000010];

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

bool cmp(const int &x, const int &y){
	return A[x] + dep[x] > A[y] + dep[y];
}

void Init(int x, int l, int r, int t, int delta){
	seg[x].s += delta;
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (t <= mid) Init(x << 1, l, mid, t, delta);
	else Init((x << 1) + 1, mid + 1, r, t, delta);
}

int ask(int x, int l, int r, int ll, int rr){
	if (l == ll && r == rr) return seg[x].s;
	int mid = (l + r) >> 1;
	if (rr <= mid) return ask(x << 1, l, mid, ll, rr);
	else if (ll > mid) return ask((x << 1) + 1, mid + 1, r, ll, rr);
	else return ask(x << 1, l, mid, ll, mid) + ask((x << 1) + 1, mid + 1, r, mid + 1, rr);
}

void dfs(int x){
	in[x] = ++len;
	for (int i = st[x]; i; i = ne[i])
		if (go[i] != fa[x]){
			fa[go[i]] = x;
			dep[go[i]] = dep[x] + 1;
			dfs(go[i]);
		}
	out[x] = len;
}

void deal(int x){
	if (vis[x]) return;
	vis[x] = 1;
	Init(1, 1, N, in[x], -1);
	for (int i = st[x]; i; i = ne[i])
		if (go[i] != fa[x])
			deal(go[i]);
}

int main(){
//	freopen("I.in", "r", stdin);
//	freopen("I.out", "w", stdout);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &A[i]);
	for (int i = 1; i < N; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		Add(x, y);
		Add(y, x);
	}
	dep[1] = 1;
	dfs(1);
	for (int i = 1; i <= N; i++)
		Init(1, 1, N, i, 1);
	for (int i = 1; i <= N; i++) t[i] = i;
	sort(t + 1, t + N + 1, cmp);
	int l = 0;
	for (int i = 1; i <= N; i++){
		int x = t[i];
		if (vis[x]) continue;
		int s = ask(1, 1, N, in[x], out[x]);
		l += s;
		ans = max(ans, A[x] + dep[x] + l - 2);
		deal(x);
	}
	printf("%d", ans);
	return 0;
}

