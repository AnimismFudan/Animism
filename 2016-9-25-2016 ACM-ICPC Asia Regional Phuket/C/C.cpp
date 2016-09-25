#include <bits/stdc++.h>
#define maxn 201000
#define Vec vector<int>
#define INF ((1 << 30) - 10)
using namespace std;

typedef int arr32[maxn];
arr32 fst,sou,sing,du;
int top,tp,e,n,m,T,Q,t;
int d[510][510],mk[510];
deque<int> que;

struct str { int v,nex,len; } edge[maxn << 1];

void make_edge(int a,int b,int c) {
    edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b; edge[e].len = c;
    edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a; edge[e].len = c;
}

struct ST {
    Vec pos,anc;
    int len;
    int mark;

    int dis(int a, int b) {
	int d = abs(pos[a] - pos[b]);
	if (mark) d = min(d, len - d);
	return d;
    }

    void update() {
	len = mark = 0;
	pos.clear(); anc.clear();
	if (que.front() == que.back()) {
	    mark = 1;
	} else mark = 0;
	int u = que.front();
	sing[u] = 0;
	sou[u] = top;
	anc.push_back(u);
	pos.push_back(0);
	int q = 0;
	while (!que.empty()) {
	    int u = que.front(); que.pop_front();
	    if (que.empty()) break;
	    int v = que.front();
	    int P = pos[q];
	    int K = INF;
	    for (int i = fst[u]; i; i = edge[i].nex)
		if (edge[i].v == v) K = min(K, edge[i].len);
	    P += K;
	    q++;
	    pos.push_back(P);
	    anc.push_back(v);
	    sing[v] = q;
	    sou[v] = top;
	}
	len = pos[(int)pos.size() - 1];
	return;
    }

    void proc() {
	int u = anc[0];
	int v = anc[(int)anc.size() - 1];
	if (du[u] < 3 || du[v] < 3) return;
	d[sou[u]][sou[v]] = min(d[sou[u]][sou[v]], len);
	d[sou[v]][sou[u]] = min(d[sou[v]][sou[u]], len);
    }

    int solve_in(int a, int b) {
	a = sing[a]; b = sing[b];
	int k = abs(pos[a] - pos[b]);
	if (mark) k = min(k, len - k);
	return k;
    }

    int solve_out(int a, int b) {
	int ans = INF;
	if (du[anc[0]] > 2) {
	    ans = min(ans, d[sou[anc[0]]][sou[b]] + pos[sing[a]]);
	}
	if (du[anc[(int)anc.size() - 1]] > 2) {
	    ans = min(ans, d[sou[anc[(int) anc.size() - 1]]][sou[b]] + len - pos[sing[a]]);	    
	}
	return ans;
    }
} proc[maxn];

int solve(int a,int b) {
    int A = sou[a], B = sou[b];
    int u,v;
    int ans = INF;
    if (du[(u = proc[A].anc[0])] > 2) {
	if (du[(v = proc[B].anc[0])] > 2)
	    ans = min(ans, d[sou[u]][sou[v]] + proc[A].pos[sing[a]] + proc[B].pos[sing[b]]);
	if (du[(v = proc[B].anc[(int) proc[B].anc.size() - 1])] > 2) {
	    ans = min(ans, d[sou[u]][sou[v]] + proc[A].pos[sing[a]] - proc[B].pos[sing[b]] + proc[B].len );
	}
    }
    if (du[(u = proc[A].anc[(int) proc[A].anc.size() - 1])] > 2) {
	if (du[(v = proc[B].anc[0])] > 2)
	    ans = min(ans, d[sou[u]][sou[v]] - proc[A].pos[sing[a]] + proc[A].len + proc[B].pos[sing[b]]);
	if (du[(v = proc[B].anc[(int) proc[B].anc.size() - 1])] > 2) {
	    ans = min(ans, d[sou[u]][sou[v]] - proc[A].pos[sing[a]] + proc[A].len - proc[B].pos[sing[b]] + proc[B].len);
	} 
    }
    return ans;
}

void dfs(int bg, int u,int pas,int mark) {
    if (!mark) que.push_back(u);  
    else que.push_front(u);
    if (du[u] > 2) return;
    for (int i = fst[u]; i; i = edge[i].nex) {
	int v = edge[i].v;
	if ((i ^ 1) == pas) continue;
	else if (du[v] > 2) {
	    if (!mark)
		que.push_back(v);
	    else
		que.push_front(v);
	    return;
	}
	else if (v == bg) {
	    if (!mark)		
		que.push_back(v);
	    else que.push_front(v);
	    return;
	}
	else {
	    dfs(bg, v, i, mark);
	    return;
	}
    }    
}

void init() {
    e = 1; top = tp = 0;
    for (int i = 1; i <= n; i++) fst[i] = du[i] = sou[i] = 0;   
}

int main() {
    freopen("C.in","r",stdin);
    freopen("C.out","w",stdout);
    for (scanf("%d",&T); T; T--) {
	scanf("%d %d %d",&n,&m,&Q);
	init();
	for (int i = 1; i <= m; i++) {
	    int a, b, c;
	    scanf("%d %d %d",&a,&b,&c);
	    du[a]++; du[b]++;
	    make_edge(a, b, c);
	}

	for (int i = 1; i <= n; i++) {
	    if (du[i] > 2) continue;
	    if (sou[i]) continue;
	    dfs(i, i, 0, 0);
	    if (du[i] == 2 && que.back() != i) {
		dfs(i, edge[edge[fst[i]].nex].v, edge[fst[i]].nex, 1);
	    }
	    top++;
	    proc[top].update();
	}

	for (int i = 1; i <= n; i++) {
	    if (du[i] > 2) mk[++tp] = i, sou[i] = tp;	    
	}

	for (int i = 1; i <= tp; i++)
	    for (int j = i + 1; j <= tp; j++)
		d[i][j] = d[j][i] = INF;
	for (int i = 1; i <= n; i++) {
	    if (du[i] < 3) continue;
	    for (int j = fst[i]; j; j = edge[j].nex) {
		int k = edge[j].v;
		if (du[k] <  3) continue;
		d[sou[i]][sou[k]] = min(d[sou[i]][sou[k]], edge[j].len);
	    }
	}
	
	for (int i = 1; i <= top; i++) proc[i].proc();

	printf("Case %d:\n",++t);
	for (; Q; Q--) {
	    int a,b;
	    scanf("%d %d",&a,&b);
	    if (du[a] < du[b]) swap(a, b);
	    if (du[a] > 2 && du[b] > 2)
		printf("%d\n",d[sou[a]][sou[b]]);
	    else if (du[a] > 2)
		printf("%d\n",proc[sou[b]].solve_out(b, a));
	    else if (sou[a] == sou[b])		
		printf("%d\n",proc[sou[a]].solve_in(a, b));
	    else printf("%d\n", solve(a, b));
	}
    }
    return 0;
}
