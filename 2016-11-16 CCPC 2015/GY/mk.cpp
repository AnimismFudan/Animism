#include <bits/stdc++.h>
using namespace std;

#define LL long long

int main(){
	srand(time(0));
	freopen("K.in", "w", stdout);
	int Test = 10;
	printf("%d\n", Test);
	while (Test--){
		int N = rand() % 5 + 2;
		printf("%d\n", N);
		for (int i = 1; i <= N; i++)
			printf("%d %d\n", rand() % 10, rand() % 10);
	}
}