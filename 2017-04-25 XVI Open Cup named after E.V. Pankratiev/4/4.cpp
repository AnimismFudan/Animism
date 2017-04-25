#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, l, r;
double S[100010], X[100010], P[100010];
double dp[100010];

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%lf%lf%lf", &S[i], &X[i], &P[i]);
	for (int i = 1; i <= N; i++)
		dp[i] = 2e18;
	dp[0] = 0;
	for (int i = 0; i < N; i++){
		double s = 0;
		for (int j = 1; j <= 400; j++){
			if (i + j > N) break;
			s = s + S[i + j];
			dp[i + j] = min(dp[i + j], dp[i] + s + X[i + j]);
			s = s * (100 + P[i + j]) / 100;
		}
	}
	printf("%.8lf\n", dp[N]);
	return 0;
}

