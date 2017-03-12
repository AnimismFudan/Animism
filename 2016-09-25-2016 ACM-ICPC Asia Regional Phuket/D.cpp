#include <bits/stdc++.h>
using namespace std;

struct str { int a,b,c; } edge[1010000];

int fa[1010000];
int n,m,top,e,T,t,ans;
int mark[110][110][2];
char s[110][110];

bool cmp(const str &a, const str &b) {
    return (a.c < b.c);
}

int find(int a) {
    return (fa[a] == a ? a : (fa[a] = find(fa[a])));
}

void com(int a,int b) {
    if (find(a) == find(b)) return;
    fa[fa[a]] = fa[b];
}

int main() {
    freopen("D.in","r",stdin);
    freopen("D.out","w",stdout);
    for (scanf("%d",&T); T; T--) {
	scanf("%d %d\n",&n,&m);
	for (int i = 1; i <= n; i++)
	    scanf("%s",s[i] + 1);
	top = 0; e = 0;
	for (int i = 1; i <= n; i++)
	    for (int j = 1; j <= m; j++)
		mark[i][j][0] = ++top, mark[i][j][1] = ++top;

	for (int i = 1; i <= top; i++) fa[i] = i;
	ans = 0;
	
	for (int i = 1; i <= n; i++) {
	    for (int j = 1; j < m; j++) {
		com(mark[i][j][1], mark[i][j + 1][0]);
	    }	
	}
	

	for (int i = 1; i < n; i++)
	    for (int j = 1; j <= m; j++) {
		if (s[i][j] == '/' && s[i + 1][j] == '\\')
		    com(mark[i][j][1], mark[i + 1][j][1]);
		else if (s[i][j] == '/' && s[i + 1][j] == '/')
		    com(mark[i][j][1], mark[i + 1][j][0]);
		else if (s[i][j] == '\\' && s[i + 1][j] == '/')
		    com(mark[i][j][0], mark[i + 1][j][0]);
		else
		    com(mark[i][j][0], mark[i + 1][j][1]);
	    }
	
	for (int i = 1; i <= n; i++)
	    for (int j = 1; j <= m; j++) {
		int c;
		scanf("%d",&c);
		edge[++e] = (str) { mark[i][j][0], mark[i][j][1], c };
	    }
	sort(edge + 1, edge + e + 1, cmp);
	for (int i = 1; i <= e; i++) {
	    int a = edge[i].a;
	    int b = edge[i].b;
	    if (find(a) == find(b)) continue;
	    fa[fa[a]] = fa[b];
	    ans += edge[i].c;
	}
	printf("Case %d: %d\n",++t,ans);
    }
    return 0;
}
