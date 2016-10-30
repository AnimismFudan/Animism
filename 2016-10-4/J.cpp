#include <bits/stdc++.h>
using namespace std;

struct bignum {
    int v[1010],n;

    void set(char *s, int m) {
	n = m;
	for (int i = 1; i <= n; i++)
	    v[i] = s[i] - '0';
    }

    void operator -= (bignum B) {
	bignum A;
	memcpy(A.v, v, sizeof(v));
	A.n = n;
	reverse(A.v + 1, A.v + A.n + 1);
	reverse(B.v + 1, B.v + B.n + 1);
	int m = max(A.n, B.n);
	memset(v,0,sizeof(v));
	for (int i = 1; i <= m; i++) {
	    v[i] = A.v[i] - B.v[i];
	}
	for (int i = 1; i <= m; i++) {
	    if (v[i] < 0) {
		v[i] += 10;
		v[i + 1]--;
	    }
	}
	while (!v[n] && n) n--;
	reverse(v + 1, v + n + 1);
	return;
    }

    void proc(int m) {
	for (int i = n + 1; i <= 1000; i++)
	    v[i] = 0;
	reverse(v + 1, v + n + 1);
	v[1]--;
	for (int i = 1; i <= n; i++) {
	    if (v[i] < 0) {
		v[i + 1]--;
		v[i] += 10;
	    }
	}
	while(!v[n] && n) n--;
	if (n * 2 <= m) m = n * 2;
	reverse(v + 1, v + n + 1);
	for (int i = 1; i <= n; i++)
	    v[m - i + 1] = v[i];
	n = m;
    }

    bool judge() {
	return (!n);
    }

    void print() {
	for (int i = 1; i <= n; i++)
	    printf("%d",v[i]);
	putchar('\n');
    }

    bool special() {
	return (n == 2 && v[1] == 1);
    }
} A,B,ans[60];

bool operator <= (bignum A, bignum B) {
    if (A.n < B.n) return true;
    if (A.n > B.n) return false;
    for (int i = 1; i <= A.n; i++) {
	if (A.v[i] < B.v[i]) return true;
	if (A.v[i] > B.v[i]) return false;
    }
    return true;
}

int t,T,n,top;
char s[1010];

int main() {
    freopen("J.in","r",stdin);
    freopen("J.out","w",stdout);
    for (scanf("%d",&T); T; T--) {
	scanf("%s",s + 1);
	n = strlen(s + 1);
	A.set(s, n);
	top = 0;
	while(!A.judge()) {
	    int m = (A.n + 1) / 2;
	    for (int i = 1; i <= m; i++) {
		B.v[i] = B.v[A.n - i + 1] = A.v[i];
	    }
	    B.n = A.n;
	    if (A.special()) {
		B.n = 1;
		memset(B.v,0,sizeof(B.v));
		B.v[1] = 9;		
		ans[++top] = B;
		A -= B;
	    }
	    else if (B <= A) {
		A -= B;
		ans[++top] = B;
		continue;
	    } else {
		B.n = (A.n + 1) / 2;
		B.proc(A.n);
		ans[++top] = B;
		A -= B;
		continue;
	    }
	}
	printf("Case #%d:\n",++t);
	printf("%d\n",top);
	for (int i = 1; i <= top; i++)
	    ans[i].print();
    }
    return 0;
}
