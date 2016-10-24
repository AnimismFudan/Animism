#include <bits/stdc++.h>
using namespace std;

int Test, N, M;
int a[1010];
int f[1010][1010];

int main(){
	scanf("%d", &Test);
	while (Test--){
		scanf("%d", &N);
		for (int i = 1; i <= N; i++){
			scanf("%d", &a[i]);
		}
		M = N + 1;
		for (int step = 2; step <= N; step += 2){
			for (int l = 1; l + step <= M; l++){
				f[step][l] = f[step - 2][l + 1] + 1;
				if (a[l] != a[l + step - 1])
					f[step][l]--;
				for (int m = 2; m < step; m += 2){
					int t = f[m][l] + f[step - m][l + m];
					if (f[step][l] < t)
						f[step][l] = t;
				}
			}
		}
		printf("%d\n", f[N][1]);
	}
	return 0;
}