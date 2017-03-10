#include <bits/stdc++.h>
using namespace std;

int f[1 << 20];
int n;
int val[1010000];
int top;

int main() {	
	freopen("just.out","w",stdout);
	n = 11;
	for (int st = 1; st < (1 << n); st++) {
		f[st] = 1;
		for (int u = 0; u < n; u++) {
			if (!(st >> u & 1)) continue;
			f[st] &= f[st ^ (1 << u)];
			for (int k = 1; u - k >= 0; k++) {
				int v = 1 << u;
				for (int j = 1; u - k * j >= 0; j++) {
					v |= (1 << (u - k * j));
					f[st] &= f[st ^ v];
				}
			}
			//break;
		}
		f[st] ^= 1;
	}
	int pas = 0;
	for (int st = 0; st < (1 << n); st++) {
		if (f[st]) continue;
		val[++top] = st;
		continue;
		printf("%d ",f[st]);
		for (int i = (n - 1); i >= 0; i--)
			printf("%d", (st >> i) & 1);
		printf(" %d\n",st - pas);
		pas = st;
	}
	for (int i = 1; i <= top; i++) {
		int st = val[i] ^ val[i - 1];
		for (int i = (n - 1); i >= 0; i--)
			printf("%d", (st >> i) & 1);
		putchar('\n');
	}
	return 0;
}
