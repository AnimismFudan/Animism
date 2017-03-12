#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, Q, pt;
int fa[18][100010], dep[100010], G[100010];
int st[100010], ne[200010], go[200010];

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

class rec{
	public:
	LL l, m, r, s;
	rec(){
		l = r = m = -2e18;
		s = 0;
	}
	void getdata(LL t){
		l = m = r = s = t;
	}
	void reverse(){
		swap(l, r);
	}
}t1, t2, S[18][100010];

rec operator + (const rec &A, const rec &B){
	rec C;
	C.m = max(A.m, B.m);
	C.m = max(C.m, A.r + B.l);
	C.l = max(A.l, A.s + B.l);
	C.r = max(B.r, A.r + B.s);
	C.s = A.s + B.s;
	return C;
}

void dfs(int x){
	for (int i = st[x]; i; i = ne[i])
		if (go[i] != fa[0][x]){
			fa[0][go[i]] = x;
			dep[go[i]] = dep[x] + 1;
			dfs(go[i]);
		}
}

void getTwice(){
	for (int i = 1; i <= N; i++)
		S[0][i].getdata(G[i]);
	for (int i = 1; i <= 17; i++)
		for (int j = 1; j <= N; j++){
			fa[i][j] = fa[i - 1][fa[i - 1][j]];
			S[i][j] = S[i - 1][j] + S[i - 1][fa[i - 1][j]];
		}
}

int getLca(int x, int y){
	if (dep[x] < dep[y])swap(x, y);
	for (int i = 17; i >= 0; i--)
		if (dep[x] - dep[y] >= (1 << i))
			x = fa[i][x];
	if (x == y)
		return x;
	for (int i = 17; i >= 0; i--)
		if (fa[i][x] != fa[i][y]){
			x = fa[i][x];
			y = fa[i][y];
		}
	return fa[0][x];
}

rec getRes(int x, int y){
	int l = dep[x] - dep[y];
	rec T;
	for (int i = 17; i >= 0; i--)
		if (l >= (1 << i)){
			T = T + S[i][x];
			x = fa[i][x];
			l -= 1 << i;
		}
	return T;
}

register char *_sp __asm__("rsp");

int main() {
	const int size = 64 * 1024 * 1024;
	static char *sys, *mine(new char[size] + size - 4096);
	sys = _sp;
	_sp = mine;
	
    scanf("%d", &N);
    for (int i = 1; i < N; i++){
    	int x, y;
    	scanf("%d%d", &x, &y);
    	Add(x, y);
    	Add(y, x);
    }
    for (int i = 1; i <= N; i++)
    	scanf("%d", &G[i]);
    dep[1] = 1;
    dfs(1);
    getTwice();
    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++){
    	int x, y;
    	scanf("%d%d", &x, &y);
    	int t = getLca(x, y);
    	t1 = getRes(x, t);
    	t2 = getRes(y, t);
    	t2.reverse();
    	t1 = t1 + S[0][t] + t2;
    	cout << t1.m << endl;
    }
    
    _sp = sys;
    return 0;
}
