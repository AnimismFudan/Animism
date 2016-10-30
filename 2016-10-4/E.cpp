#include <bits/stdc++.h>
using namespace std;

#define LL long long

int Test, N, pt, SUM, l, r, len, last;
int ans, ansx, ansy, res, resx, resy;
int sta[100010], cir[200010], b[200010];
int S[100010], L[100010][2], W[100010], AL[100010][2], AW[100010][2];
int st[100010], ne[200010], go[200010], fa[100010];
bool in_sta[100010], vis[200010];

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

void dfs(int x){
	sta[++last] = x;
	in_sta[x] = 1;
	for (int i = st[x]; i; i = ne[i])
		if (!vis[i]){
			vis[i] = vis[i ^ 1] = 1;
			int y = go[i];
			if (in_sta[y]){
				int j = last + 1;
				do{
					j--;
					cir[++len] = sta[j];
				}while (sta[j] != y);
			}else
				dfs(go[i]);
		}
	in_sta[x] = 0;
	sta[last--] = 0;
}

void Renew(int &ans, int &ansx, int &ansy, int res, int resx, int resy, bool flag){
	if (resx > resy) swap(resx, resy);
	if ((flag && res < ans) || (!flag && res > ans)){
		ans = res;
		ansx = resx;
		ansy = resy;
	}else if (res == ans)
		if (ansx > resx || (ansx == resx && ansy > resy)){
			ansx = resx;
			ansy = resy;
		}
}

void dp(int x){
	L[x][0] = L[x][1] = 0;
	AL[x][0] = AL[x][1] = x;
	S[x] = 1;
	W[x] = 0;
	AW[x][0] = AW[x][1] = x;
	for (int i = st[x]; i; i = ne[i])
		if (!vis[i] && fa[x] != go[i]){
			int y = go[i];
			fa[y] = x;
			dp(y);
			S[x] += S[y];
			Renew(W[x], AW[x][0], AW[x][1], W[y], AW[y][0], AW[y][1], 0);
			if (L[x][0] < L[y][0] + 1 || (L[x][0] == L[y][0] + 1 && AL[x][0] > AL[y][0])){
				L[x][1] = L[x][0];
				AL[x][1] = AL[x][0];
				L[x][0] = L[y][0] + 1;
				AL[x][0] = AL[y][0];
			}else	if (L[x][1] < L[y][0] + 1 || (L[x][1] == L[y][0] + 1 && AL[x][1] > AL[y][0])){
				L[x][1] = L[y][0] + 1;
				AL[x][1] = AL[y][0];
			}
		}
	Renew(W[x], AW[x][0], AW[x][1], L[x][0] + L[x][1], AL[x][0], AL[x][1], 0);
}

void Push(int rr){
	while (r){
		bool flag = 0;
		flag |= (b[r] - L[cir[b[r]]][0] > rr - L[cir[rr]][0]);
		if (b[r] - L[cir[b[r]]][0] == rr - L[cir[rr]][0])
			flag |= AL[cir[b[r]]][0] > AL[cir[rr]][0];
		if (flag)b[r--] = 0;
		else break;
	}
	b[++r] = rr;
}

register char *_sp __asm__("rsp");

int main() {
	const int size = 64 * 1024 * 1024;
	static char *sys, *mine(new char[size] + size - 4096);
	sys = _sp;
	_sp = mine;
	
	freopen("E.in","r",stdin);
	freopen("E.out","w",stdout);
	scanf("%d", &Test);
	for (int tt = 1; tt <= Test; tt++){
		scanf("%d", &N);
		memset(st, 0, sizeof(st));
		memset(fa, 0, sizeof(fa));
		memset(cir, 0, sizeof(cir));
		memset(vis, 0, sizeof(vis));
		memset(in_sta, 0, sizeof(in_sta));
		pt = 1;
		for (int i = 1; i <= N; i++){
			int x, y;
			scanf("%d %d", &x, &y);
			Add(x, y);
			Add(y, x);
		}
		len = last = 0;
		dfs(1);
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= len; i++){
			int x = cir[i];
			int r = cir[i + 1];
			if (i == len)r = cir[1];
			for (int j = st[x]; j; j = ne[j])
				if (go[j] == r)
					vis[j] = vis[j ^ 1] = 1;
		}
		SUM = 0;
		for (int i = 1; i <= len; i++){
			dp(cir[i]);
			cir[i + len] = cir[i];
			SUM += 2 * S[cir[i]] - 2;
		}
		ans = 2e9;
		ansx = ansy = 0;
		for (int i = 1; i <= len; i++){
			res = len - W[cir[i]] + SUM;
			resx = AW[cir[i]][0];
			resy = AW[cir[i]][1];
			Renew(ans, ansx, ansy, res, resx, resy, 1);
		}
		l = 1;
		r = 0;
		for (int i = 1; i < len; i++)
			Push(i);
		for (int i = 1; i <= len; i++){
			int rr = i + len - 1;
			res = SUM + len - 1 - i + b[l] - L[cir[b[l]]][0] - L[cir[rr]][0];
			resx = AL[cir[b[l]]][0];
			resy = AL[cir[rr]][0];
			Renew(ans, ansx, ansy, res, resx, resy, 1);
			Push(rr);
			if (b[l] == i)
				b[l++] = 0;
		}
		printf("Case #%d: %d %d %d\n", tt, ans, ansx, ansy);
	}
	_sp = sys;
    return 0;
}
