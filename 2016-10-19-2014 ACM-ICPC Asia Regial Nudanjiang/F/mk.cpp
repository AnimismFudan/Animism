#include <bits/stdc++.h>
using namespace std;
#define LL long long

int L[60], R[60];

int main(){
	srand(time(0));
	freopen("F.in", "w", stdout);
	int Test = 5;
	printf("%d\n", Test);
	while(Test--){
		int N = 50;
		printf("%d\n", N);
		for (int i = 1; i <= N; i++){
//			L[i] = rand () % 50000 + 1;
//			R[i] = rand () % 50000 + 1;
			L[i] = 1;
			R[i] = 50000;
			if (L[i] > R[i])swap(L[i], R[i]);
		}
		for (int i = 1; i <= N; i++)
			printf("%d ", L[i]);
		printf("\n");
		for (int i = 1; i <= N; i++)
			printf("%d ", R[i]);
		printf("\n");
		for (int i = 1; i < N; i++)
			printf("%d %d\n", rand() % i + 1, i + 1);
	}
	return 0;
}
