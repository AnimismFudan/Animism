#include <bits/stdc++.h>
#define maxn 101000
#define lk (u << 1)
#define rk ((u << 1) | 1)
#define midl ((L + R) >> 1)
#define midr ((midl) + 1)
using namespace std;

int val[maxn << 2];
int A[maxn];
int n,m;
int T;

void build(int u,int L,int R) {
    if (L == R) { val[u] = A[L]; return; }
    build(lk,L,midl);
    build(rk,midr,R);
    val[u] = min(val[lk], val[rk]);
}

int find(int u,int L,int R,int l,int r,int k) {
    if (l > r) return n + 1;
    if (val[u] > k) return n + 1;
    if (L == l && R == r) {
	if (L == R) {
	    if (val[u] <= k) return L;
	    return n + 1;
	}
	if (val[lk] <= k) return find(lk,L,midl,l,midl,k);
	else return find(rk,midr,R,midr,r,k);
    }
    if (r < midr) return find(lk,L,midl,l,r,k);
    else if (l > midl) return find(rk,midr,R,l,r,k);
    else {
	int ans = find(lk,L,midl,l,midl,k);
	if (ans == n + 1)
	    ans = find(rk,midr,R,midr,r,k);
	return ans;
    }
}

int main() {
    freopen("1008.in","r",stdin);
    freopen("1008.out","w",stdout);
    for (scanf("%d",&T); T; T--) {
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) scanf("%d",&A[i]);
	build(1,1,n);
	scanf("%d",&m);
	for (int i = 1; i <= m; i++) {
	    int l,r;
	    scanf("%d %d",&l,&r);
	    int ans = A[l];
	    for (int u = l; u <= r;) {
		u = find(1, 1, n, u + 1, r, ans);
		if (u <= r) ans %= A[u];
		else break;
		if (!ans) break;
	    }
	    printf("%d\n",ans);
	}
    }
}
