#include <bits/stdc++.h>
using namespace std;

#define LL long long

int fa[10010];

int main() {
	srand(time(0));
	freopen("E.in","w",stdout);
	int Test = 10;
	printf("%d\n", Test);
	while (Test--){
		int N = rand() % 8 + 3;
		printf("%d\n", N);
		for (int i = 1; i < N; i++){
			fa[i + 1] = rand() % i + 1;
			printf("%d %d\n", fa[i + 1], i + 1);
		}
		int x = rand() % N + 1, y = rand() % N + 1;
		if (x > y) swap(x, y);
		while (x == y || fa[y] == x){
			x = rand() % N + 1;
			y = rand() % N + 1;
			if (x > y) swap(x, y);
		}
		printf("%d %d\n", x, y);
	}
    return 0;
}
