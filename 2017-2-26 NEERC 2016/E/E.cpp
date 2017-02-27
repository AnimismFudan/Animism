#include <bits/stdc++.h>
#define maxn 101000
#define intl long long
using namespace std;

intl tim[maxn];
intl ques[maxn], Ans[maxn], sum[maxn], num[maxn];
int p[maxn], sou[maxn];
int n, m;
intl ans;

bool cmp(int a, int b) {
	return (num[a] < num[b]);
}

bool pmc(int a, int b) {
	return (ques[a] < ques[b]);
}

int main() {
	freopen("expect.in","r",stdin);
	freopen("expect.out","w",stdout);
	scanf("%d %d\n",&n,&m);
	intl res = 0;
	for (int i = 1; i <= n; i++) {
		char c;
		scanf("%c %lld %lld\n",&c,&tim[i],&num[i]);
		if (c == '+') {
			res += num[i];
			num[i] = num[i - 1];
			intl js = min(num[i], res);
			res -= js;
			num[i] -= js;
		} else {
			num[i] = num[i - 1] + num[i];
			intl js = min(num[i], res);
			num[i] -= js;
			res -= js;
		}		
	}
	for (int i = 1; i <= n; i++) p[i] = i;
	sort(p + 1, p + n + 1, cmp);
	int q = 1;
	for (; q <= n && !num[q]; q++);
	for (int i = 1; i <= m; i++) scanf("%lld",&ques[i]);
	for (int i = 1; i <= m; i++) sou[i] = i;
	ans = 0;
	tim[n + 1] = tim[n];
	for (int i = 1; i <= n; i++)
		ans += (tim[i + 1] - tim[i]) * num[i];
	sort(sou + 1, sou + m + 1, pmc);
	for (int i = n; i >= 1; i--) sum[i] = sum[i + 1] + tim[p[i] + 1] - tim[p[i]];
	
	for (int i = 1; i <= m; i++) {
		for (; q <= n && num[p[q]] <= ques[sou[i]]; q++) {
			intl js = max(num[p[q]] - ques[sou[i - 1]], 0LL);
			ans -= js * (tim[p[q] + 1] - tim[p[q]]);
			js = max(num[p[q]] - ques[sou[i]], 0LL);
			ans += js * (tim[p[q] + 1] - tim[p[q]]);
		}
		ans -= (ques[sou[i]] - ques[sou[i - 1]]) * sum[q];
		if (num[n] <= ques[sou[i]]) {
			Ans[sou[i]] = ans;
		} else Ans[sou[i]] = -1;
	}

	for (int i = 1; i <= m; i++) {
		if (Ans[i] == -1LL) printf("INFINITY\n");
		else printf("%lld\n",Ans[i]);
	}
	return 0;
}
