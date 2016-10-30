#include <bits/stdc++.h>
using namespace std;
#define LL long long

const LL pp = (1e9) + 9;

int N, M, Q;
LL upN, upM, ans;
char s[110];
LL q1[110], q2[110];
LL dp[110][110];

LL lowbit(LL x){
	return x & -x;
}

LL get_pred(LL x){
	LL s = 0;
	LL res = 0;
	for (int i = 50; i >= 0; i--)
		if ((x >> i) & 1){
			if (i)
				res = res + (1ll << (i - 1)) * i;
			res = res + s * (1ll << i);
			s++;
		}
	res += s;
	return res;	
}

LL get_digit(LL x){
	LL s = 0;
	for (int i = 50; i >= 0; i--)
		if ((x >> i) & 1)
			s++;
	return s;
}

LL get_sum(LL R, LL C){
	if (R == 0 || C == 0)return 0;
	if (C == upM){
		LL res = get_sum(R, C - 1) % pp;
		res = (res + get_pred(R) % pp) % pp;
		return res;
	}
	LL res = (get_pred(R - 1) % pp) * (C % pp) % pp;
	res = (res + (get_pred(C) % pp) * (R % pp) % pp) % pp;
	return res;
}

LL get_MinPath(LL R, LL C){
	LL res = 2e18;
	if (C == upM){
		res = min(res, get_pred(C - 1) + get_pred(R));
		res = min(res, get_MinPath(R, C - 1) + get_digit(R * upM));
		return res;
	}
	res = min(res, get_pred(C) + get_digit(C) * (R - 1) + get_pred(R - 1));
	R--;
	int r1 = 1;q1[r1] = R;
	while (R > 0){
		LL x = lowbit(R);
		R = R ^ x;
		q1[++r1] = R;
	}
	for (int l = 1, r = r1; l < r; l++, r--)
		swap(q1[l], q1[r]);
	int r2 = 1;q2[r2] = C;
	while (C > 0){
		LL x = lowbit(C);
		C = C ^ x;
		q2[++r2] = C;
	}
	q2[r2] = 1;
	while (r2 > 1 && q2[r2] == q2[r2 - 1])q2[r2--] = 0;
	for (int l = 1, r = r2; l < r; l++, r--)
		swap(q2[l], q2[r]);
	for (int i = 1; i <= r1; i++)
		for (int j = 1; j <= r2; j++)
			dp[i][j] = 2e18;
	dp[1][1] = 1;
	for (int i = 1; i <= r1; i++)
		for (int j = 1; j <= r2; j++){
			if (i < r1){
				LL res = dp[i][j];
				res = res + get_pred(q1[i + 1]) - get_pred(q1[i]);
				res = res + (q1[i + 1] - q1[i]) * get_digit(q2[j]);
				dp[i + 1][j] = min(dp[i + 1][j],  res);
			}
			if (j < r2){
				LL res = dp[i][j];
				res = res + get_pred(q2[j + 1]) - get_pred(q2[j]);
				res = res + (q2[j + 1] - q2[j]) * get_digit(q1[i]);
				dp[i][j + 1] = min(dp[i][j + 1],  res);
			}
		}
	return dp[r1][r2];
}

int main(){
	freopen("F.in", "r", stdin);
	freopen("F.out", "w", stdout);
	scanf("%d%d%d", &N, &M, &Q);
	upN = 1ll << N;
	upM = 1ll << M;
	for (int i = 1; i <= Q; i++){
		scanf("%s", s);
		if (s[0] == 'M'){
			LL R, C;
			cin >> R >> C;
			ans = get_MinPath(R, C);
			cout << ans % pp << endl;
		}
		if (s[0] == 'S'){
			LL sx, sy, tx, ty;
			cin >> sx >> sy >> tx >> ty;
			ans = get_sum(tx, ty) - get_sum(tx, sy - 1) - get_sum(sx - 1, ty) + get_sum(sx - 1, sy - 1);
			ans = ans % pp;
			if (ans < 0) ans += pp;
			cout << ans % pp << endl;
		}
	}
	return 0;
}
