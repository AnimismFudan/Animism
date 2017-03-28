#include <bits/stdc++.h>
#define intl long long
using namespace std;

intl k, R, L;
int ans;

bool check(intl x) {
	if (R / x < k) return false;		
	intl v = x;	
	x *= k;
	if (x < L || x > R) return false;
	intl cnt = 0;
	for (; x; x /= 10LL) cnt += (x % 10LL) * (x % 10LL);
	//if (cnt == v) printf("%lld\n", v * k);
	return (cnt == v);
}

int main() {
	//freopen("G.in","r",stdin);
	//freopen("G.out","w",stdout);
	cin >> k >> L >> R;
	for (intl i = 1; i <= 18 * 9 * 9; i++)
		if (check(i)) ans++;
	printf("%d\n",ans);
	return 0;
}
