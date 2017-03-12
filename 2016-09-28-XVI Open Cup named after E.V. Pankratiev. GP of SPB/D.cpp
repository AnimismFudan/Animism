#include <bits/stdc++.h>
#define intl long long
#define lowbit(a) ((a) & (-(a)))
#define Vec vector<int>
#define INF (1 << 30)
using namespace std;

map<int,int> mp;
int n,tp,top,ansL = 2,ansR = 1;
int st[2010000],ts[2010000];
int A[501000],pri[1010000],mark[1010000];
Vec vec[1010000];

void force(int a,int p) {
	for (int i = 1; pri[i] * pri[i] <= a; i++) {
		if (a % pri[i]) continue;
		if (!mp[pri[i]]) mp[pri[i]] = ++tp;
		int q = mp[pri[i]];
		while (!(a % pri[i])) a /= pri[i];
		vec[q].push_back(p);
	}
	if (a > 1) {
		if (!mp[a]) mp[a] = ++tp;
		int q = mp[a];
		vec[q].push_back(p);
	}
}

void update(int L,int R,int num) {
	if (L > R) return;
	int res = num * 2 - (R - L + 1);
	if (res < 0) return;
	int pas = L;
	L = max(1, L - res);
	res -= (pas - L);
	R = min(n, R + res);
	if (R - L > ansR - ansL) {
		ansL = L;
		ansR = R;
	}
	return;
}

void solve(Vec vec) {
	int n = vec.size();
	for (int i = 0; i < n; i++) {
		int val = 2 * i - vec[i] + 1000011;
		int ans = INF,Ans = 0;
		for (int j = val; j; j -= lowbit(j)) {
			if (ans > st[j]) {
				ans = st[j];
				Ans = ts[j];
			}
		}
		update(vec[i], vec[i], 1);
		update(ans, vec[i], i - Ans + 1);
		for (int j = val - 1; j <= 2000100; j += lowbit(j)) {
			if (st[j] > vec[i]) {
				st[j] = vec[i];
				ts[j] = i;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		int val = 2 * i - vec[i] + 1000011;
		for (int j = val - 1; j <= 2000100; j += lowbit(j))
			st[j] = INF;
	}
}

bool judge() {
	for (int i = 1; i <= n; i++)
		if (A[i] != 1) return false;
	return true;
}

int main() {
	freopen("halfgcd.in","r",stdin);
	freopen("halfgcd.out","w",stdout);
	for (int i = 2; i <= 1000000; i++) {
		if (!mark[i]) pri[++top] = i;
		for (int j = 1; j <= top && pri[j] * i <= 1000000; j++) {
			mark[i * pri[j]] = 1;
			if (!(i % pri[j])) break;
		}
	}
	
	scanf("%d",&n);
	
	for (int i = 1; i <= n; i++)
		scanf("%d",&A[i]);
	for (int i = 1; i <= n; i++) {
		force(A[i], i);
	}

	if (judge()) {
		printf("0 0\n");
		return 0;
	}
	if (n == 1) {
		printf("1 1\n");
		return 0;
	}
	for (int i = 1; i <= 2000100; i++)
		st[i] = INF;
	for (int i = 1; i <= tp; i++)
		solve(vec[i]);

	printf("%d %d\n",ansL,ansR);
	return 0;
}
