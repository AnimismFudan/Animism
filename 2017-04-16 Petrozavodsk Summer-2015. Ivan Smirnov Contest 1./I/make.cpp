#include <bits/stdc++.h>
#include <sys/timeb.h>
#define R(a) (abs(rand() * rand() + rand()) % (a) + 1)

int main() {
	struct timeb t; ftime(&t); srand(t.millitm + t.time * 10000);
	freopen("I.in","w",stdout);
	int n = 5000;
	printf("%d\n",n);
	for (int i = 1; i <= n; i++)
		printf("%d %d\n",R(10000),R(10000));
	printf("1000.0\n");
	return 0;
}
