#include <bits/stdc++.h>
using namespace std;


vector <int> vec[1010];
int n,m,mark[1010],u,T,tp[1010],top;
char s[1001000],S[1001000],sing[1001000];
int nex[1010000];

bool cmp(char a, char b) {
    return (mark[a] < mark[b]);
}

int main() {
    for (scanf("%d",&T); T; T--) {
	scanf("%s",s + 1);
	n = strlen(s + 1);
	mark['.'] = (top = 1);
	m = 0;
	for (int i = 'A'; i <= 'Z'; i++) mark[i] = ++top;
	for (int t = 1; t <= n; t++) {
	    if (s[t] <= '9' && s[t] >= '0') {
		int k = 0;
		do {
		    k = k * 10 + (s[t] - '0');
		    t++;
		} while (s[t] <= '9' && s[t] >= '0');
		
		for (int i = 1; i < k; i++) {
		    m++;
		    S[m] = S[m - 1];
		}
		t--;
	    } else
		S[++m] = s[t];
	}

	S[m + 1] = sing[m + 1] = 0;
	for (int i = 1; i <= m; i++) sing[i] = S[i];	
	sort(sing + 1, sing + m + 1, cmp);
	for (int i = 1; i <= top; i++) {
	    vec[i].clear();
	    tp[i] = 0;
	}
	
	for (int i = 1; i <= m; i++) {
	    vec[mark[S[i]]].push_back(i);
	}
	
	for (int i = 1; i <= m; i++) {
	    nex[i] = vec[mark[sing[i]]][tp[mark[sing[i]]]++];
	    //tp[mark[sing[i]]]++;
	    if (S[i] == '.') u = i;
	}

	u = nex[u];
	putchar(S[u]);
	for (int i = nex[u]; i != u; i = nex[i]) putchar(S[i]);
	
	putchar('\n');
    }
    return 0;
}