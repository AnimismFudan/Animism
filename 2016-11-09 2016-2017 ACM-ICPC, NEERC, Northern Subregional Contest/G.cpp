#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, Q, pt, len;
char s[110];
int st[100010], ne[100010], go[100010], fa[100010], dep[100010], son[100010];
int dfn[200010], in[100010], out[100010], ST[18][200010];
int ls[100010];
int col[100010], last[100010], Head[100010];

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

class que{
	public:
	int ans_pipe, ans_s;
	int v, pre, l, r;
	char c;
}q[100010], Mark[100010];

class segleaf{
	public:
	int lca, s;
	int mark_lca, mark_s;
}seg[400010];

void dfs(int x, int c){
	col[x] = c;
	son[x] = !st[x];
	dfn[++len] = x;
	in[x] = len;
	for (int i = st[x]; i; i = ne[i]){
		dep[go[i]] = dep[x] + 1;
		dfs(go[i], c ? c : go[i]);
		son[x] += son[go[i]];
	}
	dfn[++len] = x;
	out[x] = len;
}

int find_ls(int x){
	return lower_bound(ls + 1, ls + len + 1, x) - ls;
}

void get_Twice(){
	for (int i = 1; i <= len; i++)
		ST[0][i] = dfn[i];
	for (int i = 1, s = 1; i <= 17; i++, s <<= 1)
		for (int j = 1; j <= len; j++){
			ST[i][j] = ST[i - 1][j];
			if (j + s <= len && dep[ST[i][j]] > dep[ST[i - 1][j + s]])
				ST[i][j] = ST[i - 1][j + s];
		}
}

int get_lca(int x, int y){
	if (x == y)return x;
	if (in[x] > in[y])swap(x, y);
	if (out[x] > out[y])return x;
	int l = in[x];
	int r = in[y];
	int t = log(r - l + 1) / log(2);
	int s = 1 << t;
	int t1 = ST[t][l];
	int t2 = ST[t][r - s + 1];
	if (dep[t1] > dep[t2])t1 = t2;
	return fa[t1];
}

void get_Push(int x, int l, int r, int v, int s){
	if (seg[x].lca){
		seg[x].lca = get_lca(seg[x].lca, v);
		seg[x].s += s;
	}else{
		seg[x].lca = v;
		seg[x].s = s;
	}
	if (seg[x].mark_lca){
		seg[x].mark_lca = get_lca(seg[x].mark_lca, v);
		seg[x].mark_s = seg[x].mark_s + s;
	}else{
		seg[x].mark_lca = v;
		seg[x].mark_s = s;
	}
}

void mark_down(int x, int l, int r){
	if (l == r){
		seg[x].mark_s = 0;
		seg[x].mark_lca = 0;
	}
	int mid = (l + r) >> 1;
	if (seg[x].mark_s){
		get_Push(x << 1, l, mid, seg[x].mark_lca, seg[x].mark_s);
		get_Push((x << 1) + 1, mid + 1, r, seg[x].mark_lca, seg[x].mark_s);
		seg[x].mark_s = 0;
		seg[x].mark_lca = 0;
	}
}

void Push_x(int x, int l, int r, int ll, int rr, int v){
	mark_down(x, l, r);
	if (l == ll && r == rr){
		get_Push(x, l, r, v, 1);
		return;
	}
	int mid = (l + r) >> 1;
	if (rr <= mid)Push_x(x << 1, l, mid, ll, rr, v);
	else if (ll > mid) Push_x((x << 1) + 1, mid + 1, r, ll, rr, v);
	else Push_x(x << 1, l, mid, ll, mid, v), Push_x((x << 1) + 1, mid + 1, r, mid + 1, rr, v);
}

void Push_all(int x, int l, int r){
	mark_down(x, l, r);
	if (l < r){
		int mid = (l + r) >> 1;
		Push_all(x << 1, l, mid);
		Push_all((x << 1) + 1, mid + 1, r);
	}else if (seg[x].lca){
		Mark[ls[l]].ans_pipe ++;
		Mark[ls[l]].ans_s += son[seg[x].lca] - seg[x].s;
		Mark[ls[l + 1]].ans_pipe --;
		Mark[ls[l + 1]].ans_s -= son[seg[x].lca] - seg[x].s;
	}
}

void build(int x, int l, int r){
	seg[x].lca = seg[x].s = seg[x].mark_lca = seg[x].mark_s = 0;
	if (l < r){
		int mid = (l + r) >> 1;
		build(x << 1, l, mid);
		build((x << 1) + 1, mid + 1, r);
	}
}

void work(int top){
	len = 0;
	for (int x = Head[top]; x; x = q[x].pre)
		if (q[x].c == '+'){
			ls[++len] = q[x].l;
			ls[++len] = q[x].r;
		}
	ls[++len] = Q + 1;
	sort(ls + 1, ls + len + 1);
	len = unique(ls + 1, ls + len + 1) - ls - 1;
	build(1, 1, len);
	for (int x = Head[top]; x; x = q[x].pre)
		if (q[x].c == '+')
			Push_x(1, 1, len, find_ls(q[x].l), find_ls(q[x].r) - 1, q[x].v);
	Push_all(1, 1, len);
}

int main(){
	freopen("gangsters.in", "r", stdin);
	freopen("gangsters.out", "w", stdout);
	scanf("%d%d", &N, &Q);
	for (int i = 2; i <= N; i++){
		scanf("%d", &fa[i]);
		Add(fa[i], i);
	}
	dep[1] = 1;
	dfs(1, 0);
	get_Twice();
	for (int i = 1; i <= Q; i++){
		scanf("%s%d", s, &q[i].v);
		q[i].c = s[0];
		q[i].pre = Head[col[q[i].v]];
		Head[col[q[i].v]] = i;
		if (q[i].c == '-'){
			int p = last[q[i].v];
			q[p].l = p;
			q[p].r = i;
			last[q[i].v] = 0;
		}else
			last[q[i].v] = i;
	}
	for (int i = 1; i <= Q; i++)
		if (q[i].c == '+' && !q[i].r){
			q[i].l = i;
			q[i].r = Q + 1;
		}
	for (int i = st[1]; i; i = ne[i])
		work(go[i]);
	for (int i = 1; i <= Q; i++){
		q[i].ans_pipe = q[i - 1].ans_pipe + Mark[i].ans_pipe;
		q[i].ans_s = q[i - 1].ans_s + Mark[i].ans_s;
	}
	for (int i = 1; i <= Q; i++)
		printf("%d %d\n", q[i].ans_pipe, q[i].ans_s);
	return 0;
}

