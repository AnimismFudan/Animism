#include <bits/stdc++.h>
using namespace std;

int Test, N, M, ans;
int X[210], Y[210], A[210];

bool big(int *A, int *B){
	for (int i = 1; i <= M; i++){
		if (A[i] > B[i]) return 1;
		if (A[i] < B[i]) return 0;
	}
	return 0;
}

int main(){
	freopen("L.in", "r", stdin);
	freopen("L.out", "w", stdout);
	scanf("%d", &Test);
	while (Test--){
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= M; i++)scanf("%d", &X[i]);
		for (int i = 1; i <= M; i++)scanf("%d", &Y[i]);
		for (int i = 1; i <= N; i++){
			scanf("%d", &A[i]);
			A[N + i] = A[i];
		}
		ans = 0;
		for (int i = 1; i <= N; i++){
			if (!big(X, A + i - 1) && !big(A + i - 1, Y))
				ans++;
		}
		printf("%d\n", ans);
	}
}
