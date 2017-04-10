#include <bits/stdc++.h>
using namespace std;

struct point {
	int x, y;
	void read() {
		scanf("%d %d",&x,&y);
	}
} dot[1010];

int ans[1010][1010], dt[1010][1010];
int n, top;
int ansx[10100], ansy[10100];

bool cmp(const point &a, const point &b) {
	return (a.x < b.x);
}

void solve(int L, int R) {
	if (L > R) return;
	int mid = (L + R) / 2;
	for (int i = L; i <= R; i++) {
		ans[dot[mid].x][dot[i].y] = 1;		
	}
	solve(L, mid - 1);
	solve(mid + 1, R);
}

int main() {
	//freopen("D.in","r",stdin);
	//freopen("D.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) {
		dot[i].read();
		dt[dot[i].x][dot[i].y] = 1;
	}
	sort(dot + 1, dot + n + 1, cmp);
	solve(1, n);
	for (int i = 1; i <= 1000; i++)
		for (int j = 1; j <= 1000; j++) {
			if (ans[i][j] != dt[i][j]) {
				ansx[++top] = i;
				ansy[top] = j;
			}
		}
	printf("%d\n",top);
	for (int i = 1; i <= top; i++)
		printf("%d %d\n",ansx[i], ansy[i]);
	return 0;
}
