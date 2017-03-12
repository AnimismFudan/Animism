#include <bits/stdc++.h>
#define intl long long
using namespace std;

const intl Mo = 1000000007LL;

intl f[3400][3400],g[3400][3400],F[3400][3400],G[3400][3400];
int n,d,t,K;

void add(intl &a, intl b) {
    a += b;
    a %= Mo;
}

int main() {
    scanf("%d %d %d %d",&n,&d,&t,&K);
    g[0][0] = 1; G[0][0] = 1;
    if (d == 1) {
		if (t != n) cout << 0 << endl;
		else {
			intl ans = 1LL;
			for (int i = 1; i <= n; i++) (ans *= K) %= Mo;
			cout << ans << endl;
		}
		return 0;
    }
    for (int j = 0; j <= t; j++) {
		for (int i = 1; i <= n; i++) {	    	
			if (j > 0) {
				add(f[i][j], f[i - 1][j - 1]);
				if (i > d) {
					add(f[i][j], g[i - d][j - 1] * (intl) (K - 1));
					add(f[i][j], f[i - d][j - 1] * (intl) (K - 1));
				}
				else if (i == d)
					add(f[i][j], g[i - d][j - 1] * (intl) (K));
			}
			int k = max(i - d, 0);
			//if (i >= d) {
			add(g[i][j], (F[i - 1][j] - F[k][j]) * (intl) (K - 1));
			add(g[i][j], (G[i - 1][j] - G[k][j]) * (intl) (K - 1));
			/*} else {
			  add(g[i][j], (F[i - 1][j]) * (intl) (K - 1));
			  add(g[i][j], (G[i - 1][j]) * (intl) (K - 1));	    
			  }*/
			if (i < d && j == 0)
				add(g[i][j], K);	    
			F[i][j] = (F[i - 1][j] + f[i][j]) % Mo;
			G[i][j] = (G[i - 1][j] + g[i][j]) % Mo;
		}
    }
    cout << ((f[n][t] + g[n][t]) % Mo + Mo) % Mo;
    return 0;
}

