#include <bits/stdc++.h>
#define intl __int128
using namespace std;

const intl MAX = 100000;

long long ans;

void exgcd(intl p, intl q, intl &x, intl &y) {
	if (!q) { x = 1LL, y = 0LL; return; }
	intl x_, y_;
	exgcd(q, p % q, x_, y_);
	x = y_;
	y = x_ - (p / q) * y_;
	return;
}

intl Abs(intl a) {
	if (a > (intl) 0) return a;
	return -a;
}

void proc(intl base, intl x, intl y, intl k, intl p, intl q) {
	for (intl sing = base - (intl) 2; sing <= base + (intl) 2; sing++) {
		intl cnt = 0;
		intl b = x + sing * q;
		intl d = y - sing * p;
		cnt = Abs(-k * p + b) + Abs(b) + Abs(k * q + d) + Abs(d);
		if (cnt > (intl) (1LL << 60)) continue;
		ans = min(ans, (long long) cnt);
	}
}

void solve(intl k, intl p, intl q) {
	intl san = (intl) 1 - k * (-p * p + q * q);
	if (san & (intl) 1) return;
	san = san / (intl) 2;
	intl x, y;
	exgcd(p, q, x, y);
	x *= san;
	y *= san;
	intl base = (k * p - x) / q;
	proc(base, x, y, k, p, q);
	base = (-x) / q;
	proc(base, x, y, k, p, q);
	base = (-k * q - y) / p;
	proc(-base, x, y, k, p, q);
	base = (-y) / p;
	proc(-base, x, y, k, p, q);
	return;
}

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

int main() {
	freopen("pqknight.in","r",stdin);
	freopen("pqknight.out","w",stdout);
	int p, q;
	cin >> p >> q;
	if (!p) {
		if (q != 1) printf("-1\n");
		else printf("1\n");
		return 0;
	}
	if (!q) {
		if (p != 1) printf("-1\n");
		else printf("1\n");
		return 0;
	}
	if (!((p ^ q) & 1)) { printf("-1\n"); return 0; }
	if (gcd(p, q) != 1) { printf("-1\n"); return 0; }
	ans = 1LL << 60;
	for (intl k = -MAX; k <= MAX; k++) {
		solve(k, p, q);
	}
	cout << ans << endl;
	return 0;
}
