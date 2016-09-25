#include <bits/stdc++.h>
using namespace std;

struct str { int k; string s; };

struct cmp {
    bool operator () (str a, str b) {
	return (a.k < b.k || (a.k == b.k && a.s < b.s));
    }
};
    
map<str,int,cmp> nex[10100];

typedef map<str,int,cmp> :: iterator poi;

int T,top;
string s,S;

int add(int u,int k, string s) {
    int v;
    if (!(v = nex[u][(str) { k, s }])) {
	nex[u][(str) { k, s }] = ++top;
	v = top;
    }
    return v;
}

void dfs(int u, int dep, string s) {
    if (u != 1) {
	for (int i = 1; i < dep; i++)
	    for (int j = 1; j <= 4; j++)
		putchar(' ');
	int k = s.length();
	for (int i = 0; i < k; i++)
	    putchar(s[i]);
	putchar('\n');
    }
    for (poi i = nex[u].begin(); i != nex[u].end(); i++) {
	dfs(i -> second, dep + 1, i -> first.s);
    }
}

bool judge(char c) {
    return ((c <= 'Z' && c >= 'A') || (c <= '9' && c >= '0') || (c == ' '));
}

void init() {
    top = 1;
}

int main() {
    freopen("A.in","r",stdin);
    freopen("A.out","w",stdout);
    while (true) {
	init();
	char ch;
	while (true) {
	    //do ch = getchar(); while(!judge(ch) && ch != -1);
	    //if (ch == -1) return 0;	
	    //S = "";
	    if (!getline(cin, S)) return 0;
	    //cout << S << endl;
	    //int u = 1;
	    //S = S + ch;
	    /*while (true) {
		ch = getchar();
		if (ch == '\n') break;
		else S = S + ch;
		}*/

	    if ((int) S.length() == 1 && S[0] == '0') break;
	    int u = 1;
	    s = "";
	    for (int i = 0; i < (int) S.length(); i++) {
	        if (S[i] == '/') {
		    u = add(u, 0, s);
		    s = "";
		} else
		    s = s + S[i];
	    }
	    add(u, 1, s);
	}
	printf("Case %d:\n",++T);
	dfs(1, 0, "");
	for (int i = 1; i <= top; i++) nex[i].clear(); 
    }
    return 0;
}
