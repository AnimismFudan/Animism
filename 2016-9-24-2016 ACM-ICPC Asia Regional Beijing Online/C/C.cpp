#include <bits/stdc++.h>
#define maxn 101000
using namespace std;

int nex[maxn][27], ans[maxn], mark[maxn];
int fa[maxn],ch[maxn],fail[maxn];
int wp[maxn],sou[maxn],que[maxn];
int n,top,T,num,m;
string pas, now, Ans;
char s[maxn];
string S[maxn];

void add(string s) {
    S[++m] = s;
}

void init() {
    n = 0; m = 0;
}

bool judge(char a) {
    return (a <= 'z' && a >= 'a');
}

int main() {
    freopen("C.in","r",stdin);
    freopen("C.out","w",stdout);
    for (int i = 'a'; i <= 'z'; i++) {
	wp[i] = i - 'a';
	sou[i - 'a'] = i;
    }
    wp[' '] = 26;
    sou[26] = ' ';
    while (true) {
	init();
	n = 0;
	do s[++n] = getchar(); while (s[n] != -1 && s[n] != '#');
	pas = ""; now = "";
	if (s[n] == -1) return 0;
	else {
	    char c;
	    do c = getchar(); while (c == '#');
	}
	for (int u = 1; u <= n; u++) {
	    if (s[u] == ' ') {		
		if (s[u - 1] != ' ') {
		    if (now.length() && pas.length()) {
				add(pas + " " + now);
		    }
		    pas = now;
		    now = "";
		}
	    } else if (!judge(s[u])) {
		if (now.length() && pas.length()) {
		    add(pas + " " + now);
		}
		now = pas = "";
	    } else now = now + s[u];
	}
	
	sort(S + 1,S + m + 1);
	Ans = ""; num = 0;
	for (int i = 1; i <= m; i++) {
	    int j = i;
	    while (S[i] == S[j] && j <= m) j++;
	    j--;
	    if (j - i + 1 > num) {
		num = j - i + 1;
		Ans = S[i];
	    }
	    i = j;
	}
	cout << Ans << ":" << num << endl;
    }
    return 0;
}
