#include <bits/stdc++.h>
using namespace std;

int ans = 26;
int f[10100];
int n;
char s[10100];

int main() {
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	scanf("%s",s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; i++) {
		f[i] = 1;
		for (int j = 1; j < i; j++)
			if (s[j] < s[i]) f[i] = max(f[i], f[j] + 1);
		ans = min(ans, 26 - f[i]);
	}
	printf("%d\n",ans);
	return 0;
}
