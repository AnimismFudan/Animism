#include <bits/stdc++.h>
#define intl long long
using namespace std;

const intl Mo = 1000000007LL;

int T;
intl ans;
intl p[30];
intl P;
int n, m;

intl fpm(intl a, intl b) {
	if (!a) return 0LL;
	intl ans = 1LL;
	for (; b; b >>= 1) {
		if (b & 1LL) ans *= a, ans %= Mo;
		a *= a; a %= Mo;
	}
	return ans;
}

int main() {
	//freopen("A.in","r",stdin);
	//freopen("A.out","w",stdout);
	for (scanf("%d",&T); T; T--) {
		scanf("%d %d",&n,&m);
		P = 0LL;
		for (int i = 1; i <= m; i++) scanf("%lld",&p[i]), (P += p[i]) %= Mo;
		P = fpm(P, Mo - 2LL);
		for (int i = 1; i <= m; i++) (p[i] *= P) %= Mo;
		ans = 0LL;
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= m; j++) {
				if (i == j) continue;
				if (p[i] != p[j]) {
					intl bg = p[i] * fpm(p[j], n - 1) % Mo;
					intl bias = p[i] * fpm(p[j], Mo - 2LL) % Mo;
					ans += bg * ((fpm(bias, n - 1) + Mo - 1) % Mo) % Mo * fpm((bias + Mo - 1) % Mo, Mo - 2LL) % Mo;
					ans %= Mo;
				} else {
					ans += fpm(p[i], n) * (intl) (n - 1) % Mo;
					ans %= Mo;
				}
			}
		for (int i = 1; i <= m; i++)
			(ans += fpm(p[i], n)) %= Mo;
		cout << ans << endl;
	}
	return 0;
}
