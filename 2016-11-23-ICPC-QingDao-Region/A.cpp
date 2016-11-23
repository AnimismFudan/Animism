#include <bits/stdc++.h>
#define intl long long
using namespace std;

intl ans;
int n,T;

int main() {
	for (scanf("%d",&T); T; T--) {
		scanf("%d",&n);
		ans = 0LL;
		for (int i = 1; i <= n; i++) {
			int a, b;
			scanf("%d %d",&a,&b);
			ans += (intl) a * (intl) b;
		}
		cout << ans << endl;
	}
	return 0;
}
