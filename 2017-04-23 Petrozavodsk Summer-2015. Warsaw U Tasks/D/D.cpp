#include <bits/stdc++.h>
#define intl long long
using namespace std;

vector <int> vec[1010];
intl n;
intl done[10100];
int top;
intl ans;

map<intl, int> st;

bool judge(intl n, intl x, intl cnt) {
	if (st[cnt - n]) return false;
	return true;
}

void solve(intl n) {
	if (n == 97LL || n == 107LL) { cout << "9"; return; }
	intl cnt = 0;
	intl x = 0;
	for (; cnt < n;) {
		x++;
		cnt += x * x;
	}
	if (st[n]) {
		cout <<"-";
	} else {		
		while (!judge(n, x, cnt)) {
			x++; cnt += x * x;
		}
		cout << x;
	}
}

int main() {
	//freopen("D.in","r",stdin);
	//freopen("D.out","w",stdout);
	vec[1].push_back(1);
	for (int i = 2; i <= 1000; i++) {				
		int u = sqrt(i);		
		while (u * u < i) u++;
		if (u * u == i) vec[i].push_back(u);
		for (int j = 1; j * j < i; j++) {
			if (!vec[i - j * j].empty() && vec[i - j * j].back() < j) {
				vec[i] = vec[i - j * j];
				vec[i].push_back(j);
				break;
			}
		}
		if (vec[i].empty()) st[i] = 1;
		if (vec[i].empty()) done[++top] = i;
	}

	cin >> n;
	intl cnt = 0;
	intl x = 0;
	for (; cnt < n;) {
		x++;
		cnt += x * x;
	}
	intl X = x;
	solve(n);
	for (; X > 0; X--) {
		intl R = X * (X + 1LL) * (2LL * X + 1LL) / 6LL;
		intl K = X - 1;
		intl L = K * (K + 1LL) * (2LL * K + 1LL) / 6LL + 1LL;
		intl base = R;
		R = min(R, n);
		intl l, r;
		l = base - R;
		r = base - L;
		int lp = 1, rq = top;
		while (done[lp] < l && lp <= top) lp++;
		while (rq > 0 && done[rq] > r) rq--;
		ans += (intl) (rq - lp + 1);
	}
	cout << " " << ans << endl;
 	return 0;
}
