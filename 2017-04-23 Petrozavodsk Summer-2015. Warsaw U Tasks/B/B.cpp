#include <bits/stdc++.h>
#define intl long long
#define maxn 1010000
#define midl ((L + R) >> 1)
#define midr (midl + 1)
#define lk (u << 1)
#define rk (u << 1 | 1)
using namespace std;

int val[maxn], A[maxn];
vector<int> p[maxn];
intl Max[maxn << 2], mark[maxn << 2];
intl ans;
int n, m, top;

struct PER {
	int x1, x2, y1, y2, val;
} per[maxn * 2];

bool cmp(const PER &a, const PER &b) {
	return (a.x1 < b.x1);
}

struct pmc {
	bool operator () (int a, int b) {
		return (per[a].x2 < per[b].x2 || (per[a].x2 == per[b].x2 && a < b));
	}
};

set<int,pmc> st;

void down(int u, int L, int R) {
	if (!mark[u]) return;
	Max[u] += mark[u];
	if (L < R) {
		mark[lk] += mark[u];
		mark[rk] += mark[u];
	}
	mark[u] = 0;
}

void add(int u, int L, int R, int l, int r, intl val) {
	down(u, L, R);
	if (L == l && R == r) {
		mark[u] += val;
		down(u, L, R);
		return;
	}
	if (r < midr) { down(rk, midr, R); add(lk, L, midl, l, r, val); }
	else if (l > midl) { down(lk, L, midl); add(rk, midr, R, l, r, val); }
	else {
		add(lk, L, midl, l, midl, val);
		add(rk, midr, R, midr, r, val);
	}
	Max[u] = max(Max[lk], Max[rk]);
	return;
}

int main() {
	//freopen("B.in","r",stdin);
	//freopen("B.out","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++) {
		scanf("%d",&A[i]);
		p[A[i]].push_back(i);
	}
	for (int i = 1; i <= m; i++)
		scanf("%d",&val[i]);
	for (int i = 1; i <= m; i++) {
		if (p[i].empty()) continue;
		int pas = 1;
		for (int j = 0; j < (int) p[i].size(); j++) {
			if (j < (int) (p[i].size() - 1))
				per[++top] = (PER) { pas, p[i][j], p[i][j], p[i][j + 1] - 1, val[i] };
			else
				per[++top] = (PER) { pas, p[i][j], p[i][j], n, val[i] };
			pas = p[i][j] + 1;
		}
	}
	sort(per + 1, per + top + 1, cmp);
	int q = 1;
	for (int x = 1; x <= n; x++) {
		for (; q <= top && per[q].x1 <= x; q++) {
			st.insert(q);
			add(1, 1, n, per[q].y1, per[q].y2, per[q].val);
		}
		while (!st.empty() && per[*st.begin()].x2 < x) {
			int u = *st.begin();
			st.erase(st.begin());
			add(1, 1, n, per[u].y1, per[u].y2, -per[u].val);
		}
		ans = max(ans, Max[1]);
	}
	cout << ans << endl;
	return 0;
}
