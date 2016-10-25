#include <bits/stdc++.h>
using namespace std;
#define LL long long

const int pp = (1e9) + 7;
int Test, N, pt, len;
int st[60], ne[120], go[120], fa[60];
int ans[60], L[60], R[60], miu[50010], ff[50010], p[50010], res[50010];
int f[60][50010], f0[60][50010], s[60][50010];

inline void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

inline int quick(int x, int y){
	LL s = 1, t = x;
	for (; y; y >>= 1){
		if (y & 1) s = s * t % pp;
		t = t * t % pp;
	}
	return s;
}

inline void renew(int x, int y, int flag){
	for (int i = L[x]; i <= R[x]; i++)
		res[i] = 0;
	for (int i = 1; i <= R[y]; i++)
		if (miu[i] && s[y][i]){
			int l = L[x] / i * i;
			if (l < i)l += i;
			for (int j = l; j <= R[x]; j += i){
				res[j] += s[y][i] * miu[i];
				if (res[j] >= pp)res[j] -= pp;
				if (res[j] < 0)res[j] += pp;
			}
		}
	for (int i = L[x]; i <= R[x]; i++)
		if (res[i]){
			int t = res[i];
			if (flag)
				t = quick(t, pp - 2);
			f[x][i] = (LL)f[x][i] * t % pp;
		}else{
			if (!flag)f0[x][i]++;
			else f0[x][i]--;
		}
}

inline void renew_s(int x){
	for (int i = 1; i <= R[x]; i++)
		if (miu[i]){
			s[x][i] = 0;
			for (int j = i; j <= R[x]; j += i){
				if (!f0[x][j])
					s[x][i] = s[x][i] + f[x][j];
				if (s[x][i] >= pp)
					s[x][i] -= pp;
			}
		}
}

inline void dp(int x){
	for (int i = 1; i <= 50000; i++){
		f0[x][i] = 0;
		f[x][i] = 0;
	}
	for (int i = L[x]; i <= R[x]; i++)f[x][i] = 1;
	for (int k = st[x]; k; k = ne[k])
		if (go[k] != fa[x]){
			int y = go[k];
			fa[y] = x;
			dp(y);
			renew(x, y, 0);
		}
	renew_s(x);
}

inline void move_root(int x, int y){
	renew(x, y, 1);
	renew_s(x);
	renew(y, x, 0);
	renew_s(y);
}

inline void dfs(int x){
	ans[x] = 0;
	for (int i = L[x]; i <= R[x]; i++)
		ans[x] = (ans[x] + (LL)i * f[x][i] % pp) % pp;
	for (int k = st[x]; k; k = ne[k])
		if (go[k] != fa[x]){
			int y = go[k];
			move_root(x, y);
			dfs(y);
			move_root(y, x);
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
			else miu[p[j] * i] = -miu[ff[i]];
		}
	}
	scanf("%d", &Test);
	while (Test--){
		scanf("%d", &N);
		memset(st, 0, sizeof(st));
		memset(fa, 0, sizeof(fa));
		pt = 0;
		for (int i = 1; i <= N; i++)scanf("%d", &L[i]);
		for (int i = 1; i <= N; i++)scanf("%d", &R[i]);
		for (int i = 1; i < N; i++){
			int x, y;
			scanf("%d%d", &x, &y);
			Add(x, y);
			Add(y, x);
		}
		dp(1);
		dfs(1);
/*		for (int x = 1; x <= N; x++){
			memset(fa, 0, sizeof(fa));
			dp(x);
			ans[x] = 0;
			for (int i = L[x]; i <= R[x]; i++)
				ans[x] = (ans[x] + (LL)i * f[x][i] % pp) % pp;
		}*/
		for (int i = 1; i <= N; i++){
			printf("%d", ans[i]);
			if (i < N)printf(" ");
			else printf("\n");
		}
	}
	return 0;
}
