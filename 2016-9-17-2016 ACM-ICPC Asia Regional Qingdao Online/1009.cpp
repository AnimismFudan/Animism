#include <bits/stdc++.h>
using namespace std;

#define LL long long

int Test, N, M, pt;
LL ans;
int L[100010][3], S[100010][3];
int st[100010], ne[200010], go[200010], w[200010], fa[100010];

void Add(int x, int y, int ww){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
	w[pt] = ww;
}

void renew_L2S(int x, int y, int ww){
	for (int j = 0; j < 3; j++)
		if (L[x][0] + L[x][1] > S[x][j]){
			for (int k = 2; k > j; k--)
				 S[x][k] = S[x][k - 1];
			S[x][j] = L[x][0] + L[x][1];
			break;
		}
}

void erase_L2S(int x, int y, int ww){
	for (int j = 0; j < 3; j++)
		if (L[x][0] + L[x][1] == S[x][j]){
			for (int k = j; k < 2; k++)
				 S[x][k] = S[x][k + 1];
			S[x][2] = 0;
			break;
		}
}

void renew(int x, int y, int ww){
	erase_L2S(x, y, ww);
	
	for (int j = 0; j < 3; j++)
		if (L[y][0] + ww > L[x][j]){
			for (int k = 2; k > j; k--)
				L[x][k] = L[x][k - 1];
			L[x][j] = L[y][0] + ww;
			break;
		}
	
	renew_L2S(x, y, ww);
	
	for (int j = 0; j < 3; j++)
		if (S[y][0] > S[x][j]){
			for (int k = 2; k > j; k--)
				S[x][k] = S[x][k - 1];
			S[x][j] = S[y][0];
			break;
		}
}

void erase(int x, int y, int ww){
	erase_L2S(x, y, ww);
	
	for (int j = 0; j < 3; j++)
		if (L[y][0] + ww == L[x][j]){
			for (int k = j; k < 2; k++)
				L[x][k] = L[x][k + 1];
			L[x][2] = 0;
			break;
		}
	
	renew_L2S(x, y, ww);
	
	for (int j = 0; j < 3; j++)
		if (S[x][j] == S[y][0]){
			for (int k = j; k < 2; k++)
				S[x][k] = S[x][k + 1];
			S[x][2] = 0;
			break;
		}
}

void dp(int x){
	memset(L[x], 0, sizeof(L[x]));
	memset(S[x], 0, sizeof(S[x]));
	for (int i = st[x]; i; i = ne[i])
		if (go[i] != fa[x]){
			int y = go[i];
			fa[y] = x;
			dp(y);
			renew(x, y, w[i]);
		}
}

void move_root(int x, int y, int ww, bool flag){
	int res = 0;
	res = max(res, S[y][0]);
	
	erase(x, y, ww);
	renew(y, x, ww);
	
	res = max(res, S[x][0]);
	
	if (flag)
		ans += res;
}

void dfs(int x){
	for (int i = st[x]; i; i = ne[i])
		if (go[i] != fa[x]){
			int y = go[i];
			move_root(x, y, w[i], 1);
			dfs(y);
			move_root(y, x, w[i], 0);
		}
}

register char *_sp __asm__("rsp");

int main() {
	const int size = 16*1024*1024;
	static char *sys, *mine(new char[size] + size - 4096);
	sys = _sp;
	_sp = mine;
	
	freopen("1009.in","r",stdin);
	freopen("1009.out","w",stdout);
	scanf("%d",&Test);
	while (Test--){
		scanf("%d", &N);
		pt = 0;
		for (int i = 1; i <= N; i++){
			st[i] = 0;
			fa[i] = 0;
		}
		for (int i = 1; i < N; i++){
			int x, y, ww;
			scanf("%d%d%d", &x, &y, &ww);
			Add(x, y, ww);
			Add(y, x, ww);
		}
		ans = 0;
		dp(1);
		dfs(1);
		cout << ans << endl;
	}
	
	_sp = sys;
	return 0;
}
