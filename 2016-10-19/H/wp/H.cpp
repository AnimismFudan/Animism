#include <bits/stdc++.h>
using namespace std;

int nex[601000][64];
int top,head,n,m,q,T,L[601000],R[601000];
char s[10100000];
int mark[10100],tp;

void init() {
	head = top = tp = 1;
	memset(nex[1], 0, sizeof(nex[1]));
}

int add(int u, int v) {
	if (!nex[u][v]) {
		nex[u][v] = ++top;
		L[top] = R[top] = 0;
		memset(nex[top], 0, sizeof(nex[top]));
	}
	return nex[u][v];
}

void Add(int head) {
	if (s[tp + 1] == '}') { tp++; return; }
	while (true) {
		int u = head;
		for (tp += 2; tp <= n && s[tp] != '"'; tp++)
			u = add(u, mark[s[tp]]);
		if (tp > n) { printf("orz"); exit(0); }
		tp += 2;
		if (s[tp] == '{') {
			L[u] = tp;
			int v = add(u, mark['.']);
			Add(v);
			R[u] = tp;
		} else {
			L[u] = tp;
			tp++;
			int v = u;
			while (tp <= n && s[tp] != '"') {
				v = add(v, mark[s[tp]]);
				tp++;
			}
			R[u] = tp;
		}
		tp++;
		if (tp > n) { printf("orz"); exit(0); }
		if (s[tp] == '}') break;		
	}
}

bool judge(char a) {
	return (a == '"' || a == '.' || (a <= 'z' && a >= 'a') || (a <= 'Z' && a >= 'A') ||
			(a <= '9' && a >= '0'));
}

int main() {
	freopen("H.in","r",stdin);
	freopen("H.out","w",stdout);
	int js = 0;
	for (int i = 'a'; i <= 'z'; i++) mark[i] = ++js;
	for (int i = 'A'; i <= 'Z'; i++) mark[i] = ++js;
	for (int i = '0'; i <= '9'; i++) mark[i] = ++js;
	mark['.'] = 0;
	for (scanf("%d",&T); T; T--) {
		scanf("%s",s + 1);
		n = strlen(s + 1);
		if (n > 1000000) { printf("orz"); return 0; }
		init();
		Add(head);
		//if (n > 100) return 0;
		for (scanf("%d",&q); q; q--) {
			char ch;
			do ch = getchar(); while (!judge(ch));
			int u = head;
			do {
				if (ch != '"')
					u = nex[u][mark[ch]];
				ch = getchar();
			} while (judge(ch));
			
			if (L[u]) {
				for (int i = L[u]; i <= R[u]; i++) putchar(s[i]);
				putchar('\n');
			} else
				puts("Error!");
		}
	}
	return 0;
}

