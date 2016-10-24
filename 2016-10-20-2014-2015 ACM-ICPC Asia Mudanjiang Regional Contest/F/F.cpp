#include <bits/stdc++.h>
using namespace std;
#define LL long long

bool stt;

const int pp = (1e9) + 7;
int Test, N, pt, len, r, tot;
int st[60], ne[120], go[120], fa[60];
int q[200], head[60], tail[60], brol[200], bror[200];
int L[60], R[60], miu[50010], ff[50010], p[50010];
LL ans[60], f[60][50010], s[60][50010], res[50010];
LL resf[110][50010], resl[110][50010],resr[110][50010];

bool enn;

inline void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

inline void renew(int x, int y){
	for (int i = 1; i <= 50000; i++)
		res[i] = 0;
	for (int i = 1; i <= R[y]; i++)
		if (miu[i] && s[y][i]){
			int l = L[x] / i * i;
			if (l < L[x])l += i;
			for (int j = l; j <= R[x]; j += i)
				res[j] += s[y][i] * miu[i];
		}
	for (int i = L[x]; i <= R[x]; i++){
		res[i] = res[i] % pp;
		if (res[i] < 0)
			res[i] += pp;
		f[x][i] = f[x][i] * res[i] % pp;
	}
}

inline void renew_s(int x){
	for (int i = 1; i <= R[x]; i++)
		if (miu[i]){
			s[x][i] = 0;
			for (int j = i; j <= R[x]; j += i){
				s[x][i] = s[x][i] + f[x][j];
			}
		}
	for (int i = 1; i <= R[x]; i++)
		if (miu[i]){
			s[x][i] = s[x][i] % pp;
			if (s[x][i] < 0)
				s[x][i] += pp;
		}
}

void get_tree(int x){
	head[x] = r + 2;
	q[++r] = ++tot;
	for (int j = st[x]; j; j = ne[j])
		if (go[j] != fa[x]){
			fa[go[j]] = x;
			q[++r] = go[j];
		}
	q[++r] = q[head[x] - 1];
	tail[x] = r - 1;
	for (int j = head[x]; j <= tail[x]; j++){
		int y = q[j];
		get_tree(y);
		brol[y] = q[j - 1];
		bror[y] = q[j + 1];
	}
}

inline void dp(int x){
	memset(resl[x], 0, sizeof(resl[x]));
	memset(resr[x], 0, sizeof(resr[x]));
	for (int k = head[x]; k <= tail[x]; k++){
		int y = q[k];
		fa[y] = x;
		dp(y);
	}
	memset(f[x], 0, sizeof(f[x]));
	for (int i = L[x]; i <= R[x]; i++)f[x][i] = 1;
	int y = q[head[x] - 1];
	for (int i = 1; i <= 50000; i++)
		resl[y][i] = resr[y][i] = f[x][i];
	for (int k = head[x]; k <= tail[x]; k++){
		int y = q[k];
		renew(x, y);
		for (int j = 1; j <= 50000; j++)
			resl[y][j] = f[x][j];
	}
	memset(f[x], 0, sizeof(f[x]));
	for (int i = L[x]; i <= R[x]; i++)f[x][i] = 1;
	for (int k = tail[x]; k >= head[x]; k--){
		int y = q[k];
		renew(x, y);
		for (int j = 1; j <= 50000; j++)
			resr[y][j] = f[x][j];
	}
	renew_s(x);
}

inline void dfs(int x){
	ans[x] = 0;
	for (int i = L[x]; i <= R[x]; i++)
		ans[x] = (ans[x] + f[x][i] * i % pp) % pp;
	for (int k = head[x]; k <= tail[x]; k++){
		int y = q[k];
		for (int i = L[x]; i <= R[x]; i++)
			f[x][i] = resl[brol[y]][i] * resr[bror[y]][i] % pp * resf[x][i] % pp;
		renew_s(x);
		renew(y, x);
		for (int i = L[y]; i <= R[y]; i++)
			resf[y][i] = res[i];
		renew_s(y);
		dfs(y);
		for (int i = L[y]; i <= R[y]; i++)
			f[y][i] = resr[q[head[y]]][i];
		for (int i = L[x]; i <= R[x]; i++)
			f[x][i] = resr[q[head[x]]][i];
	}
}

int main(){
	freopen("F.in", "r", stdin);
	freopen("F.out", "w", stdout);
	miu[1] = 1;
	for (int i = 2; i <= 50000; i++){
		if (!ff[i]){
			ff[i] = i;
			p[++len] = i;
			miu[i] = -1;
		}
		for (int j = 1; j <= len && p[j] <= ff[i] && p[j] * i <= 50000; j++){
			ff[p[j] * i] = p[j];
			if (p[j] == ff[i])miu[p[j] * i] = 0;
			else miu[p[j] * i] = -miu[i];
		}
	}
	scanf("%d", &Test);
	while (Test--){
		scanf("%d", &N);
		memset(st, 0, sizeof(st));
		memset(fa, 0, sizeof(fa));
		tot = N;
		pt = 0;
		for (int i = 1; i <= N; i++)scanf("%d", &L[i]);
		for (int i = 1; i <= N; i++)scanf("%d", &R[i]);
		for (int i = 1; i < N; i++){
			int x, y;
			scanf("%d%d", &x, &y);
			Add(x, y);
			Add(y, x);
		}
		r = 0;
		get_tree(1);
		dp(1);
		for (int i = 1; i <= 50000; i++)
			resf[1][i] = 0;
		for (int i = L[1]; i <= R[1]; i++)
			resf[1][i] = 1;
		dfs(1);
		for (int i = 1; i <= N; i++){
			cout << ans[i];
			if (i < N)printf(" ");
			else printf("\n");
		}
	}
	return 0;
}