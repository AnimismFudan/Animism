#include <bits/stdc++.h>
#define intl long long
using namespace std;

const intl Mo = 1000000007LL;
intl ans;
intl C[310][310];
int A[310];
int n, k;
intl fac[310], inv[310];

intl fpm(intl a, intl b) {
	intl ans = 1LL;
	for (; b; b >>= 1) {
		if ((b & 1LL)) ans *= a, ans %= Mo;
		a *= a, a %= Mo;
	}
	return ans;
}

void add(intl &a, intl b) {
	a += b;
	a %= Mo;
}

int main() {
	freopen("D.in","r",stdin);
	freopen("D.out","w",stdout);
	scanf("%d %d",&n,&k);
	for (int i = 1; i <= n; i++)
		scanf("%d",&A[i]);
	C[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= n; j++)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % Mo;
	}

	fac[0] = 1LL;
	for (int i = 1; i <= n; i++) fac[i] = (fac[i - 1] * (intl) i) % Mo;
	for (int i = 0; i <= n; i++) inv[i] = fpm(fac[i], Mo - 2LL);
	
	for (int u = 1; u <= n; u++) {
		intl cnt = 0;
		for (int v = 1; v <= n; v++) {
			if (u == v) continue;
			if (A[v] < A[u] || (A[v] == A[u] && v < u)) cnt++;
 		}
		intl tnc = n - cnt - 1;
		add(ans, ((intl) n * (intl) (n - 1) / 2LL) % Mo * fac[n - 2] % Mo * tnc % Mo * (intl) A[u] % Mo);
		intl just = 0;
		for (int x = k + 1; x <= n; x++) {
			intl x_ = x - k;
			for (int j = 0; j < x_; j++) {
				intl sing = 1;
				sing *= C[cnt][j] * fac[x - 1] % Mo * inv[x - 1 - j] % Mo;
				sing %= Mo;
				sing *= (intl) (x - 1 - j);
				sing %= Mo;
				sing *= C[tnc][x - 1 - 1 - j] * fac[x - 1 - j - 1] % Mo;
				sing %= Mo;
				if (cnt <= j) continue;
				sing *= (intl) (cnt - j);
				sing %= Mo;
				sing *= (intl) fac[n - x];
				sing %= Mo;
				add(just, sing);
			}
		}
		add(ans, just * (intl) A[u] % Mo);
		intl sum = 0;
		for (int v = 1; v <= n; v++) {
			if (u == v) continue;
			if (A[v] < A[u] || (A[v] == A[u] && v < u)) sum += A[v], sum %= Mo;
		}
		just = ((fac[n] * inv[2] % Mo * (intl) cnt % Mo - just) % Mo + Mo) % Mo;
		add(ans, just * sum % Mo * fpm(cnt, Mo - 2LL) % Mo);
	}
	for (int i = 1; i <= n; i++)
		add(ans, (intl) A[i] * fac[n] % Mo);
	cout << ans << endl;
	return 0;
}
