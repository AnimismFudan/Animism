#include <bits/stdc++.h>
#define eps (1e-8)
using namespace std;

int fail[110],nex[110][10];
double d[110][110];
int n,m,top,sou[110],T;
int que[1100],mark[110];
int A[110][110];

int add(int u,int k) {
    if (!nex[u][k]) {
    nex[u][k] = ++top;
    memset(nex[top], 0, sizeof(nex[top]));    
    mark[top] = 0;
    }
    return nex[u][k];
}

void bfs() {
    int L = 0, R = 0;
    que[++R] = 1; fail[1] = 1;
    while (L < R) {
    int u = que[++L];
    for (int k = 1; k <= 6; k++) {
        int v = nex[u][k];
        if (!v) continue;
        fail[v] = fail[u];
        for (; fail[v] != 1 && !nex[fail[v]][k]; fail[v] = fail[fail[v]]);
        if (nex[fail[v]][k] && nex[fail[v]][k] != v) fail[v] = nex[fail[v]][k];
        que[++R] = v;
    }
    }
}

int trans(int u,int k) {
    for (; u != 1 && !nex[u][k]; u = fail[u]);
    if (nex[u][k]) u = nex[u][k];
    return u;
}

void solve() {
    for (int u = 1; u <= top; u++) {
    int v;
    for (v = u; fabs(d[v][u] < eps); v++);
    for (int i = 1; i <= top + 1; i++)
        swap(d[u][i], d[v][i]);
    for (v = 1; v <= top; v++) {
        if (v == u) continue;
        double co = d[v][u] / d[u][u];
        for (int k = 1; k <= top + 1; k++) {
        d[v][k] -= d[u][k] * co;
        }
    }
    }

    for (int i = 1; i <= top; i++)
    d[i][top + 1] /= d[i][i];    
}

int main() {
    for (scanf("%d",&T); T; T--) {
    scanf("%d %d",&n,&m); mark[1] = 0;
    top = 1; memset(nex[1],0,sizeof(nex[1])); 
    for (int i = 1; i <= n; i++) {
        int u = 1;
        for (int j = 1; j <= m; j++) {
        scanf("%d",&A[i][j]);
        u = add(u, A[i][j]);
        }
        sou[i] = u;
        mark[u] = 1;
    }
    bfs();
    for (int i = 1; i <= n; i++) {
        memset(d,0,sizeof(d));
        for (int u = 1; u <= top; u++) {
        if (u == sou[i]) {
            d[u][u] = 1; d[u][top + 1] = 1;
            continue;
        } else if (mark[u]) {
            d[u][u] = 1; d[u][top + 1] = 0;
            continue;
        }
        d[u][u] = 1;        
        for (int k = 1; k <= 6; k++) {
            int v = trans(u, k);
            d[u][v] += -1.0 / 6;
        }
        }
        solve();
        printf("%.6lf",d[1][top + 1]);
        if (i < n) putchar(' ');
        else putchar('\n');
    }
    }
    return 0;
}
