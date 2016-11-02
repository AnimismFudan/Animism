#include <bits/stdc++.h>
using namespace std;

int vis[230],mark[230];
int n;
char s[101000];
string A,A_,B,B_;

string solve() {
	string ans = "";
	for (int t = 126; t >= 32; ) {
		if (!mark[t]) { t--; continue; }
		if (vis[t]) {
			int s = t;
			int cnt = 0;
			while (s >= 32 && (!mark[s] || (mark[s] && vis[s]))) {
				if (mark[s]) cnt++;
				s--;
			}
			if (cnt > 2) {
				s++;
				ans += (char) t;
				ans += '-';
				ans += (char) s;
				t = s - 1;
			} else {
				ans += (char) t;
				t--;
			}
		} else {
			t--;
			continue;
		}
	}
	return ans;
}

int main() {
	freopen("F.in","r",stdin);
	freopen("F.out","w",stdout);
	do {
		s[++n] = getchar();		
	} while (s[n] != -1 && s[n] != '\n');
	s[n--] = 0;
	for (int i = 1; i <= n; i++) {
		vis[s[i]] = 1;
	}
	for (int i = 'a'; i <= 'z'; i++) mark[i] = 1;
	for (int i = 'A'; i <= 'Z'; i++) mark[i] = 1;
	for (int i = '0'; i <= '9'; i++) mark[i] = 1;
	mark[' '] = 1;

	A_ = solve();
	A = "%[";	
	for (int i = A_.length() - 1; i >= 0; i--)
		A += A_[i];
	A += "]";

	for (int i = 32; i <= 126; i++)
		if (mark[i])
			vis[i] ^= 1;
	B_ = solve();
	B = "%[^";
	for (int i = B_.length() - 1; i >= 0; i--)
		B += B_[i];
	B += "]";

	if (B == "%[^]") B = "%[^!]";
	if (A.length() < B.length() || (A.length() == B.length() && A < B) || B == "%[^]")
		cout << A << endl;
	else
		cout << B << endl;
	return 0;
}
