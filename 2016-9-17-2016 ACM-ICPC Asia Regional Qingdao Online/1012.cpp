#include <bits/stdc++.h>
using namespace std;

bitset<90> g[12];
int f[55][12][90],st[55][12][90],pas[55][12][90];
int ans[12],Ans[55][55][55];
int T,n,m;
int mark[55],done[55],A[55];
int wp[4];

void dp(int a,int b,int c) {
    for (int i = 1; i <= n; i++) done[i] = 0;
    done[a] = done[b] = done[c] = 1;
    memset(g,0,sizeof(g));
    g[0][0] = 1;
    for (int u = 1; u <= n; u++) {	
	if (done[u]) continue;
	for (int k = 9; k >= 0; k--) {
	    if (A[u] > 87) continue;
	    g[k + 1] = g[k + 1] | (g[k] << A[u]);
	}
    } 
    Ans[a][b][c] = g[10][87];
}

void init() {
    memset(f,0,sizeof(f));
    memset(g,0,sizeof(g));
    memset(st,0,sizeof(st));
    memset(pas,0,sizeof(pas));
    memset(done,0,sizeof(done));
    memset(mark,0,sizeof(mark));
}

bool prepare() {
    f[0][0][0] = 1; pas[0][0][0] = 0;
    for (int u = 1; u <= n; u++) {
	memcpy(f[u], f[u - 1], sizeof(f[u]));
	memcpy(pas[u], pas[u - 1], sizeof(pas[u]));
	memcpy(st[u], st[u - 1], sizeof(st[u]));
	for (int k = 0; k < 10; k++)
	    for (int val = 0; val + A[u] <= 87; val++) {
		if (f[u][k + 1][val + A[u]]) continue;
		f[u][k + 1][val + A[u]] |= f[u - 1][k][val];
		if (f[u - 1][k][val]) {
		    st[u][k + 1][val + A[u]] = u;
		    pas[u][k + 1][val + A[u]] = st[u - 1][k][val];
		}
	    }
    }
    if (!f[n][10][87]) return false;
    int sum = 87, u = st[n][10][87];
    for (int i = 10; i >= 1; i--) {
	ans[i] = u;
	int s = sum - A[u];
	u = pas[u][i][sum];
	sum = s;
    }
    for (int i = 1; i <= 10; i++)
	mark[ans[i]] = 1;
    for (int a = 0; a <= n; a++)
	for (int b = a; b <= n; b++) {
	    //if (b == a && b != 0) continue;
	    for (int c = b; c <= n; c++) {
		//if (c == b && c != 0) continue;
		if (!mark[a] && !mark[b] && !mark[c]) {
		    Ans[a][b][c] = 1;
		    continue;
		}
		dp(a,b,c);
	    }
	}
    return true;
}

void special() {
    scanf("%d",&m);
    for (int i = 1; i <= m; i++) {
	int k;
	for (int j = 1; j <= 3; j++)
	    scanf("%d",&k);
	printf("No\n");
    }
}

void solve() {
    scanf("%d",&m);
    for (; m; m--) {
	int k = 3;
	wp[1] = wp[2] = wp[3] = 0;
	for (int i = 1; i <= k; i++) scanf("%d",&wp[i]);
	sort(wp + 1,wp + 4);
	if (Ans[wp[1]][wp[2]][wp[3]])
	    printf("Yes\n");
	else printf("No\n");
    }
}

int main() {
    freopen("1012.in","r",stdin);
    freopen("1012.out","w",stdout);
    for (scanf("%d",&T); T; T--) {
	init();
	scanf("%d",&n);
	for (int i = 1; i <= n; i++)
	    scanf("%d",&A[i]);	
	bool flag = prepare();
	if (!flag) special();
	else solve();
    }
    return 0;
}
