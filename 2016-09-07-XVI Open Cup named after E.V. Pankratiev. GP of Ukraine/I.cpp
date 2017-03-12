#include <bits/stdc++.h>
#define maxm 15000100
#define maxn 210000
#define midl ((L + R) >> 1)
#define midr (midl + 1)
#define lowbit(a) ((a) & (-(a)))
using namespace std;

bool ss;
struct node {
	node *f,*nex[27];
	int ml,num,rt;
	node() { ml= 0; }
} pool[201000],*tail,*head,*sing[maxn];

struct str { int v,nex; } edge[maxn];

int n,tot,top,q,e,T,tp;
int Lb[maxn],Rb[maxn],con[maxn],dot[maxn],st[maxn][21],fa[maxn],fst[maxn];
int sum[maxm],lk[maxm],rk[maxm];
int ans;
char s[maxn];

bool tt;

void make_edge(int a,int b) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b;
}

void add(int ch,int len) {
	node *p = tail, *np = &pool[++tot]; np -> num = tot;
	np -> ml = len;
	for (; p && !p -> nex[ch]; p = p -> f) p -> nex[ch] = np;
	tail = np;
	if (!p) np -> f = head;
	else {
		if (p -> nex[ch] -> ml == p -> ml + 1) np -> f = p -> nex[ch];
		else {
			node *q = p -> nex[ch], *just = &pool[++tot]; //just -> num = tot;
			*just = *q; just -> num = tot;
			just -> ml = p -> ml + 1;
			q -> f = np -> f = just;
			for (; p && p -> nex[ch] == q; p = p -> f) p -> nex[ch] = just;
		}
	}
}

int dfs(int u) {
	Lb[u] = Rb[u] = ++top;
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v;
		Rb[u] = dfs(v);
	}
	return Rb[u];
}

int jump(int u,int x) {
	int k = 20;
	for (; k >= 0 && !st[u][k]; k--);
	if (k < 0) return u;
	while (pool[u].f -> ml >= x) {
		for (;k >= 0 && pool[st[u][k]].ml < x; k--);
		if (k < 0) return u;
		u = st[u][k];
	}
	return u;
}

void add_seg(int u,int L,int R,int p,int k) {
	sum[u] += k;
	if (L == R) return;
	if (p < midr) {
		if (!lk[u]) lk[u] = ++top;
		add_seg(lk[u], L, midl, p, k);
	} else {
		if (!rk[u]) rk[u] = ++top;
		add_seg(rk[u], midr, R, p, k);
	}
	return;
}

int find(int u,int L,int R,int k) {
	if (L == R) return sum[u];
	if (!sum[u]) return 0;
	if (k < midr) return find(lk[u], L, midl, k);
	else return find(rk[u], midr, R, k);
}

void add_str(int u,int L,int R,int p,int k) {
	sum[u] += k;
	if (L == R) return;
	if (p < midr) {
		if (!lk[u]) lk[u] = ++top;
		add_str(lk[u], L, midl, p, k);
	} else {
		if (!rk[u]) rk[u] = ++top;
		add_str(rk[u], midr, R, p, k);
	}
	return;
}

void Add(int x,int p,int k) {
	int u = jump(sing[p] -> num, x);
	int san = find(pool[u].rt, pool[u].f -> ml + 1, pool[u].ml, x);
	if (k == 1  &&  san) return;
	if (k == -1 && !san) return;

	add_str(pool[u].rt, pool[u].f -> ml + 1, pool[u].ml, x, k);

	for (int i = Lb[u]; i <= tp; i += lowbit(i))
		add_seg(i, 1, n, x, k);
}

int query(int L,int R,int k) {
	int S = 0;
	for (int i = 1; i <= q; i++) S += sum[dot[i]] * con[i];
	if (S < k) return -1;
	if (L == R) return L;
	S = 0;
	for (int i = 1; i <= q; i++) S += sum[lk[dot[i]]] * con[i];
	if (S >= k) {
		for (int i = 1; i <= q; i++) dot[i] = lk[dot[i]];
		return query(L, midl, k);
	}
	else {
		for (int i = 1; i <= q; i++) dot[i] = rk[dot[i]];
		return query(midr, R, k - S);
	}
}

int lower(int u,int L,int R,int k) {
	if (k < L) return 0;
	if (L == R) return sum[u];
	if (k < midr) return lower(lk[u], L, midl, k);
	return sum[lk[u]] + lower(rk[u], midr, R, k);
}

int solve(int x,int p,int k) {
	int u = jump(sing[p] -> num, x);
	q = 0;
	for (int i = Rb[u]; i; i -= lowbit(i)) {
		dot[++q] = i;
		con[q] = 1;
	}
	
	for (int i = Lb[u] - 1; i; i -= lowbit(i)) {
		dot[++q] = i;
		con[q] = -1;
	}
	
	k += lower(pool[u].rt, pool[u].f -> ml + 1, pool[u].ml, x - 1);

	return query(1, n, k);
}

int main() {
	//freopen("I.in","r",stdin);
	//freopen("I.out","w",stdout);
	scanf("%s",s + 1);
	n = strlen(s + 1);
	head = tail = &pool[++tot];
	head -> num = tot;
	for (int i = 1; i <= n; i++) {
		add(s[i] - 'a', i);
		sing[i] = tail;
	}

	for (int i = 2; i <= tot; i++) {
		make_edge(pool[i].f -> num, pool[i].num);
		fa[pool[i].num] = st[pool[i].num][0] = pool[i].f -> num;
	}

	for (int j = 1; j <= 20; j++) {
		for (int i = 1; i <= tot; i++) {
			st[i][j] = st[st[i][j - 1]][j - 1];
		}
	}

	dfs(1); tp = top;

	for (int i = 1; i <= tot; i++) pool[i].rt = ++top;
	
	for (scanf("%d",&T); T; T--) {
		int t,x,p,k;
		scanf("%d %d %d",&t,&x,&p);
		p++;
		if (t == 1) Add(x,p,1);
		else if (t == 2) Add(x,p,-1);
		else {
			scanf("%d",&k);
			ans = solve(x,p,k);
			printf("%d\n",ans);
		}
	}
	
	return 0;
}
