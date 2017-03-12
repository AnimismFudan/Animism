#include <bits/stdc++.h>
#define intl long long
using namespace std;

bool SS;
struct node {
    int f,nex[27];
    int ml,p,num;
    intl st;

    void init() {
	memset(nex,0,sizeof(nex));
	f = 0;
	ml = p = st = 0;
    }
    
} pool[1310000];
int head,tail;

struct str { int v,nex; } edge[1310000];

int n,m,e,len,tot;
char S[610000],s[610100];
int fst[1310000],pas[610000];
int ans,que[1310000];

map<intl,int> mp;

bool TT;

void init() {
    mp.clear();
    tot = 0; e = 0;
    head = tail = ++tot;
    pool[tot].num = tot;
    pool[tot].init();
    len = 0; ans = 0;
}

void make_edge(int a,int b) {
    edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b;
}

void add(int ch, int len, int k) {
    int p = tail, np = ++tot;
    pool[tot].init(); pool[tot].num = tot;
    pool[np].ml = pool[np].p = len;
    if (k != -1)
	pool[np].st = (1LL << k);
    else
	pool[np].st = 0;
    for (; p && !pool[p].nex[ch]; p = pool[p].f) pool[p].nex[ch] = np;
    tail = np;
    if (!p) 
	pool[np].f = head;
    else {
	if (pool[pool[p].nex[ch]].ml == pool[p].ml + 1) {
	    pool[np].f = pool[p].nex[ch];
	}
	else {
	    int q = pool[p].nex[ch], just = ++tot; 
	    pool[tot].init();
	    pool[just] = pool[q];
	    pool[tot].num = tot;
	    pool[q].f = pool[np].f = just;
	    pool[just].ml = pool[p].ml + 1;
	    for (; p && pool[p].nex[ch] == q; p = pool[p].f)
		pool[p].nex[ch] = just;
	}
    }
}

void Add(intl st) {
    if (!mp[st]) {
	mp[st] = 1;
	ans++;
    }
}

void dfs() {
    int L = 0, R = 0;
    que[++R] = 1;
    while (L < R) {
	int u = que[++L];
	for (int i = fst[u]; i; i = edge[i].nex) {
	    int v = edge[i].v;
	    que[++R] = v;
	}
    }
    for (int t = R; t; t--) {
	int u = que[t];
	for (int i = fst[u]; i; i = edge[i].nex) {
	    int v = edge[i].v;
	    pool[u].st |= pool[v].st;
	}
	if (u == 1) continue;
	if (pas[pool[u].p] <= pool[u].p - (pool[pool[u].f].ml + 1))
	    Add(pool[u].st);
    }
}

int main() {
    freopen("F.in","r",stdin);
    freopen("F.out","w",stdout);
    while (scanf("%d",&n) != EOF && n) {
	init();
	for (int i = 0; i < n; i++) {
	    scanf("%s",s + 1);
	    int N = strlen(s + 1);
	    for (int j = 1; j <= N; j++) {
		add(s[j] - 'a', ++len, i);
		S[len] = s[j];
	    }
	    S[++len] = 'z' + 1;
	    add(26, len, -1);
	}

	for (int i = 1; i <= len; i++) {
	    pas[i] = S[i] == ('z' + 1) ? i : pas[i - 1];
	}

	for (int i = 1; i <= tot; i++) fst[i] = 0;
	for (int i = 1; i <= tot; i++) {
	    if (pool[i].f != 0)
		make_edge(pool[pool[i].f].num, i);
	}

	dfs();
	cout << ans << endl;
    }
    return 0;
}
