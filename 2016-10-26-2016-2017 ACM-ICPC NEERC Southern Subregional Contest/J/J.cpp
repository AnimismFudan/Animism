#include <bits/stdc++.h>
using namespace std;

int N, M, ansx, ansy, Max, now, pre;
int f[2][110][10010];
class rec{
	public:
	int v, r;
}P[110];

int main(){
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &P[i].r);
	for (int i = 1; i <= N; i++)
		scanf("%d", &P[i].v);
	
	Max = 0;
	pre = 1;
	now = 0;
	memset(f[now], 230, sizeof(f[now]));
	f[now][0][0] = 0;
	for (int i = 1; i <= N; i++){
		swap(now, pre);
		memset(f[now], 230, sizeof(f[now]));
		for (int j = 0; j < i; j++)
			for (int k = 0; k <= Max; k++)
				if (f[pre][j][k] > -1e8){
					f[now][j][k + P[i].r] = max(f[now][j][k + P[i].r], f[pre][j][k] - P[i].r);
					f[now][j + 1][k] = max(f[now][j + 1][k], f[pre][j][k] + P[i].v - P[i].r);
				}
		Max += P[i].v;
	}
	ansx = -1;
	for (int j = 0; j <= N && ansx == -1; j++)
		for (int k = 0; k <= Max; k++)
			if (f[now][j][k] >= 0){
				ansx = j;
				ansy = k;
				break;
			}
	printf("%d %d\n", ansx, ansy);
	return 0;
}

