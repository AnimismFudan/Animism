#include <bits/stdc++.h>
#include <sys/timeb.h>
using namespace std;

int n = 10000;
int v[10100],u[10100];

void sets(int *u, int k) {
	for (int i = 0; i < n; i++) u[i] = 0;
	for (int j = 1; j <= k; j++) {
		int x;
		do x = abs(rand()) % n;
		while (u[x]);
		u[x] = 1;
	}
	return;
}

bool solve() {
	scanf("%d",&n);
	int js = 0;
	for (int k = n; k >= 1; k /= 2) {
		for (int i = 1; i <= 10; i++) {
			sets(u, k);
			for (int i = 0; i < n; i++) printf("%d",u[i]);
			printf("\n");
			fflush(stdout);
			char ch;
			do scanf("%c",&ch); while (ch != '-' && ch != '+');
			if (ch == '+') exit(0);
			js++;
		}
	}
	return false;
}

int main() {
	struct timeb t; ftime(&t); srand(t.millitm + t.time * 10000);
	//sets(v, 100);
	solve();
	return 0;
}
