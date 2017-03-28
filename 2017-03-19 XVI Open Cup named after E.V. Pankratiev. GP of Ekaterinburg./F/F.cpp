#include <bits/stdc++.h>
using namespace std;

int N, M, len, pt, tot, num, last, l, r;
bool ans[310][310];
int q[310], C[310][310], D[310][310];
int dfn[310], low[310], sta[310], vis[310], cc[310], mark[310], in[310];
int st[310], ne[90010], go[90010];

class rec{
	public:
	int x, y;
}L[90010];

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

void tarjan(int x){
	dfn[x] = low[x] = ++tot;
	sta[++last] = x;
	vis[x] = 1;
	for (int i = st[x]; i; i = ne[i])
		if (vis[go[i]] == 0){
			tarjan(go[i]);
			low[x] = min(low[x], low[go[i]]);
		}
		else if (vis[go[i]] == 1) low[x] = min(low[x], dfn[go[i]]);
	if (dfn[x] == low[x]){
		++num;
		int p;
		do {
			p = sta[last];
			mark[p] = num;
			vis[p] = 2;
			sta[last--] = 0;
		} while (p != x);
	}
}

int main() {
//	freopen("F.in","r",stdin);
//	freopen("F.out","w",stdout);
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= M; i++){
		scanf("%d%d", &L[i].x, &L[i].y);
		Add(L[i].x, L[i].y);
	}
	for (int i = 1; i <= N; i++)
		if (!vis[i])
			tarjan(i);
	for (int i = 1; i <= N; i++) cc[i] = 0;
	for (int i = 1; i <= N; i++)
		if (!cc[i]){
			r = 0;
			for (int j = i; j <= N; j++)
				if (mark[i] == mark[j]){
					cc[j] = i;
					q[++r] = j;
				}
			if (r > 1)
				for (int j = 1; j <= r; j++)
					ans[q[j]][q[j % r + 1]] = 1;
		}
	for (int i = 1; i <= M; i++)
		if (cc[L[i].x] != cc[L[i].y])
			C[cc[L[i].x]][cc[L[i].y]] = 1;
	for (int k = 1; k <= N; k++)
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				if (C[i][k] && C[k][j])
					D[i][j] = 1;
	for (int k = 1; k <= N; k++)
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				if (D[i][k] && C[k][j])
					D[i][j] = 1;
	for (int k = 1; k <= N; k++)
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				if (D[i][k] && D[k][j])
					D[i][j] = 1;
	for (int i = 1; i <= M; i++)
		if (cc[L[i].x] != cc[L[i].y] && D[cc[L[i].x]][cc[L[i].y]] == 0)
			ans[cc[L[i].x]][cc[L[i].y]] = 1;
	len = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			len += ans[i][j];
	printf("%d %d\n", N, len);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			if (ans[i][j])
				printf("%d %d\n", i, j);
	return 0;
}
