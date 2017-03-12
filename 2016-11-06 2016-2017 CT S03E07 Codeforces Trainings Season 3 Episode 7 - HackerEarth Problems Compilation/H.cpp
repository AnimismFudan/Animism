#include <bits/stdc++.h>
#define intl long long
#define lowbit(a) ((a) & (-(a)))
using namespace std;

map<intl,int> mp;

struct Proc { intl d, a, st; } proc[50];

bool cmp(const Proc &a, const Proc &b) {
    return (a.d < b.d);
}

struct ProcL { intl sum, val, st; } A[3010000];

bool cmpL(const ProcL &a, const ProcL &b) {
    return (a.sum > b.sum);
}

struct ProcR { intl fmax,sum,val,st; } B[3010000];

bool cmpR(const ProcR &a, const ProcR &b) {
    return (a.fmax > b.fmax);
}

int Ans[60];
int n,m,N,top,ta,tb,tp;
intl ans,ansST;
intl st[4010000],Val[4010000],ts[4010000];
intl sing;

void dfs(int u, intl sum, intl val, intl st) {
    if (u > n) {
		A[++ta] = (ProcL) { sum, val, st };
		return;
    }
    if (sum + 1LL >= proc[u].d)
		dfs(u + 1, sum + proc[u].d, val + proc[u].a, st | proc[u].st);
    dfs(u + 1, sum, val, st);   
}

void Dfs(int u, intl fmax, intl sum, intl val, intl st) {
    if (u > N) {
		B[++tb] = (ProcR) { fmax, sum, val, st };
		return;
    }
    Dfs(u + 1, max(fmax, proc[u].d - sum - 1LL), sum + proc[u].d, val + proc[u].a, st | proc[u].st);
    Dfs(u + 1, fmax, sum, val, st);
}

void solve() {
    for (int i = 1; i <= ta; i++) {
		mp[A[i].sum] = 1;
    }
    for (map<intl,int> :: iterator i = mp.begin(); i != mp.end(); i++) {
		i -> second = ++top;
		Val[top] = i -> first;
    }
    int v = 1;
    for (int i = 0; i <= top; i++)
		st[i] = -1LL << 60;
    for (int u = 1; u <= tb; u++) {
		while (v <= ta && A[v].sum >= B[u].fmax) {
			for (int i = top - mp[A[v].sum] + 1; i <= top; i += lowbit(i)) {
				if (st[i] < A[v].val) { 
					st[i] = A[v].val;
					ts[i] = A[v].st;
				}
			}
			v++;
		}
		intl san = sing - B[u].sum;
		int k;
		if (san < Val[1]) k = 1;
		else if (san > Val[top]) k = top + 1;
		else {
			int L = 1, R = top;
			while (L < R) {
				int mid = (L + R) >> 1;
				if (Val[mid] >= san) R = mid;
				else L = mid + 1;
			}
			k = L;
		}
		if (k > top) continue;
		intl js = -1LL << 60, ST = 0;
		for (int i = top - k + 1; i > 0; i -= lowbit(i)) {
			if (js < st[i]) {
				js = st[i];
				ST = ts[i];
			}
		}
		if (ans < js + B[u].val) {
			ans = js + B[u].val;
			ansST = ST | B[u].st;
		}	
    }
}

int main() {
    scanf("%d %lld",&N,&sing);
    for (int i = 1; i <= N; i++) {
		int a,b;
		scanf("%d %d",&a,&b);
		proc[i] = (Proc) { a, -b, 1LL << i };
    }
    n = N / 2;
    m = N - n;
    sort(proc + 1, proc + N + 1, cmp);
    dfs(1, 0, 0, 0);
    Dfs(n + 1, -1LL << 60, 0, 0, 0);
    sort(A + 1, A + ta + 1, cmpL);
    sort(B + 1, B + tb + 1, cmpR);
    ans = -1LL << 60;
    solve();
    //cout << ans << endl;
    for (int i = 1; i <= N; i++) {
		if ((ansST >> i) & 1LL) Ans[++tp] = i;
    }
    if (!tp) { printf("-1"); return 0; }
    printf("%d\n",tp);
    for (int i = 1; i < tp; i++)
		printf("%d ",Ans[i]);
    printf("%d\n",Ans[tp]);
    return 0;
}
