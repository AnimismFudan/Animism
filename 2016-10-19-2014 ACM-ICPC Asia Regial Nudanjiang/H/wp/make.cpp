#include <bits/stdc++.h>
using namespace std;

int T;

void print(int dep) {
	if (dep == 1000) {
		putchar('"');
		printf("aaaaaaaaaaaaaaaaaaaaaa");
		putchar('"');
		return;
	}
	putchar('{');
	putchar('"');
	printf("aaaaaaaaaaaaaaaaaaaa");
	putchar('"');
	putchar(':');
	print(dep + 1);
	putchar('}');
}

int main() {
	freopen("H.in","w",stdout);
	T = 10;
	for (printf("%d\n",T); T; T--) {
		print(1);
		printf("\n1\n");
		printf("aaaaaaaaaaaaaaaaaaaa.aaaaaaaaaaaaaaaaaaaa.aaaaaaaaaaaaaaaaaaaa\n");
	}
	return 0;
}
