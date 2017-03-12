#include <bits/stdc++.h>
#define maxn 101000
#define lowbit(a) ((a) & (-(a)))
using namespace std;

int ts[maxn],ST[maxn * 21],TS[maxn * 21];
int mark[maxn * 10];
int st[maxn][20],f[maxn][20];
int n,m,q;
int A[maxn];

int gcd(int a,int b) {
    return b ? gcd(b, a % b) : a; 
}

struct str { int L,R,num,ans; } ques[maxn];

bool cmp(const str &a, const str &b) {
    return (a.L < b.L);
}

bool pmc(const str &a, const str &b) {
    return (a.num < b.num);
}

void prepare() {
    for (int i = 1; i < n; i++) {
	st[i][0] = i + 1;
	f[i][0] = gcd(A[i], A[i + 1]);
    }

    for (int j = 1; j <= 20; j++)
	for (int i = 1; i <= n; i++) {
	    st[i][j] = st[st[i][j - 1]][j - 1];
	    f[i][j] = gcd(f[i][j - 1], f[st[i][j - 1]][j - 1]);
	}    
}

void add(int val,int u) {
    ST[++q] = u; TS[q] = val;
    if (mark[val] && mark[val] < u) return;
    if (mark[val])
	for (int i = mark[val]; i <= n; i += lowbit(i)) ts[i]--;
    mark[val] = u;
    for (int i = mark[val]; i <= n; i += lowbit(i)) ts[i]++;
    return;
}

void Add(int u) {
    int now = A[u];
    add(now, u);
    int k,pas = 20;
    while (u <= n) {	
	k = pas;
	while (true) {
	    while (k >= 0 && !st[u][k]) k--;
	    while (k >= 0 && f[u][k] != now) k--;
	    if (k < 0) break;
	    u = st[u][k];
	}
	u++;
	if (u <= n) {
	    now = gcd(now, A[u]);
	    add(now, u);
	}
    }
}

int main() {
    freopen("1002.in","r",stdin);
    freopen("1002.out","w",stdout);
    while (scanf("%d %d",&n,&m) != EOF) {
	for (int i = 1; i <= n; i++) {
	    scanf("%d",&A[i]);
	    mark[A[i]] = 0;
	}
	prepare();
	for (int i = 1; i <= m; i++) ques[i].ans = 0;
	for (int i = 1; i <= m; i++) {
	    scanf("%d %d",&ques[i].L,&ques[i].R);
	    ques[i].num = i;
	}
	sort(ques + 1,ques + m + 1,cmp);

	int pas = n;
	for (int t = m; t >= 1; t--) {
	    for (; pas >= ques[t].L; pas--) {
		Add(pas);
	    }
	    for (int i = ques[t].R; i; i -= lowbit(i)) ques[t].ans += ts[i]; 
	}
	
	sort(ques + 1,ques + m + 1,pmc);
	for (int i = 1; i <= m; i++) printf("%d\n",ques[i].ans);
	for (; q; q--) {
	    for (int i = ST[q]; i <= n; i += lowbit(i))
		ts[i] = 0;
	    mark[TS[q]] = 0;
	}
    }
    return 0;
}
