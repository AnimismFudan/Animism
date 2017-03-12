#include <bits/stdc++.h>
using namespace std;

int pri[3010];
int f[3010],g[3010],n,T,top;
int ans[6];

bool is_prime(int u) {
    for (int i = 2; i < u; i++)
	if (!(u % i)) return false;
    return true;
}

int main() {
    freopen("J.in","r",stdin);
    freopen("J.out","w",stdout);
    for (int i = 2; i <= 1000; i++) {
	if (is_prime(i))
	    pri[++top] = i;
    }

    for (int i = 1; i <= top; i++)
	for (int j = 1; j <= top; j++)
	    f[pri[i] + pri[j]] = pri[i];
    for (int i = 1; i <= top; i++)
	for (int j = 1; j <= 1000; j++)
	    if (f[j])
		g[pri[i] + j] = pri[i];
    for (scanf("%d",&T); T; T--) {
	scanf("%d",&n);
	ans[1] = g[n];
	ans[2] = f[n - ans[1]];
	ans[3] = n - ans[1] - ans[2];
	sort(ans + 1, ans + 4);
	printf("%d %d %d\n",ans[1], ans[2], ans[3]);
    }
    return 0;
}
