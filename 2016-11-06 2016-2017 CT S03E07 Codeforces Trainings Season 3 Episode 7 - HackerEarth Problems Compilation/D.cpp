#include <bits/stdc++.h>
#define intl long long
using namespace std;

struct Proc {
    int p, L, R, k, mark;
} proc[201000];

int n,m,top,A[101000];
intl Ans[101000],cnt[101000];

void add(int p, int L, int R, int k) {
    if (L > R) return;
    proc[++top] = (Proc) { p, L, R, k, 0 };
}

bool cmp(const Proc &a, const Proc &b) {
    return (a.mark < b.mark || (a.mark == b.mark && a.R < b.R));
}

void solve() {
    int base = sqrt(top + 1) + 1;
    for (int i = 1; i <= top; i++)
		proc[i].mark = proc[i].L / base;
    sort(proc + 1, proc + top + 1, cmp);
    int PL = 0, PR = 0;
    cnt[0] = 1;
    intl ans = 1;
    for (int u = 1; u <= top; u++) {
		int L = proc[u].L, R = proc[u].R;
		int v;
		while (L < PL) {
			PL--;
			v = A[PL];
			ans -= cnt[v] * cnt[v];
			cnt[v]++;
			ans += cnt[v] * cnt[v];
		}
		while (L > PL) {
			v = A[PL];
			ans -= cnt[v] * cnt[v];
			cnt[v]--;
			ans += cnt[v] * cnt[v];
			PL++;
		}
		while (R < PR) {
			v = A[PR];
			ans -= cnt[v] * cnt[v];
			cnt[v]--;
			ans += cnt[v] * cnt[v];
			PR--;
		}
		while (R > PR) {
			PR++;
			v = A[PR];
			ans -= cnt[v] * cnt[v];
			cnt[v]++;
			ans += cnt[v] * cnt[v];	
		}
		Ans[proc[u].p] += ans * (intl) proc[u].k;
    }
}

int main() {
    scanf("%d",&n);
    for (int i = 1; i <= n; i++)
		scanf("%d",&A[i]);
    scanf("%d",&m);
    for (int i = 1; i <= m; i++) {
		int l1, r1, l2, r2;
		scanf("%d %d %d %d",&l1,&r1,&l2,&r2);
		if (l1 > l2) swap(l1, l2), swap(r1, r2);
		if (l1 == l2 && r1 > r2) swap(r1, r2);
		add(i, l1, r2, 1);
		add(i, r1 + 1, l2 - 1, 1);
		add(i, l1, l2 - 1, -1);
		if (r1 < r2)
			add(i, r1 + 1, r2, -1);
		else
			add(i, r2 + 1, r1, -1);
		add(i, l2, r1, 1);	
    }
    solve();
    for (int i = 1; i <= m; i++)
		printf("%I64d\n",Ans[i] / 2LL);
    return 0;
}
