#include <bits/stdc++.h>
using namespace std;

#define ll long long

int T, K;
long long A, B;
int pr[10][10];

long long X, ans, sum;
int flg;

ll GCD(ll a, ll b)
{
	while (b)
	{
		ll t = a;
		a = b; b = t % b;
	}
	return a;
}

void DFS(int t)
{
	if (t > pr[K][0] || sum > X)
	{
		if (sum != 1)
			ans += flg * (X / sum);
		return;
	}
	DFS(t+1);
	ll d = pr[K][t] / GCD(sum, pr[K][t]);
	flg = -flg; sum *= d;
	DFS(t+1);
	flg = -flg; sum /= d;
}

inline ll Calc(ll ttt)
{
	flg = -1; sum = 1; ans = 0;
	X = ttt;
	DFS(1);
	return ans;
}

int main()
{
	pr[2][0] = 1; pr[2][1] = 2;
	pr[3][0] = 2; pr[3][1] = 3; pr[3][2] = 4;
	pr[4][0] = 3; pr[4][1] = 4; pr[4][2] = 6; pr[4][3] = 10;
	pr[5][0] = 6; pr[5][1] = 5; pr[5][2] = 6; pr[5][3] = 8; pr[5][4] = 9; pr[5][5] = 14; pr[5][6] = 21;
	pr[6][0] = 4; pr[6][1] = 6; pr[6][2] = 8; pr[6][3] = 10; pr[6][4] = 14;
	pr[7][0] = 9; pr[7][1] = 7; pr[7][2] = 8; pr[7][3] = 9; pr[7][4] = 10; pr[7][5] = 12; pr[7][6] = 15; pr[7][7] = 33; pr[7][8] = 39; pr[7][9] = 44;
	
	scanf("%d", &T);
	while (T--)
	{
		scanf("%lld%lld%d", &A, &B, &K);
		printf("%lld\n", Calc(B) - Calc(A-1));
	}
	return 0;
}

