#include <bits/stdc++.h>
using namespace std;

int ans[1010][1010], dot[1010][1010];
int X[1010], Y[1010];
int n, top;
int ansx[10100], ansy[10100];

void solve(int x1, int x2, int y1, int y2) {
	int x = 0, y = 0;
	for (int i = 1; i <= n; i++) {
		if (X[i] < x2 && X[i] > x1 && Y[i] < y2 && Y[i] > y1) {
			x = X[i]; y = Y[i];
			break;
		}
	}
	if (!x) return;
	ans[x1][y] = ans[x2][y] = ans[x][y1] = ans[x][y2] = 1;
	solve(x1, x, y1, y);
	solve(x1, x, y, y2);
	solve(x, x2, y1, y);
	solve(x, x2, y, y2);
	return;
}

int main() {
	freopen("D.in","r",stdin);
	freopen("D.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d",&X[i],&Y[i]);
		dot[X[i]][Y[i]] = ans[X[i]][Y[i]] = 1;

	}
	
	ans[1][1000] = ans[1000][1] = ans[1][1] = ans[1000][1000] = 1;
	solve(1, 1000, 1, 1000);
	top = 0;
	for (int i = 1; i <= 1000; i++)
		for (int j = 1; j <= 1000; j++) {
			if (dot[i][j] != ans[i][j]) {
				ansx[++top] = i;
				ansy[top] = j;
			}
		}
	printf("%d\n",top);
	for (int i = 1; i <= top; i++)
		printf("%d %d\n",ansx[i], ansy[i]);
	return 0;
}
