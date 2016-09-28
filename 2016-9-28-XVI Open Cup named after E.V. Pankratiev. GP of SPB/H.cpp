#include <bits/stdc++.h>
#define intl long long
using namespace std;

intl n;
int T;

int main() {
	//freopen("H.in","r",stdin);
	//freopen("H.out","w",stdout);
	for (scanf("%d",&T); T; T--) {
		cin >> n;
		for (int i = 2; i <= n; i++) {
			if (!(n % i)) { n = -1; break; }
			n -= n / i;
		}
		cout << n << endl;
		   
	}
	return 0;
}
