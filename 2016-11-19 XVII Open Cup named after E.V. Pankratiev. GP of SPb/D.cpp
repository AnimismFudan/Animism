#include<bits/stdc++.h>
using namespace std;

int N, K;
double A[110], AMax, AMin, RES, ANS;
int C[110], ANSC[110];

void Renew(){
	AMax = 0;
	AMin = 2e9;
	for (int i = 1; i <= N; i++){
		AMax = max(AMax, A[i] / C[i]);
		AMin = min(AMin, A[i] / C[i]);
	}
	RES = AMax / AMin;
	if (RES < ANS){
		for (int i = 1; i <= N; i++)
			ANSC[i] = C[i];
		ANS = RES;
	}
}

int main(){
//	freopen("D.in", "r", stdin);
//	freopen("D.out", "w", stdout);
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= N; i++)
		scanf("%lf", &A[i]);
	AMax = 0;
	AMin = 2e9;
	for (int i = 1; i <= N; i++){
		ANSC[i] = C[i] = 1;
		AMax = max(AMax, A[i]);
		AMin = min(AMin, A[i]);
	}
	ANS = AMax / AMin;
	while (1){
		int j = 0;
		for (int i = 1; i <= N; i++){
			if (!j)j = i;
			if (A[i] / C[i] > A[j] / C[j])
				j = i;
		}
		if (!j || C[j] == K)
			break;
		C[j]++;
		Renew();
	}
	for (int i = 1; i <= N; i++){
		printf("%d", ANSC[i]);
		if (i < N)printf(" ");
		else printf("\n");
	}
	return 0;
}
