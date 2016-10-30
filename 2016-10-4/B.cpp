#include <bits/stdc++.h>
using namespace std;

#define LL long long

LL A[101],B[101];
LL T,t,n,a,b;

int main() {
    freopen("B.in","r",stdin);
    freopen("B.out","w",stdout);
    for (scanf("%lld",&T); T; T--) {
	scanf("%lld",&n);
	for (int i = 1; i <= n; i++)
	    scanf("%lld",&A[i]);
	for (int i = 1; i <= n; i++)
	    scanf("%lld",&B[i]);
	b = B[n]; a = A[n];
	for (int i = n - 1; i >= 1; i--) {
	    b += a * A[i];
	    a *= B[i];
	    swap(a, b);
	    LL k = __gcd(a, b);
	    a /= k;
	    b /= k;
	}
	LL k  = __gcd(a, b);
	a /= k;
	b /= k;
	printf("Case #%lld: %lld %lld\n",++t,b,a);
    }
    return 0;
}
