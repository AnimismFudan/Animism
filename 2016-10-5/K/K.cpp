#include <bits/stdc++.h>
using namespace std;

#define LL long long

int Test, tot, pt, ans;
int root[2], st[4010], ne[4010], go[4010], size[4010], SL[4010], SR[4010];
char col[4010];
int dp[2010][2010], vis[2010][2010];
int R[2][2010], q[2][2010], b[2010];
int len[2];
char s[2][5010];
int mark[2][5010];

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

void KuoHaoPiPei(int n){
	int r = 0;
	for (int i = 0; i < len[n]; i++)
		if (s[n][i] == '(')b[++r] = i;
		else if (s[n][i] == ')'){
			mark[n][i] = b[r];
			mark[n][b[r]] = i;
			b[r--] = 0;
		}
}

void get_tree(int n, int &root, int l, int r){
	root = ++tot;
	size[root] = 1;
	l++;r--;
	col[tot] = s[n][l++];
	while (l <= r){
		int x;
		get_tree(n, x, l, mark[n][l]);
		size[root] += size[x];
		Add(root, x);
		l = mark[n][l] + 1;
	}
}

void get_bfs(int n){
	int l, r;
	q[n][l = 1] = root[n];
	q[n][r = 2] = 0;
	R[n][1] = R[n][2] = 2;
	for (; l <= r; l++){
		int x = q[n][l];
		if (!x)continue;
		SL[x] = r + 1;
		for (int i = st[x]; i; i = ne[i])
			q[n][++r] = go[i];
		q[n][++r] = 0;
		SR[x] = r;
		for (int i = SL[x]; i <= SR[x]; i++)
			R[n][i] = r;
	}
}

int work(int l0, int l1){
	if (vis[l0][l1] == Test)
		return dp[l0][l1];
	vis[l0][l1] = Test;
	dp[l0][l1] = 2e9;
	if (R[0][l0] == l0 && R[1][l1] == l1){
		dp[l0][l1] = 0;
		return 0;
	}
	if (l0 < R[0][l0])
		dp[l0][l1] = min(dp[l0][l1], work(l0 + 1, l1) + size[q[0][l0]]);
	if (l1 < R[1][l1])
		dp[l0][l1] = min(dp[l0][l1], work(l0, l1 + 1) + size[q[1][l1]]);
	if (l0 < R[0][l0] && l1 < R[1][l1]){
		int res = work(l0 + 1, l1 + 1);
		res = res + work(SL[q[0][l0]], SL[q[1][l1]]);
		int x = q[0][l0];
		int y = q[1][l1];
		if (col[x] != col[y])
			res++;
		dp[l0][l1] = min(dp[l0][l1], res);
	}
	return dp[l0][l1];
}

int main(){
	freopen("K.in", "r", stdin);
	freopen("K.out", "w", stdout);
	scanf("%d", &Test);
	memset(vis, 255, sizeof(vis));
	while (Test--){
		scanf("%s%s", s[0], s[1]);
		tot = 0;
		pt = 0;
		memset(st, 0, sizeof(st));
		len[0] = strlen(s[0]);
		len[1] = strlen(s[1]);
		KuoHaoPiPei(0);
		get_tree(0, root[0], 0, len[0] - 1);
		get_bfs(0);
		KuoHaoPiPei(1);
		get_tree(1, root[1], 0, len[1] - 1);
		get_bfs(1);
		ans = work(1, 1);
		printf("%d\n", ans);
	}
}
