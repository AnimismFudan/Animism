#include <bits/stdc++.h>
#define maxn 201000
#define midl ((L + R) >> 1)
#define midr (midl + 1)
using namespace std;

int rt[maxn],vis[maxn],Rt[maxn];
int lk[maxn * 25], rk[maxn * 25], sum[maxn * 25];
int n,m,T,ans,top,t;
int A[maxn];

int build(int v, int L, int R, int k, int val) {
    int u = ++top;
    sum[u] = sum[v] + val;
    lk[u] = rk[u] = 0;
    if (L == R) return u;
    if (k < midr) {
	rk[u] = rk[v];
	lk[u] = build(lk[v], L, midl, k, val);
    } else {
	lk[v] = lk[v];
	rk[u] = build(rk[v], midr, R, k, val);
    }
    return u;
}

int Build(int v, int L, int R, int k, int val) {
    int u = ++top;
    sum[u] = sum[v] + val;
    lk[u] = rk[u] = 0;
    if (L == R) return u;
    if (k < midr) {
	rk[u] = rk[v];
	lk[u] = build(lk[v], L, midl, k, val);
    } else {
	lk[v] = lk[v];
	rk[u] = build(rk[v], midr, R, k, val);
    }
    return u;
}

int Find(int u, int L, int R, int k) {
    if (L == R) return L;
    if (k <= sum[lk[u]]) return Find(lk[u], L, midl, k);
    else return Find(rk[u], midr, R, k - sum[lk[u]]);
}

int find(int u, int L, int R, int k) {
    if (k < L) return 0;
    if (R <= k) return sum[u];
    if (k < midr) return find(lk[u], L, midl, k);
    else return sum[lk[u]] + find(rk[u], midr, R, k);
}

void init() {
    memset(vis,0,sizeof(vis));
    top = 0;
    ans = 0;
}

int main() {
    freopen("I.in","r",stdin);
    freopen("I.out","w",stdout);
    for (scanf("%d",&T); T; T--) {
	printf("Case #%d: ",++t);
	scanf("%d %d",&n,&m);
	init();
	for (int i = 1; i <= n; i++)
	    scanf("%d",&A[i]);
	rt[n + 1] = 0;
	for (int i = n; i >= 1; i--) {
	    rt[i] = rt[i + 1];
	    if (vis[A[i]]) {
		rt[i] = build(rt[i], 1, n, vis[A[i]], -1);
		Rt[i] = Build(Rt[i], 1, n, A[i], -1);
	    }
	    vis[A[i]] = i;
	    rt[i] = build(rt[i], 1, n, vis[A[i]], 1);
	    Rt[i] = Build(Rt[i], 1, n, A[i], 1);
	}
	ans = 0;
	for (; m; m--) {
	    int L, R;
	    scanf("%d %d",&L,&R);
	    L += ans; L %= n; L++;
	    R += ans; R %= n; R++;
	    if (L < R) swap(L, R);
	    int k = find(rk[L], 1, n, R);
	    printf("%d ",ans = Find(rt[L], 1, n, (k + 1) / 2));
	}
	putchar('\n');
    }
    return 0;
}
