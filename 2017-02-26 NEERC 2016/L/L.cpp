#include <bits/stdc++.h>
using namespace std;

#define LL long long

const int maxn = 2300;

char sout[100010];
LL A, B, Delta, S, s, hg;
int len, ll;
bool a[maxn + 10];
int f[maxn + 10], p[maxn + 10], pn[maxn + 10];
LL dp[1010][maxn + 10], dps[1010][maxn + 10];

int get_length(int x){
	int t = 0;
	for (; x > 0; x /= 10)
		t++;
	return t;
}

void str_Add(int x){
	if (x > 9)
		str_Add(x / 10);
	sout[++ll] = x % 10 + '0';
}

void pri(LL l, LL d){
	ll = 0;
	sout[++ll] = ',';
	sout[++ll] = ' ';
	sout[++ll] = '[';
	bool flag = 0;
	for (int i = 1; i <= len; i++)
		if (a[i]){
			if (flag){
				sout[++ll] = ',';
				sout[++ll] = ' ';
			}
			str_Add(p[i]);
			flag = 1;
		}
	sout[++ll] = ']';
	for (int i = l; Delta > 0 && i <= ll; i++){
		printf("%c", sout[i]);
		Delta--;
	}
}

int main(){
	freopen("list.in", "r", stdin);
	freopen("list.out", "w", stdout);
	
	for (int i = 2; i <= maxn; i++){
		if (!f[i]){
			f[i] = i;
			p[++len] = i;
			pn[len] = get_length(i);
		}
		for (int j = 1; j <= len && p[j] <= f[i] && p[j] * i <= maxn; j++)
			f[p[j] * i] = p[j];
	}
	
	dp[len + 1][0] = 1;
	dps[len + 1][0] = 4;
	for (int i = len; i >= 1; i--){
		for (int j = 0; j <= maxn; j++){
			dp[i][j] += dp[i + 1][j];
			dps[i][j] += dps[i + 1][j];
			if (j + p[i] <= maxn){
				dp[i][j + p[i]] += dp[i + 1][j];
				dps[i][j + p[i]] += dps[i + 1][j] + dp[i + 1][j] * pn[i];
				if (j)
					dps[i][j + p[i]] += dp[i + 1][j] * 2;
			}
		}
	}
	
/*	double ss = 0;
	
	for (int i = 0; i <= maxn; i++)
		ss += dps[1][i];
		
	cout << ss << endl;*/
	
	cin >> A >> B;
	A += 6;
	B += 6;
	Delta = B - A + 1;
	for (S = 0; S <= maxn; S++)
		if (dps[1][S] >= A) break;
		else A -= dps[1][S];
	s = S;
	hg = 0;
	for (int i = 1; i <= len; i++){
		LL n = 0, ns = 0;
		if (s >= p[i]){
			n = dp[i + 1][s - p[i]];
			ns = dps[i + 1][s - p[i]] + pn[i] * n + hg * n;
			if (s) ns += n * 2;
		}
		if (ns >= A){
			a[i] = 1;
			s -= p[i];
			hg += pn[i];
			if (s)
				hg += 2;
		}
		else{
			a[i] = 0;
			A -= ns;
		}
	}
	pri(A, Delta);
	while (Delta > 0){
		int step;
		s = 0;
		for (step = len; step >= 1; step--)
			if (a[step]){
				s += p[step];
				a[step] = 0;
				if (dp[step + 1][s])
					break;
			}
		if (!step){
			S++;
			while (!dp[1][S]) S++;
			s = S;
		}
		for (step++ ; step <= len; step++)
			if (s >= p[step] && dp[step + 1][s - p[step]]){
				a[step] = 1;
				s -= p[step];
			}
			else a[step] = 0;
		pri(1, Delta);
	}
	return 0;
}

