#include <bits/stdc++.h>
#define intl long long
#define maxn 4010000
using namespace std;

map<intl,intl> st;

intl n, m, a, b, p, ans;
intl Lb[maxn], Rb[maxn];
int top;
char s[maxn];

bool judge(intl val) {
	if (!top) return false;
	if (val < Lb[1]) return false;
	int L = 1, R = top;
	while (L < R) {
		int mid = (L + R) / 2 + 1;
		if (Lb[mid] <= val) L = mid;
		else R = mid - 1;
	}
	if (Rb[L] >= val) return true;
	return false;
}

int main() {
	//freopen("C.in","r",stdin);
	//freopen("C.out","w",stdout);
	cin >> n >> a >> b >> p >> m;
	scanf("%s", s);
	for (int i = 0; i < m; i++) {
		intl L, R;
		if (s[i] == '0') {
			L = (-a * (intl)i) % n;
			R = L + p - 1LL;
		}
		else {
			L = (((-a * (intl)i) + p) % n + n) % n - n;
			R = L + (n - p) - 1LL;
		}
		if (R < 0) {
			L += n;
			R += n;
		}
		st[max(L, 0LL)]++;
		st[R + 1]--;
		if (L + n < n) {
			L += n;
			R += n;
			st[L]++;
			st[min(n, R + 1)]--;
		}
	}
	intl pas = 0;
	intl cnt = 0;
	for (auto i = st.begin(); i != st.end(); i++) {
		if (cnt == (intl) m) {
			Lb[++top] = pas;
			Rb[top] = i -> first - 1LL;
		}
		cnt += i -> second;
		pas = i -> first;
	}
	if (cnt == (intl) m) {
		Lb[++top] = pas;
		Rb[top] = n - 1LL;
	}
	for (int i = 1; i <= top; i++)
		ans += Rb[i] - Lb[i] + 1LL;
	for (intl i = n - (intl) m + 1; i < n; i++) {
		intl val = (a * i + b) % n;
		if (judge(val)) ans--;
	}
	cout << ans << endl;
	return 0;
}
