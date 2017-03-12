#include <bits/stdc++.h>
using namespace std;

#define LL long long

const int pp = (1e9) + 7;

int Test, len;
int a[110];
LL dp[110][2][2], s[110][2][2];
LL N, ans;

int main() {
	freopen("K.in","r",stdin);
	freopen("K.out","w",stdout);
	cin >> Test;
	for (int tt = 1; tt <= Test; tt++){
		cin >> N;
		len = 0;
		for (;N ; N >>= 1)
			a[++len] = N & 1;
		for (int l = 1, r = len; l < r; l++, r--)
			swap(a[l], a[r]);
		memset(dp, 0, sizeof(dp));
		memset(s, 0, sizeof(s));
		dp[0][0][0] = 0;
		s[0][0][0] = 1;
		for (int i = 1; i <= len; i++)
			for (int j = 0; j < 2; j++)
				for (int k = 0; k < 2; k++)
					if (s[i - 1][j][k])
						for (int x = 0; x < 2; x++)
							for (int y = 0; y < 2; y++){
								if (!j && x > a[i])continue;
								if (!k && y > x)continue;
								int t1 = j;
								int t2 = k;
								if (x > y) t2 = 1;
								if (x < a[i]) t1 = 1;
								LL res = dp[i - 1][j][k];
								res = (res + s[i - 1][j][k] * (x + y) * t2) % pp;
								dp[i][t1][t2] = (dp[i][t1][t2] + res) % pp;
								s[i][t1][t2] = (s[i][t1][t2] + s[i - 1][j][k]) % pp;
							}
		ans = (dp[len][0][1] + dp[len][1][1]) % pp;
		cout << "Case #" << tt << ": " << ans << endl;
	}
    return 0;
}
