#include <bits/stdc++.h>
using namespace std;

char s[1010000];
int n;
int top;
int val[1010000];

bool isthis(char a) {
	if (a <= 'z' && a >= 'a') return true;
	if (a <= 'Z' && a >= 'A') return true;
	return false;
}

int judge(int u) {
	if (s[u] < 'A' || s[u] > 'Z') return 0;
	if (!isthis(s[u + 1])) return 0;
	for (u++; isthis(s[u]); u++) {
		if (s[u] <= 'Z' && s[u] >= 'A') return 0;
	}
	return u;
}

int main() {
	freopen("abbreviation.in","r",stdin);
	freopen("abbreviation.out","w",stdout);
	do s[++n] = getchar(); while (s[n] != -1);
	for (int i = 1; i < n; i++) {	
		if (judge(i)) {
			int L = i;
			int R = L;
			top = 0;
			for (int u = i; true ;) {
				int v = u;
				u = judge(u);
				if (u != 0) { val[++top] = v; R = u; }
				if (u == 0 || s[u] != ' ') break;
				else u++;
			}
			if (top > 1) {
				for (int i = 1; i <= top; i++) putchar(s[val[i]]);
				putchar(' ');
				putchar('(');
				for (int i = L; i < R; i++) putchar(s[i]);
				putchar(')');
			} else {
				for (int i = L; i < R; i++) putchar(s[i]);
			}
			i = R - 1;
		} else if (isthis(s[i])) {
			while (i < n && isthis(s[i])) putchar(s[i++]);
			i--;
		} else putchar(s[i]);
	}
	return 0;
}
