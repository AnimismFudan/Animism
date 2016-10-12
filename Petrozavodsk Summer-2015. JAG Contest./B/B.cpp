#include <bits/stdc++.h>
using namespace std;

#define LL long long

int main(){
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
	scanf("%d%d%d%d", &N, &K, &A, &B);
	sum = 0;
	for (int i = 1; i <= N; i++){
		scanf("%d", &x[i]);
		sum += x[i];
	}
	F[0][0] = 1;
	bool flag = 0;
	if (K > N - K){
		flag = 1;
		K = N - K;
	}
	for (int i = 1; i <= N; i++)
		for (int j = K; j; j--)
			F[j] = (F[j - 1] << x[i]) | F[j];
	if (flag){
		for (int i = 0; i <= sum; i++)
			b[sum - i] = F[K][i];
	}else
		for (int i = 0; i <= sum; i++)
			b[i] = F[K][i];
	pre[0] = -1;
	if (b[0])pre[0] = 0;
	for (int i = 1; i <= sum; i++)
		if (b[i])pre[i] = i;
		else pre[i] = pre[i - 1];
	suc[sum] = -1;
	if (b[sum])suc[sum] = sum;
	for (int i = sum - 1; i >= 0; i--)
		if (b[i])suc[i] = i;
		else suc[i] = suc[i + 1];
	ans = 2e9;
	ansx = -1;
	for (int i = a; i <= b; i++)
		if (ans > min(suc[i] - i, i - pre[i])){
			ans = min(suc[i] - i, i - pre[i]);
			ansx = i;
		}
	
}
