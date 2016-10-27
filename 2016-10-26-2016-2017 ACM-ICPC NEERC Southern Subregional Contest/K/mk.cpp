#include <bits/stdc++.h>
using namespace std;

bool b[110][110];

int main(){
	srand(time(0));
	freopen("K.in", "w", stdout);
	int Test = 1;
	printf("%d\n", Test);
	while (Test--){
		int N = rand () % 50 + 2;
//		int M = rand () % (N * (N - 1) / 2) + 1;
		int M = N - 1 + rand () % 5 + 1;
		M = min (M, N * (N - 1) / 2);
		M = max(M, N - 1);
		int S = rand () % N + 1;
		int T = rand () % N + 1;
		while (S == T)
			T = rand () % N + 1;
		memset(b, 0, sizeof(b));
		printf("%d %d %d %d\n", N, M, S, T);
		for (int i = 1; i < N; i++){
			int x = rand() % i + 1;
			int y = i + 1;
			b[x][y] = b[y][x] = 1;
			printf("%d %d\n", x, y);
		}
		M -= N - 1;
		for (int i = 1; i <= M; i++){
			int x = rand () % N + 1;
			int y = rand () % N + 1;
			while (x == y || b[x][y]){
				x = rand () % N + 1;
				y = rand () % N + 1;
			}
			b[x][y] = b[y][x] = 1;
			printf("%d %d\n", x, y);
		}
	}
	return 0;
}

