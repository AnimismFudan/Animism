#include <bits/stdc++.h>
#define maxn 201000
#define lowbit(a) ((a) & (-(a)))
using namespace std;

struct NODE {
	int nex[27];
	int a, b, f, ml;
};

struct Per {
	int a, b, len;
};

struct str { int v, nex; };

void getmin(int &a, int b) {
	if (a > b) a = b;
}

bool cmp(const Per &a, const Per &b) {
	return (a.a < b.a);
}

struct SAM {
	char A[maxn], B[maxn];
	int n, m, tot, head, tail, e;
	NODE node[maxn * 2 * 2];
	int fst[maxn << 2];
	Per per[maxn << 2];
	str edge[maxn << 2];
	
	void make_edge(int a, int b) {
		edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b;
	}

	void dfs(int u) {
		for (int i = fst[u]; i; i = edge[i].nex) {
			int v = edge[i].v;
			dfs(v);
			getmin(node[u].a, node[v].a);
			getmin(node[u].b, node[v].b);
		}
	}

	void add(int ch, int len) {
		int p = tail, np = ++tot;
		node[np].ml = len;
		for (; p && !node[p].nex[ch]; p = node[p].f) node[p].nex[ch] = np;
		tail = np;
		if (!p) node[np].f = head;
		else {
			if (node[node[p].nex[ch]].ml == node[p].ml + 1) 
				node[np].f = node[p].nex[ch];
			else {
				int q = node[p].nex[ch], just = ++tot;
				node[just] = node[q];
				node[just].ml = node[p].ml + 1;
				node[q].f = node[np].f = just;
				for (; p && node[p].nex[ch] == q; p = node[p].f)
					node[p].nex[ch] = just;
			}
		}
		return;
	}
	
	void proc() {
		head = tail = ++tot;
		int u = head;
		for (int i = 1; i <= n; i++) {
			add(A[i] - 'a', i);
		}
		add(26, n + 1);
		for (int i = 1; i <= m; i++) {
			add(B[i] - 'a', i + n + 1);
		}

		u = head;
		for (int i = 1; i <= tot; i++) {
			node[i].a = n + 1;
			node[i].b = m + 1;
		}
		node[1].a = node[1].b = 0;
		for (int i = 1; i <= n; i++) {
			u = node[u].nex[A[i] - 'a'];
			getmin(node[u].a, i);			
		}
		u = head;
		for (int i = 1; i <= m; i++) {
			u = node[u].nex[B[i] - 'a'];
			getmin(node[u].b, i);
		}
		for (int i = 2; i <= tot; i++) {
			make_edge(node[i].f, i);
		}
		dfs(head);		
		for (int u = 1; u <= tot; u++) {
			per[u] = (Per) { node[u].a, node[u].b, node[u].ml };
		}
		return;
	}
} saml, samr;

int n, m, ansl, ansr, ans;
char A[maxn], B[maxn];
int st[maxn << 2], ts[maxn << 2];

void solve() {
	for (int i = 1; i <= samr.tot; i++) {
		samr.per[i].a = n - samr.per[i].a + 1;
		samr.per[i].b = m - samr.per[i].b + 1;
	}
	sort(saml.per + 1, saml.per + saml.tot + 1, cmp);
	sort(samr.per + 1, samr.per + samr.tot + 1, cmp);

	int v = 1;
	ans = -1;
	for (int i = 0; i <= m + 1; i++) st[i] = -(1 << 29);
	for (int u = 1; u <= samr.tot; u++) {
		for (; v <= saml.tot && saml.per[v].a < samr.per[u].a; v++) {
			for (int k = saml.per[v].b + 1; k <= m + 1; k += lowbit(k)) {
				if (st[k] <= saml.per[v].len) ts[k] = v;
				st[k] = max(st[k], saml.per[v].len);				
			}
		}		
		for (int k = samr.per[u].b; k; k -= lowbit(k)) {
			if (st[k] + samr.per[u].len > ans) {
				ans = st[k] + samr.per[u].len;
				ansl = ts[k];
				ansr = u;
			}
		}
	}
	
	//printf("%d\n",ans);
	for (int i = saml.per[ansl].a - saml.per[ansl].len + 1; i <= saml.per[ansl].a; i++)
		putchar(A[i]);
	putchar('\n');
	for (int i = samr.per[ansr].a; i <= samr.per[ansr].a + samr.per[ansr].len - 1; i++)
		putchar(A[i]);
	putchar('\n');
}

int main() {
	//freopen("D.in","r",stdin);
	//freopen("D.out","w",stdout);
	scanf("%s\n%s",A + 1, B + 1);
	n = strlen(A + 1);
	m = strlen(B + 1);
	for (int i = 1; i <= n; i++) saml.A[i] = samr.A[i] = A[i];
	for (int i = 1; i <= m; i++) saml.B[i] = samr.B[i] = B[i];
	reverse(samr.A + 1, samr.A + n + 1);
	reverse(samr.B + 1, samr.B + m + 1);
	saml.n = samr.n = n;
	saml.m = samr.m = m;
	saml.proc();
	samr.proc();
	solve();
	return 0;
}
