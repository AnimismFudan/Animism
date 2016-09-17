#include <bits/stdc++.h>
using namespace std;
int T;
long long L,R;

int main() {
    while (scanf("%lld %lld",&L,&R) != EOF) {
	if (L == 0LL && R == 1LL) printf("0\n");
	else if (!L) printf("%lld\n",(R + 1LL) / 2LL);
	else if (L == 1LL && R == 1LL) printf("0\n");
	else if (L == 1LL && R == 2LL) printf("1\n");
	else if (L == 2LL && R == 2LL) printf("1\n");
	else if (R - L <= 3LL) printf("2\n");
	else printf("%lld\n",(R - L - 2LL) / 2LL + 2LL);
    }
}
