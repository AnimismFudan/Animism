#include <bits/stdc++.h>
using namespace std;

int Test, N, ans;
int len[15];
int a[110][110];
class rec{
	public:
	int x, y, z;
}q[15][10010];

void get_Find(int step, int x, int y){
	for (int i = 1; i <= N; i++)
		if (a[x][y] + a[x][i] + a[y][i] == 2 && i != x && i != y){
			rec tt;
			tt.x = x;
			tt.y = y;
			tt.z = i;
			if (!a[tt.x][tt.z])swap(tt.y, tt.z);
			if (!a[tt.y][tt.z])swap(tt.x, tt.z);
			++len[step + 1];
			q[step + 1][len[step + 1]] = tt;
		}
}

void get_FUCK(int step, rec t){
	len[step + 1] = 0;
	for (int i = 1; i <= len[step]; i++){
		rec tt = q[step][i];
		if (a[tt.x][tt.y] + a[tt.x][tt.z] + a[tt.y][tt.z] == 2){
			++len[step + 1];
			if (!a[tt.x][tt.z])swap(tt.y, tt.z);
			if (!a[tt.y][tt.z])swap(tt.x, tt.z);
			q[step + 1][len[step + 1]] = tt;
		}
	}
	if (a[t.x][t.y])
		get_Find(step, t.x, t.y);
	if (!a[t.x][t.z])
		get_Find(step, t.x, t.z);
	if (!a[t.y][t.z])
		get_Find(step, t.y, t.z);
}

void dfs(int step){
	if (!len[step])
		ans = min(ans, step);
	if (step >= ans || step >= 10 || !len[step])
		return;
	rec t;
	t = q[step][1];
	
	a[t.x][t.y] = 1;
	a[t.y][t.x] = 1;
	get_FUCK(step, t);
	dfs(step + 1);
	a[t.x][t.y] = 0;
	a[t.y][t.x] = 0;
	
	a[t.x][t.z] = 0;
	a[t.z][t.x] = 0;
	get_FUCK(step, t);
	dfs(step + 1);
	a[t.x][t.z] = 1;
	a[t.z][t.x] = 1;
	
	a[t.y][t.z] = 0;
	a[t.z][t.y] = 0;
	get_FUCK(step, t);
	dfs(step + 1);
	a[t.y][t.z] = 1;
	a[t.z][t.y] = 1;
}

int main() {
	freopen("J.in", "r", stdin);
	freopen("J.out", "w", stdout);
	scanf("%d", &Test);
	for (int tt = 1; tt <= Test; tt++){
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				scanf("%d", &a[i][j]);
		len[0] = 0;
		for (int i = 1; i <= N; i++)
			for (int j = i + 1; j <= N; j++)
				for (int k = j + 1; k <= N; k++)
					if (a[i][j] + a[i][k] + a[j][k] == 2){
						if (len[0] > 10 * N)
							break;
						++len[0];
						q[0][len[0]].x = i;
						q[0][len[0]].y = j;
						q[0][len[0]].z = k;
						if (!a[i][k])swap(q[0][len[0]].y, q[0][len[0]].z);
						if (!a[j][k])swap(q[0][len[0]].x, q[0][len[0]].z);
					}
		ans = 20;
		if (len[0] <= 20 * N)
			dfs(0);
		if (ans == 20) ans = -1;
		printf("Case #%d: %d\n", tt, ans);
	}
	return 0;
}
