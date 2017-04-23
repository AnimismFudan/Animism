#include <bits/stdc++.h>
using namespace std;

int N;
int dp[1000010][2];
int Res[1000010], A[1000010];

void pri(int step){
	if (step == 0) Res[N] = N;
	else Res[N] = 1;
	int x = N - 1, y = step;
	while (x){
		if (dp[x][y] == 0) Res[x] = x;
		else Res[x] = x + 1;
		y = dp[x][y];
		x--;
	}
	for (int i = 1; i <= N; i++){
		printf("%d", Res[i]);
		if (i < N) printf(" ");
		else printf("\n");
	}
}

int Get1(int x, int y){
	if (x == 1) return dp[x][y];
	return Get1(x - 1, dp[x][y]);
}

bool work(int step){
	int x, y;
	if (step == 0) x = A[1];
	else x = A[1] >> 1;
	y = A[2] >> 1;
	if (x >= y) dp[1][0] = 0;
	else dp[1][0] = 1;
	y = A[2];
	if (x >= y) dp[1][1] = 0;
	else dp[1][1] = 1;
	for (int i = 2; i < N; i++)
		for (int j = 0; j < 2; j++){
			if (!j) y = A[i + 1] >> 1;
			else y = A[i + 1];
			if (dp[i - 1][0] == 1) x = A[i] >> 1;
			else x = A[i];
			if (x >= y) dp[i][j] = 0;
			else dp[i][j] = 1;
		}
	int t = Get1(N - 1, step);
	if (dp[N - 1][step] == 0) x = A[N];
	else x = A[N] >> 1;
	if (t == 0) y = A[1] >> 1;
	else y = A[1];
	if (x > y && step != 0) return 0;
	if (y > x && step != 1) return 0;
	return 1;
}

int main(){
//	freopen("E.in", "r", stdin);
//	freopen("E.out", "w", stdout);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++){
		scanf("%d", &A[i]);
		A[i] <<= 1;
	}
	if (work(0))
		pri(0);
	else if (work(1))
		pri(1);
	else printf("-1\n");
	return 0;
}

