#include <bits/stdc++.h>
#define maxn 3010000
using namespace std;

bool aa;
vector<int> VEC[maxn], sing[1001000], L[1001000], R[1001000];

struct str { int v, nex; } edge[maxn << 1];

int Tnum[1001000], Fnum[1001000];
int False[1001000], True[1001000], toson[1001000], tofa[1001000];
int st[maxn], done[maxn], fa[1001000];
int scc[maxn], fst[maxn], T[1001000], F[1001000], dfn[maxn], low[maxn];
int bg[1001000], len[1001000], nex[1001000][2];
bool okay[maxn];
int n, tot, top, cl, cnt, tp, e;
char s[1010000];

bool bb;

void make_edge(int a, int b) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b;
}

int trans(int u, int v) {
	if (!nex[u][v]) nex[u][v] = ++tot, fa[tot] = u;
	return nex[u][v];
}

void tarjan(int u) {
	dfn[u] = low[u] = ++cl;
	st[++tp] = u;
	okay[u] = 1;
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v;
		if (dfn[v]) {
			if (okay[v]) low[u] = min(dfn[u], dfn[v]); 
		} else {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
	}
	if (dfn[u] == low[u]) {
		cnt++;
		int v;
		do {
			v = st[tp--];
			VEC[cnt].push_back(v);
			scc[v] = cnt;
			okay[v] = 0;
		} while (v != u);
	}
	return;
}

int main() {
	freopen("binary.in","r",stdin);
	freopen("binary.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) {
		bg[i] = bg[i - 1] + len[i - 1] + 1;
		scanf("%s",s + bg[i]);
		len[i] = strlen(s + bg[i]);
	}

	tot = 1;
	for (int i = 1; i <= n; i++) {
		int u = 1;
		for (int j = bg[i]; j < bg[i] + len[i]; j++) {
			u = trans(u, (s[j] == '?') ? 0 : s[j] - '0');
		}
		T[i] = u;
		u = 1;
		for (int j = bg[i]; j < bg[i] + len[i]; j++) {
			u = trans(u, (s[j] == '?') ? 1 : s[j] - '0');
		}
		F[i] = u;
	}

	top = 0;

	for (int i = 1; i <= tot; i++) {
		tofa[i] = ++top;
		toson[i] = ++top;
	}

	for (int i = 1; i <= n; i++) {
		if (T[i] == F[i]) {
			True[i] = ++top; False[i] = ++top;
			make_edge(False[i], True[i]);
			sing[T[i]].push_back(False[i]);
			Tnum[i] = sing[T[i]].size() - 1;
		} else {
			True[i] = ++top; False[i] = ++top;
			sing[T[i]].push_back(False[i]);
			Tnum[i] = sing[T[i]].size() - 1;
			sing[F[i]].push_back(True[i]);
			Fnum[i] = sing[F[i]].size() - 1;		
		}
		//	inv[True[i]] = False[i]; inv[False[i]] = True[i];
	}

	for (int i = 1; i <= tot; i++) {
		tofa[i] = ++top; toson[i] = ++top;
		for (int j = 0; j < (int) sing[i].size(); j++) {
			L[i].push_back(++top);
			make_edge(top, sing[i][j]);
			R[i].push_back(++top);
			make_edge(top, sing[i][j]);
		}
		for (int j = 1; j < (int) sing[i].size(); j++)
			make_edge(L[i][j], L[i][j - 1]);
		for (int j = 0; j < (int) sing[i].size() - 1; j++)
			make_edge(R[i][j], R[i][j + 1]);
		if (sing[i].size()) {
			make_edge(L[i][0], tofa[i]);
			make_edge(R[i][sing[i].size() - 1], toson[i]);
		}
	}
	
	for (int i = 1; i <= tot; i++) {
		if (fa[i]) {
			if (sing[fa[i]].size()) make_edge(tofa[i], L[fa[i]][sing[fa[i]].size() - 1]);
			else make_edge(tofa[i], tofa[fa[i]]);
		}
		for (int j = 0; j < 2; j++) {
			int v;
			if (!(v = nex[i][j])) continue;
			if (sing[v].size()) make_edge(toson[i], R[v][0]);
			else make_edge(toson[i], toson[v]);
		}
	}

	for (int i = 1; i <= n; i++) {
		if (Tnum[i] != 0) make_edge(True[i], L[T[i]][Tnum[i] - 1]);
		else make_edge(True[i], tofa[T[i]]);
		if (Tnum[i] < (int) sing[T[i]].size() - 1) make_edge(True[i], R[T[i]][Tnum[i] + 1]);
		else make_edge(True[i], toson[T[i]]);

		if (Fnum[i] != 0) make_edge(False[i], L[F[i]][Fnum[i] - 1]);
		else make_edge(False[i], tofa[F[i]]);
		if (Fnum[i] < (int) sing[F[i]].size() - 1) make_edge(False[i], R[F[i]][Fnum[i] + 1]);
		else make_edge(False[i], toson[F[i]]);
	}
	
	tot = 0;
	for (int i = 1; i <= top; i++) {
		if (!dfn[i]) tarjan(i);
 	}

	for (int i = 1; i <= n; i++)
		if (scc[True[i]] == scc[False[i]]) {
			printf("NO");
			return 0;
		}

	//for (int i = 1; i <= cnt; i++) p[i] = i;
	
	/*for (int i = 1; i <= top; i++) {
		int u = i;
		bool flag = true;
		for (auto q = VEC[u].begin(); q != VEC[u].end(); q++) {
			int v = *q;
			//printf("%d\n",v);
			if (done[inv[v]]) flag = false;
			for (int j = fst[v]; j; j = edge[j].nex) {
				int k = edge[j].v;
				if (!done[k] && scc[k] != scc[v]) flag = false;
			}
		}

		for (auto q = VEC[u].begin(); q != VEC[u].end(); q++)
			done[*q] = flag;
			}*/

	printf("YES\n");

	for (int i = 1; i <= n; i++) {
		for (int j = bg[i]; j < bg[i] + len[i]; j++)
			putchar(s[j] == '?' ? ('0' + (scc[False[i]] < scc[True[i]])) : s[j]);			
		putchar('\n');
	}

	//	for (int i = 1; i <= top; i++)
	//	for (int j = fst[i]; j; j = edge[j].nex)
	//		printf("%d %d\n",i,edge[j].v);
	return 0;
}
