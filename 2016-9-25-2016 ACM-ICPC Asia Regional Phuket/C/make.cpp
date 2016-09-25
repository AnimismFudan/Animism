#include <bits/stdc++.h>
#include <sys/timeb.h>
#define R(a) (abs(rand() * rand() + rand()) % (a) + 1)
using namespace std;
int T,n,m,q;

int main() {
    freopen("C.in","w",stdout);
    struct timeb t; ftime(&t); srand(t.millitm + t.time * 10000);
    T = 1;
    for (printf("%d\n",T); T; T--) {
	n = 100000; m = n + 50; q = 50000;
	printf("%d %d %d\n",n,m,q);
	for (int i = 2; i <= n; i++) {
	    printf("%d %d %d\n",R(i - 1),i,R(10000));
	}
	for (int i = n; i <= m; i++)
	    printf("%d %d %d\n",R(n), R(n), R(10000));
	for (int i = 1; i <= q; i++)
	    printf("%d %d\n",R(n), R(n));
    }
    return 0;
}
