#include <bits/stdc++.h>
using namespace std;

int N, Min, s;
int A[110];

int main(){
//	freopen("K.in", "r", stdin);
//	freopen("K.out", "w", stdout);
	scanf("%d", &N);
	Min = 2e9;
	for (int i = 1; i <= N; i++){
		scanf("%d", &A[i]);
		s += A[i];
		Min = min(Min, A[i]);
	}
	N &= 1;
	s &= 1;
	Min &= 1;
	if (N == 1){
		if (s == 1) printf("Iori\n");
		else printf("Yayoi\n");
	}else{
		if (Min == 1){
			printf("Iori\n");
		}
		else if (s == 1) printf("Iori\n");
		else printf("Yayoi\n");
	}
}
