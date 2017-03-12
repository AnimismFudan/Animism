#include <bits/stdc++.h>
#define intl long long
using namespace std;

intl top;
intl ans[1010000];

bool check1(intl n) {
	double ans = -3.0 + sqrt(9.0 + 4.0 * (n - 1) * 3.0);
	ans /= 6.0;
	intl x = round(ans);
	return (x * (x + 1LL) * 3LL + 1LL == n);
}

bool check2(intl n) {
	intl y = top;
	for (intl x = 0; x <= top && ((ans[x] << 1) <= n); x++) {
		while (ans[y] + ans[x] > n) y--;
		if (ans[y] + ans[x] == n) return true;		
	}
	return false;
}

bool check3(intl n) {
	return (!((n - 3LL) % 6LL));
}

intl n;

int main() {
	//freopen("E.in","r",stdin);
	//freopen("E.out","w",stdout);
	for (intl i = 0; 3LL * i * (i + 1LL) + 1LL <= 1000000000000LL; i++) {
		ans[i] = 3LL * i * (i + 1LL) + 1LL;
		top = i;
	}
	while (scanf("%lld",&n) != EOF && n) {
		if (check1(n)) { printf("%d\n",1); continue; }
		else if (check3(n + 1LL) && check2(n)) { printf("%d\n", 2); continue; }
		else {
			intl m = n;
			while (!check3(m)) m--;
			printf("%lld\n", 3LL + n - m);
		}
	}
	return 0;
}
