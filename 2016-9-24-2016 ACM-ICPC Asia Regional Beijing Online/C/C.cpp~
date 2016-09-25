#include <bits/stdc++.h>
#define maxn 101000
using namespace std;

int nex[maxn][27], ans[maxn], mark[maxn];
int fa[maxn],ch[maxn],fail[maxn];
int wp[maxn],sou[maxn],que[maxn];
int n,top,Ans,T;
string pas, now;
char s[maxn];

bool judge(char a) {
    return (a <= 'z' && a >= 'a');
}

int Add(int u,int v) {
    if (!nex[u][v]) {
	nex[u][v] = ++top;
	fa[top] = u;
	ch[top] = v;
    }
    return nex[u][v];
}

void add(string s) {
    int n = s.length();
    int u = 1;
    for (int i = 0; i < n; i++) {
	u = Add(u, wp[s[i]]);	
    }
    mark[u] = 1;
}

int trans(int u,int v) {
    if (!wp[v]) return 1;
    v = wp[v];
    for (; u != 1 && !nex[u][v]; u = fail[u]);
    if (nex[u][v]) u = nex[u][v];
    return u;
}

void dfs(int u) {
    if (mark[u] && ans[u] > ans[Ans]) {
	Ans = u;
    }
    for (int v = 0; v < 27; v++) {
	if (nex[u][v]) dfs(nex[u][v]); 
    }
}

void print(int u) {
    if (u == 1) return;
    if (u != 1) print(fa[u]);
    putchar(sou[ch[u]]);
}

void bfs() {
    int L = 0, R = 0;
    que[++R] = 1;
    fail[1] = 1; fa[1] = 1;
    while (L < R) {	
	int u = que[++L];
	int wp = fail[fa[u]];
	for (; wp != 1 && !nex[wp][ch[u]]; wp = fail[wp]);
	if (nex[wp][ch[u]] && nex[wp][ch[u]] != u) wp = nex[wp][ch[u]];
	fail[u] = wp;
	if (u == 1) fail[u] = u;
	for (int v = 0; v < 27; v++) {
	    if (!nex[u][v]) continue;
	    que[++R] = nex[u][v];
	}
    }
}

void init() {
    top = 1; n = 0; Ans = 0;
    memset(nex,0,sizeof(nex));
    memset(mark,0,sizeof(mark));
    memset(ans,0,sizeof(ans));  
}

int main() {
    freopen("C.in","r",stdin);
    freopen("C.out","w",stdout);
    for (int i = 'a'; i <= 'z'; i++) {
	wp[i] = i - 'a';
	sou[i - 'a'] = i;
    }
    wp[' '] = 26;
    sou[26] = ' ';
    while (true) {
	init();
	n = 0;
	do s[++n] = getchar(); while (s[n] != -1 && s[n] != '#');
	pas = ""; now = "";
	if (s[n] == -1) return 0;
	else {
	    char c;
	    do c = getchar(); while (c == '#');
	}
	for (int u = 1; u <= n; u++) {
	    if (s[u] == ' ') {		
		if (s[u - 1] != ' ') {
		    if (now.length() && pas.length()) {
			add(pas + " " + now);
		    }
		    pas = now;
		    now = "";
		}
	    } else if (!judge(s[u])) {
		if (now.length() && pas.length()) {
		    add(pas + " " + now);
		}
		now = pas = "";
	    } else now = now + s[u];
	}

	bfs();
	int u = 1;
	for (int i = 1; i <= n; i++) {
	    u = trans(u, s[i]);
	    ans[u]++;
	}

	for (int i = top; i >= 1; i--) {
	    if (fail[i]) ans[fail[i]] += ans[i];
	}

	dfs(1);

	print(Ans);

	putchar(':');
	printf("%d\n",ans[Ans]);
    }
    return 0;
}
