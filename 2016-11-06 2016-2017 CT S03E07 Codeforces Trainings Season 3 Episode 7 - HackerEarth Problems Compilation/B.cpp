#include <bits/stdc++.h>
using namespace std;

int f[110][110];
int T,n;
char s[110];

int main() {
    for (scanf("%d",&T); T; T--) {
		scanf("%s",s + 1);
		n = strlen(s + 1);
		memset(f,0,sizeof(f));
		for (int i = 1; i <= n; i++) f[i][i] = 1;
		for (int l = 1; l < n; l++)
			for (int L = 1; L + l <= n; L++) {
				int R = L + l;
				int k = (L + R) / 2;
				if (k - L + 1 == R - k && l != 1)
					f[L][R] |= f[L][k] & f[k + 1][R];
				else if (l == 1 && ((s[L] == 'P') || (s[R] == 'P')))
					f[L][R] |= 1;
			}
		if (f[1][n]) printf("YES\n");
		else printf("NO\n");
    }
    return 0;
}
