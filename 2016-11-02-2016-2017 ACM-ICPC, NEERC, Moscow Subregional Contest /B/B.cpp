#include <bits/stdc++.h>
#define intl long long
using namespace std;

intl gcd(intl a, intl b) {
	return (b ? gcd(b, a % b) : a);
}

intl k,w,l,v,r;

int main() {
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	cin >> l >> r >> w;
	k = gcd(r, w);
	v = ((l - w) / k) * k;
	while (v <= l - w) v += k;
	if (v >= r) printf("OK");
	else printf("DEADLOCK");
	return 0;
}
