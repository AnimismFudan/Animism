#include <bits/stdc++.h>
#define intl long long
using namespace std;

map<intl,int> mp,pm;
int ans;
int n;
char s[1010];

int main() {
    freopen("B.in","r",stdin);
    freopen("B.out","w",stdout);
    scanf("%s",s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++)
	for (int j = i + 1; j <= n; j++) {
	    intl has = 233LL * (s[i] + 1) + (s[j] + 1);
	    intl sah = 2333LL * (s[i] + 1) + (s[j] + 1);
	    int a = i, b = j;
	    for (int k = a + b; k <= n; k = a + b) {
		swap(a, b);
		b += a;
		sah = (sah * 2333LL) + (intl) (s[k] + 1);
		has = (has * 233LL + (intl) (s[k] + 1));
		has %= 1000000007LL;
		sah %= 1998585857LL;
	    }
	    if (!mp[has] || !pm[sah]) {
		pm[sah] = 1;
		mp[has] = 1;
		ans++;
	    }
	}
    printf("%d\n",ans);
    return 0;
}
