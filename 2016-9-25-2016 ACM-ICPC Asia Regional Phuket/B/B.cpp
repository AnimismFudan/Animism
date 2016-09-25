#include <bits/stdc++.h>
using namespace std;

int A[20100];
int ans,Ans,now;
int t,T,n,m;

int main() {
    freopen("B.in","r",stdin);
    freopen("B.out","w",stdout);
    for (scanf("%d",&T); T; T--) {
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++) scanf("%d",&A[i]);
	sort(A + 1, A + n + 1);
	ans = 0; now = 0; Ans = 0;
	for (int i = 1; i <= n && now + A[i] <= m; i++) {
	    ans++;
	    now += A[i];
	    Ans += now;
	}
	printf("Case %d: %d %d %d\n",++t,ans,now,Ans);
    }
    return 0;
}
