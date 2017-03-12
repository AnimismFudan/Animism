#include <bits/stdc++.h>
#define maxn 10010
using namespace std;

char s[maxn];
int n, ans;
int sg[maxn];
int g[maxn],mask[maxn];

void prepare(int n) {
	sg[0] = 1;	
	for (int u = 1; u < n; u++) {
		for (int i = 0; i <= 5000; i++) g[i] = 0;
		g[0] = 1;
		for (int k = 1; u - k >= 0; k++) {
			int js = 0;
			for (int j = 1; u - j * k >= 0; j++) {
				js ^= sg[u - j * k];
				g[js] = 1;
			}
		}
		for (int i = 0; i <= 5000; i++)
			if (!g[i]) {
				sg[u] = i;
				break;
			}
	}
}

void print() {
	for (int i = 1; i <= n; i++) {
		if (mask[n - i]) putchar(s[i] == 'N' ? 'S' : 'N');
		else putchar(s[i] == 'N' ? 'N' : 'S');
	}
	putchar('\n');
	exit(0);
}

int main() {
	//freopen("J.in","r",stdin);
	//freopen("J.out","w",stdout);
	scanf("%s",s + 1);
	n = strlen(s + 1);
	prepare(3000);
	//for (int i = 0; i < 3000; i++)
	//	printf("%d\n",sg[i]);
	ans = 0;
	for (int i = 0; i < n; i++)
		if (s[n - i] == 'N') ans ^= sg[i];
	if (ans) {
		bool flag = false;
		for (int u = 0; u < n && !flag; u++) {
			if (s[n - u] == 'S') continue;
			//for (int i = 0; i < n; i++) mask[i] = 0;
			for (int k = 1; !flag && u - k >= -1; k++) {
				int judge = ans;	
				for (int t = 0; !flag && u - k * t >= 0; t++) {
					mask[u - k * t] = 1;
					judge ^= sg[u - k * t];
					if (!judge)
						print();
				}
				for (int t = 0; !flag && u - k * t >= 0; t++)
					mask[u - k * t] = 0;
			}
		}
	}
	else printf("NIE\n");
	return 0;
}
