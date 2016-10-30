#include <bits/stdc++.h>
#define intl long long
using namespace std;

int T;
int t;
int c[33];
intl C[33][33];
intl co[33][33];
intl ans;

intl gcd(intl a,intl b) {
    return (b? gcd(b, a % b) : a);
}

struct num {
    intl a,b;

    void operator -= (num B) {
	num A; A.a = a; A.b = b;
	a = A.a * B.b - B.a * A.b;
	b = A.b * B.b;
	intl k = gcd(abs(a), abs(b));
	if (!k) return;
	a /= k;
	b /= k;
    }

    void operator /= (intl B) {
	b *= B;
	intl k = gcd(abs(a), abs(b));
	if (!k) return;
	a /= k;
	b /= k;  
    }
    void operator *= (intl B) {
	a *= B;
	intl k = gcd(abs(a), abs(b));
	if (!k) return;
	a /= k;
	b /= k;  
    }

    void set(intl v) {
	a = v;
	b = 1;
    }
} A[110];
    
int main() {
    freopen("H.in","r",stdin);
    freopen("H.out","w",stdout);
    for (int i = 0; i <= 30; i++) {
	C[i][0] = 1;
	for (int j = 1; j <= i; j++)
	    C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
    
    for (scanf("%d",&T); T; T--) {
	scanf("%d",&t);
	for (int i = 0; i <= t; i++)
	    scanf("%d",&c[i]);
	for (int i = 1; i <= t + 1; i++)
	    for (int j = 0; j < i; j++)
		co[i][j] = C[i][j];
	for (int i = t + 1; i >= 1; i--) {
	    A[i].set(c[i - 1]);
	    for (int j = i + 1; j <= t + 1; j++) {
		num js = A[j];
		js *= co[j][i - 1];
		A[i] -= js;
	    }
	    A[i] /= co[i][i - 1];
	}
	ans = abs(c[0]);
	for (int i = 1; i <= t + 1; i++)
	    ans += abs(A[i].a);
	cout << ans << endl;
    }
    return 0;
}
