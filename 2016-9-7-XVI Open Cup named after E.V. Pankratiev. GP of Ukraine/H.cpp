//19:33

#include <bits/stdc++.h>
#define eps (1e-8)
using namespace std;

typedef vector<int> VI;

double p[31],f[31][31];
double dp[810][31];
int s[31],d[31][31];
int n,top;
double ans;

map<VI,int> mp;

VI get_(const VI &u, int a, int b) {
	VI v(u.begin(), u.begin() + a);
	for (int i = a + 1; i < b; i++) v.push_back(u[i]);
	for (int i = b + 1; i < (int) u.size(); i++) v.push_back(u[i]);
	v.push_back(u[a] + u[b]);
	sort(v.begin(), v.end());
	return v;
}

void gauss(VI U) {
	int u = mp[U];
	memset(f,0,sizeof(f));
	double js = 0;
	for (int i = 0; i < (int) U.size(); i++)
		js += (double) U[i] * (U[i] - 1) / 2.0;
	js /= (double) (n * (n - 1) / 2);

	memset(f,0,sizeof(f));
   	for (int i = 1; i <= n; i++) {
		f[i][i] = 1;
		for (int j_ = 1; j_ <= s[i]; j_++) {
			int j = d[i][j_];
			f[i][j] -= js / (double) s[i] * p[i];
			f[i][n + 1] += js / (double) s[i] * p[i];
			f[i][j] -= (1.0 - p[i]) / (double) s[i];
			f[i][n + 1] += (1.0 - p[i]) / (double) s[i];
		}
		f[i][n + 1] += dp[u][i];
	}

	for (int i = 1; i <= n; i++) {
		int j = i;
		for (; j <= n && fabs(f[j][i]) < eps; j++);
		if (j > n) continue;
		for (int k = 1; k <= n + 1; k++) swap(f[i][k], f[j][k]);
		for (j = 1; j <= n; j++) {
			if (i == j) continue;
			if (fabs(f[j][i]) < eps) continue;
			double co = f[j][i] / f[i][i];
			for (int k = 1; k <= n + 1; k++)
				f[j][k] -= f[i][k] * co;
		}
	}

	for (int i = 1; i <= n; i++) dp[u][i] = f[i][n + 1] / f[i][i];

	return;
}

void solve(VI U) {	
	if (mp[U]) return;	
	mp[U] = ++top;
	int u = top;
	if (U[0] == n) return;
	int cnt = n * (n - 1) / 2;
	int size = U.size();
	for (int i = 0; i < size; i++)
		for (int j = i + 1; j < size; j++) {
			VI V = get_(U, i, j);
			solve(V);
			int v = mp[V];
			for (int a = 1; a <= n; a++) {
				for (int b_ = 1; b_ <= s[a]; b_++) {
					int b = d[a][b_];
					dp[u][a] += (dp[v][b] + 1.0) * p[a] / (double) (s[a]) * (double) U[i] * (double) U[j] / (double) cnt;
				}
			}
		}

	gauss(U);
}

int main() {
	//freopen("H.in","r",stdin);
	//freopen("H.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) scanf("%lf",&p[i]);
	for (int i = 1; i <= n; i++) {
		scanf("%d",&s[i]);
		for (int j = 1; j <= s[i]; j++) {
			scanf("%d",&d[i][j]);
		}
	}

	solve(VI(n, 1));

	ans = dp[1][1];
	
	printf("%.10lf\n",ans);
	
	return 0;
}
