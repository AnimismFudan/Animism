#include <bits/stdc++.h>
using namespace std;

#define LL long long

int main() {
	srand(time(0));
	freopen("A.in","w",stdout);
	int N = 50000;
	printf("%d\n", N);
	for (int i = 1; i <= N; i++)
		printf("%d %d\n", rand() % 500000 + 1, rand() % 500000 + 1);
	int Q = 50000;
	printf("%d\n", Q);
	for (int i = 1; i <= Q; i++){
		int xl = rand() % 500000 + 1;
		int xr = rand() % 500000 + 1;
		int yl = rand() % 500000 + 1;
		int yr = rand() % 500000 + 1;
		if (xl > xr) swap(xl, xr);
		if (yl > yr) swap(xl, xr);
		if (xl == xr) xr++;
		if (yl == yr) yr++;
		printf("%d %d %d %d\n", xl, yl, xr, yr);
	}
	return 0;
}
