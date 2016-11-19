#include <bits/stdc++.h>
using namespace std;

int ans[101000];
int n,a,b,c;

bool judge(int u, int a, int b, int c) {
	if (c & 1) return false;
	if (a < 0 || b < 0 || c < 0 || a > n / 2 || b > n / 2 || c > n / 2)
		return false;
	if (a + b + c != n / 2) return false;
	if (!c && (a && b)) { return false; }
	int now = (a || c) ? 0 : 1;	
	for (int i = 1; i <= n / 2; i++) {
		ans[u] = now;
		if (now == 0 && a)
			a--;
		else if (now == 0)
			c--, now = 1;
		else if (now == 1 && b)
			b--;
		else
			c--, now = 0;
		u += 2;
	}
	return true;
}

int main() {
	freopen("boysgirls.in","r",stdin);
	freopen("boysgirls.out","w",stdout);
	scanf("%d %d %d",&n,&a,&b);
	c = a + b - n;
	a -= c; b -= c;
	if (a < 0 || b < 0 || c < 0 || a > n || b > n || c > n) {
		printf("Impossible\n");
		return 0;
	}
	if (c & 1) {
		printf("Impossible\n");
		return 0;
	}
	if (n & 1) {
		int u = 1, now;
		if (a || c) now = 0;
		else now = 1;
		int bg = now;
		if (!c && (a && b)) { printf("Impossible\n"); return 0; }
		for (int i = 1; i <= n; i++) {
			ans[u] = now;
			if (now == 0 && a)
				a--;
			else if (now == 0)
				c--, now = 1;
			else if (now == 1 && b)
				b--;
			else
				c--, now = 0;
			u += 2;
			if (u > n) u -= n;
		}
	} else {
		if (!c) {
			if (a && b) { 
				if (!judge(1,a,0,0) || !judge(2,0,b,0)) { printf("Impossible\n"); return 0; }
			}
			else if (a) {
				if (!judge(1,a / 2,0,0) || !judge(2,a - a / 2,0,0)) { printf("Impossible\n"); return 0; }			
			} else {
				if (!judge(1, 0, b / 2,0) || !judge(2,0, b - b / 2,0)) { printf("Impossible\n"); return 0; }	
			}
		} else if (c == 2) {
			if (a > b) {
				if (!judge(1, n / 2, 0, 0) || !judge(2, a - n / 2, b, 2)) { printf("Impossible\n"); return 0; }
			} else {
				if (!judge(1, 0, n / 2, 0) || !judge(2, a, b - n / 2, 2)) { printf("Impossible\n"); return 0; }				
			}
		} else {
			int A,B,C;
			C = c / 2;
			if (C & 1) C--;
			A = min(a, n / 2 - C);
			B = max((n / 2 - C) - a, 0);
			if (!judge(1, A, B, C) || !judge(2, a - A, b - B, c - C)) {
				printf("Impossible\n");
				return 0;
			}
		}
	}
   
	if (a < 0 || b < 0 || c < 0) { printf("Impossible\n"); return 0; }
	for (int i = 1; i <= n; i++)
		if (ans[i]) putchar('G');
		else putchar('B');
	return 0;
}
