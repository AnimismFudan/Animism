#include <bits/stdc++.h>
using namespace std;

int n;
int f[101000];

int main() {
	freopen("just.out","w",stdout);
	n = 100000;
	for (int i = 1; (3 * i) * (i + 1) + 1 <= n; i++)
		f[(3 * i) * (i + 1) + 1]= 1;

	for (int i = 1; i <= n; i++) {
		if (f[i] == 1) continue;
		f[i] = i;
		for (int j = 1; j < i; j++)
			f[i] = min(f[i], f[j] + f[i - j]);
	}

	int pas;
	for (int i = 1; i <= n; i++) printf("%d\n", f[i]);
	return 0;
}
