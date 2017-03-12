#include <bits/stdc++.h>
#define maxn 1010000
using namespace std;

int ans,t,top;
int A[maxn],B[maxn],C[maxn],nex[maxn];
int n,m,p,done[maxn],T;

int main() {
    freopen("H.in","r",stdin);
    freopen("H.out","w",stdout);
    for (scanf("%d",&T); T; T--) {
	scanf("%d %d %d",&n,&m,&p);
	for (int i = 1; i <= n; i++)
	    scanf("%d",&A[i]);
	for (int i = 1; i <= m; i++)
	    scanf("%d",&B[i]);
	for (int i = 1; i <= n; i++)
	    done[i] = 0;
	B[m + 1] = 0; nex[1] = 0; ans = 0;
	for (int i = 2; i <= m; i++) {
	    nex[i] = nex[i - 1];
	    for (;nex[i] && B[nex[i] + 1] != B[i]; nex[i] = nex[nex[i]]);
	    if (B[nex[i] + 1] == B[i]) nex[i]++;
	}
	for (int i = 1; i <= n; i++) {
	    if (done[i]) continue;
	    top = 0;
	    for (int j = i; j <= n; j += p) {
		C[++top] = A[j]; done[j] = 1;
	    }
	    C[top + 1] = -1;
	    int q = 0;
	    for (int j = 1; j <= top; j++) {
		for (; q && B[q + 1] != C[j]; q = nex[q]);
		if (B[q + 1] == C[j]) q++;
		if (q == m) ans++;
	    }
	}
	printf("Case #%d: %d\n",++t,ans);
    }
    return 0;
}
