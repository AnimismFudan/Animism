#include <bits/stdc++.h>
#define intl long long
using namespace std;

intl val[120];
int a, b, n;

intl fpm(intl a, intl b) {
	intl ans = 1LL;
	for (; b; b--)
		ans *= a;
	return ans;
}

intl solve(int u) {
	intl v = val[u];
	if (u == n) {
		return (u == 1) ? v % 10LL : v % 4LL + 4LL;
	}
	intl x = solve(u + 1);
	v = fpm(val[u], x);
	return (u == 1) ? v % 10LL : v % 4LL + 4LL;
}

int main() {
	freopen("abtower.in","r",stdin);
	freopen("abtower.out","w",stdout);
	scanf("%d %d",&a, &b);
	for (int i = a; i <= b; i++) val[++n] = i;	
	cout << solve(1) % 10LL << endl;
	return 0;
}
