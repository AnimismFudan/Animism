#include <bits/stdc++.h>
#define intl long long
#define maxn 2001000
using namespace std;

const intl Mo = 1000000007LL;

map<int,int> st;
intl fac[maxn], inv[maxn];
int n, l, k, top;
int len[maxn], cnt[maxn];
intl ans, INV;

intl C(int a, int b) {
	if (a < b) return 0LL;
	return (fac[a] * inv[b] % Mo * inv[a - b] % Mo);	
}

intl solve(int x, int n) {
	return C(x + n - 1, n - 1);
}

intl fpm(intl a, intl b) {
	if (!a) return 0LL;
	intl ans = 1LL;
	for (; b ; b >>= 1) {
		if (b & 1LL) ans *= a, ans %= Mo;
		a *= a; a %= Mo;
	}
	return ans;
}

intl SOLVE(int x) {
	intl ans = 0LL;
	for (int i = 1; i <= top; i++)
		(ans += fpm(k - x, len[i]) * (intl) (cnt[i])) %= Mo;
	ans = (ans * INV) % Mo;
	return ans;
}

int main() {
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	scanf("%d %d %d",&n,&k,&l);
	fac[0] = 1LL;
	INV = fpm(l, Mo - 2LL);
	for (int i = 1; i <= n + k + 1; i++) fac[i] = (fac[i - 1] * (intl) i) % Mo;
	inv[n + k + 1] = fpm(fac[n + k + 1], Mo - 2LL);
	for (int i = n + k; i >= 0; i--) inv[i] = (inv[i + 1] * (intl) (i + 1)) % Mo;	
	for (int i = 1; i <= l; i++) {
		st[__gcd(i, l)]++;
	}

	for (auto i = st.begin(); i != st.end(); i++) {
		len[++top] = i -> first;
		cnt[top] = i -> second;
	}
	
	if (n == l) {
		ans = SOLVE(0);
	} else {
		for (int x = 0; x < k; x++) {
			ans += solve(x, n);
			ans %= Mo;
		}
	}
	cout << ans << endl;
	return 0;
}
