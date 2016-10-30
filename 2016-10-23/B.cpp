#include <bits/stdc++.h>
using namespace std;

int Max[110],Min[110],tp[110],A[110][1100];
int n,m,T,top;

struct str { int v,p; } val[110 * 1100];

bool cmp(const str &a, const str &b) {
    return (a.v < b.v);
}

int main() {
    freopen("B.in","r",stdin);
    freopen("B.out","w",stdout);
    for (scanf("%d",&T); T; T--) {
	scanf("%d %d",&n,&m);
	top = 0;
	for (int i = 1; i <= n; i++) {
	    Min[i] = Max[i] = 0;
	    for (int j = 1; j <= m; j++) {
		scanf("%d",&A[i][j]);
		val[++top] = (str) { A[i][j], i };
	    }
	    sort(A[i] + 1, A[i] + m + 1);
	    reverse(A[i] + 1, A[i] + m + 1);
	    
	}

	sort(val + 1, val + top + 1, cmp);
	
	for (int u = 1; u <= n; u++) {
	    for (int i = 1; i <= n; i++)
		tp[i] = 1;
	    bool flag = true;
	    for (int t = 1; t <= m; t++) {
		for (int v = 1; v <= n; v++) {
		    if (v == u) continue;
		    while (tp[v] <= m && A[v][tp[v]] >= A[u][t])
			tp[v]++;
		    if (tp[v] > m) flag = false;
		}
		for (int v = 1; v <= n; v++) {
		    tp[v]++;
		}
		if (!flag) break;
		Max[u]++;
	    }
	}

	for (int u = 1; u <= n; u++) {
	    int t = 1;
	    for (int i = m; i >= 1; i--) {
		while (t <= top && (val[t].p == u || val[t].v < A[u][i])) t++;
		if (t > top) break;
		t++;
		Min[u]++;
	    }
	}

	for (int i = 1; i <= n; i++)
	    printf("%d %d\n",m - Min[i], Max[i]);
    }
    return 0;
}
