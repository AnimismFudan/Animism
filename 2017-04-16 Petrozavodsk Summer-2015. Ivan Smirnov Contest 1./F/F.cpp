#include <bits/stdc++.h>
#define intl long long
#define comp complex<double>
using namespace std;

comp a;

intl ans;
intl A[1 << 21];
int n;

int main() {
	//freopen("F.in","r",stdin);
	//freopen("F.out","w",stdout);
	scanf("%d",&n);
	for (int i = 0; i < n; i++) scanf("%lld",&A[i])
	for (int i = 1; i < n / 4; i++) {
		int a = i;
		int b = n / 2 - i;
		int c = n / 2 + i;		
		int d = n - i;
		//a + b == c + d;
		ans += abs(A[a] + A[b] - A[c] - A[d]);
	}
	if (n >= 4)
		ans += abs(A[n / 4] - A[n / 4 + n / 2]);
	
	cout << ans << endl;
	return 0;
}
