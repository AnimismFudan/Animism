#include <bits/stdc++.h>
using namespace std;

#define LL long long

const int fx[4] = {-1, 1, 0, 0};
const int fy[4] = {0, 0, -1, 1};

int N, M, len, ans, sx, sy, tx, ty;
char Lis[60];
char s[60][60];
bool vis[60][60];
int qx[5000000], qy[5000000];
int f[60][60][60];

void getPos(int k, int i, int j, int &x, int &y){
	x = i + fx[k];
	y = j + fy[k];
	if (x < 0 || y < 0 || x >= N || y >= M || s[x][y] == '#'){
		x = i;
		y = j;
	}
}

void spfa(int k){
	int l, r;
	l = 1; r = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++){
			++r;
			qx[r] = i;
			qy[r] = j;
			vis[i][j] = 1;
		}
	for (; l <= r; l++){
		int i = qx[l];
		int j = qy[l];
		vis[i][j] = 0;
		for (int t = 0; t < 4; t++){
			int x, y;
			getPos(t, i, j, x, y);
			if (f[k][x][y] > f[k][i][j] + 1){
				f[k][x][y] = f[k][i][j] + 1;
				if (!vis[x][y]){
					vis[x][y] = 1;
					++r;
					qx[r] = x;
					qy[r] = y;
				}
			}
		}
	}
}

int main(){
//	freopen("B.in", "r", stdin);
//	freopen("B.out", "w", stdout);
	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; i++){
		scanf("%s", s[i]);
		for (int j = 0; j < M; j++){
			if (s[i][j] == 'R'){
				sx = i;
				sy = j;
				s[i][j] = '.';
			}
			if (s[i][j] == 'E'){
				tx = i;
				ty = j;
				s[i][j] = '.';
			}
		}
	}
	scanf("%s", Lis);
	len = strlen(Lis);
	ans = 2e9;
	memset(f, 61, sizeof(f));
	f[0][sx][sy] = 0;
	spfa(0);
	ans = min(ans, f[0][tx][ty]);
	for (int k = 1; k <= len; k++){
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++){
				if (f[k - 1][i][j] >= 1e9) continue;
				f[k][i][j] = min(f[k][i][j], f[k - 1][i][j] + 1);
				int x, y;
				if (Lis[k - 1] == 'U') getPos(0, i, j, x, y);
				else if (Lis[k - 1] == 'D') getPos(1, i, j, x, y);
				else if (Lis[k - 1] == 'L') getPos(2, i, j, x, y);
				else if (Lis[k - 1] == 'R') getPos(3, i, j, x, y);
				f[k][x][y] = min(f[k][x][y], f[k - 1][i][j]);
			}
		spfa(k);
		ans = min(ans, f[k][tx][ty]);
	}
	printf("%d", ans);
	return 0;
}

