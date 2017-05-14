#include <bits/stdc++.h>
#define intl long long
using namespace std;

intl ans;
int n, m;

int main() {
	freopen("angle-patterns.in","r",stdin);
	freopen("angle-patterns.out","w",stdout);
	intl ans = 0LL;
	scanf("%d %d",&n,&m);
	for (int x = 2; x <= n; x++)
		for (int y = 2; y <= m; y++) {
			int res = __gcd(x - 1, y - 1) - 1;
			intl just = n * m - x * y + (x * y - res - 2) / 2;
			ans += just * 2LL;
			ans += res * 3;
		}
	for (int y = 2; y <= m; y++) {
		ans += (n * (m - y + 1) - 1) * 2LL;
		ans += n * (y - 2);
	}
	for (int x = 2; x <= n; x++) {
		ans += (m * (n - x + 1) - 1) * 2LL;
		ans += m * (x - 2);
	}
	cout << ans << endl;
	return 0;
}
