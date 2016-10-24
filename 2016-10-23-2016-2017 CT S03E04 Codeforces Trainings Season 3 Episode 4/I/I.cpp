#include <bits/stdc++.h>
using namespace std;

int Test, D, N, ans;
class poi{
	public:
	int x, y;
}P[100010];
int H[1010], C[1010], A[1010][1010];

int main(){
	scanf("%d", &Test);
	while (Test--){
		scanf("%d%d", &D, &N);
		for (int i = 1; i <= N; i++){
			scanf("%d%d", &P[i].x, &P[i].y);
			P[i].x %= D;
			P[i].x = (P[i].x + D) % D;
			P[i].y %= D;
			P[i].y = (P[i].y + D) % D;
			H[P[i].x]++;
			C[P[i].y]++;
			A[P[i].x][P[i].y]++;
		}
		ans = 2e9;
		for (int i = 0; i < D; i++)
			for (int j = 0; j < D; j++)
				ans = min(ans, H[i] + C[j] - A[i][j]);
		printf("%d\n", ans);
		for (int i = 1; i <= N; i++){
			H[P[i].x] = 0;
			C[P[i].y] = 0;
			A[P[i].x][P[i].y] = 0;
		}
	}
	return 0;
}