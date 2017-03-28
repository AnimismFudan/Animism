#include <bits/stdc++.h>
#define INF (1LL << 61)
#define maxn 1010000
#define intl long long
using namespace std;

vector <int> vec[maxn];

intl d[maxn * 2], di[maxn];
int n, m, g, top;
char s[maxn];
intl val[maxn];
intl ans[maxn];
intl Ans;
int p[maxn];
int quep[maxn * 2];
intl quev[maxn * 2];

void solve(int u) {
	for (int i = 0; i < top; i++) {
		d[i] = di[p[i]];
		d[top + i] = d[i];
	}
	for (int i = 1; i < top * 2; i++)
		d[i] += d[i - 1];
	intl div_ = -d[top - 1];
	//if (div_ <= 0) return;
	int L = 0, R = 0;
	for (int i = top * 2 - 1; i >= 0; i--) {
		while (L < R && quep[L + 1] >= i + top) L++;
		while (L < R && quev[R] >= d[i]) R--;
		quev[++R] = d[i];
		quep[R] = i;
		intl mi = quev[L + 1] - (i > 0 ? d[i - 1] : 0LL);		
		if (i >= top) continue;		
		for (auto j = vec[p[i]].begin(); j != vec[p[i]].end(); j++) {
			intl t;
			if (div_ > 0) {
				if (val[*j] + mi > 0) t = (val[*j] + mi + div_ - 1) / div_;
				else t = 0;
				ans[*j] = t * top;
				val[*j] -= t * div_;
			}
			else {
				if (quev[L + 1] - (i > 0 ? d[i - 1] : 0) + val[*j] > 0) continue;
				ans[*j] = 0;
			}
			//proc[++tp] = (Proc) { d[i] - val[*j], i }; 
			intl y = (i > 0 ? d[i - 1] : 0) - val[*j];
			int l = L + 1, r = R;
			while (l < r) {
				int mid = (l + r + 1) / 2;
				if (quev[mid] <= y) l = mid;
				else r = mid - 1;
			}			
			ans[*j] += (quep[l] - i + 1);
		}
	}
}

int main() {
	//freopen("A.in","r",stdin);
	//freopen("A.out","w",stdout);
	scanf("%d",&n);
	for (int i = 0; i < n; i++) scanf("%lld",&val[i]);
	scanf("%d",&m);
	scanf("%s",s);
	for (int i = 0; i < m; i++)
		if (s[i] == 'W') di[i] = 1;
		else di[i] = -1;
	g = __gcd(n, m);
	for (int i = 0; i < n; i++)
		vec[i % m].push_back(i);
	for (int i = 0; i < n; i++) ans[i] = INF;
	for (int u = 0; u < g; u++) {
		top = 0;
		p[top++] = u;
		for (int v = (u + n) % m; v != u; v = (v + n) % m) {
			p[top++] = v;
		}
		solve(u);
	}

	Ans = INF;
	for (int i = 0; i < n; i++) {
		if (ans[i] == INF) continue;
		Ans = min(Ans, (ans[i] - 1) * n + (intl) i + 1);
	}
	if (Ans == INF) printf("-1\n");
	else cout << Ans << endl;
 	return 0;
}
