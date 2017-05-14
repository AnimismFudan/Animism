#include <bits/stdc++.h>
#define intl long long
using namespace std;

intl ans;
int n, m;

int main() {
	freopen("angle-patterns.in","r",stdin);
	freopen("angle-patterns.out","w",stdout);
	scanf("%d %d",&n,&m);
	for (int x = 2; x <= n; x++)
		for (int y = 2; y <= m; y++) {
			ans += (x - 2) * (y - 2) * 6;
			ans += (x - 2) * 3;
			ans += (y - 2) * 3;
			ans += ((x - 2) + (y - 2)) * 6; 
			ans += 6LL;
			ans += (x - 2) * (y - 2) * 3;
		}
	for (int y = 2; y <= m; y++) {
		ans += ((m - y + 1) - 1) * 2LL;
		ans += (y - 2);
	}
	for (int x = 2; x <= n; x++) {
		ans += ((n - x + 1) - 1) * 2LL;
		ans += (x - 2);
	}
	cout << ans << endl;
	return 0;
}
