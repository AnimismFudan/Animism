#include <bits/stdc++.h>
#define intl long long
using namespace std;

intl ans,tnc[30],cnt[30];
intl nex[301000][27];
int head,tail,top;
char s[1010000];
int n,m,N;

int add(int u,int v) {
    if (nex[u][v]) return nex[u][v];
    nex[u][v] = ++top;
    memset(nex[top], 0,sizeof(nex[top]));
    return top;
}

void dfs(int u) {
    for (int i = 0; i < 26; i++) {
	if (nex[u][i])
	    dfs(nex[u][i]);
    }
    if (u == 1) return;
    for (int i = 0; i < 26; i++)
	if (!nex[u][i])
	    ans += cnt[i];
	else
	    ans += tnc[i];
}

void Dfs(int u,int ok) {
    for (int i = 0; i < 26; i++) {
	if (nex[u][i])
	    Dfs(nex[u][i], i);
    }
    if (ok >= 0) cnt[ok]++;
}

int main() {
    freopen("D.in","r",stdin);
    freopen("D.out","w",stdout);
    while (scanf("%d %d",&n,&m) != EOF && n && m) {
	top = 0; ans = 0;
	memset(cnt,0,sizeof(cnt));
	memset(tnc,0,sizeof(tnc));
	head = ++top;
	memset(nex[head],0,sizeof(nex[head]));
	for (int i = 1; i <= n; i++) {
	    scanf("%s",s + 1);
	    N = strlen(s + 1);
	    int u = head;
	    for (int i = 1; i <= N; i++) {
		u = add(u, s[i] - 'a');
	    }	    
	}
	tail = ++top;
	memset(nex[tail], 0, sizeof(nex[tail]));
	for (int i = 1; i <= m; i++) {
	    scanf("%s",s + 1);
	    N = strlen(s + 1);
	    int u = tail;
	    for (int i = N; i >= 1; i--) {
		u = add(u, s[i] - 'a');
	    }
	    tnc[s[N] - 'a'] = 1;
	}
	Dfs(tail, -1);
	dfs(head);
	cout << ans << endl;
    }
    return 0;
}
