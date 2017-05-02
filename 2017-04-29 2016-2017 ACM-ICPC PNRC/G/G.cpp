#include <bits/stdc++.h>
using namespace std;

#define LL long long

const int oo = 1e9;
const int fx[4] = {0, 0, 1, -1};
const int fy[4] = {1, -1, 0, 0};

int N, M, pt, All, ans;
int S, T;
char s[50][50];
int st[2000], ne[200000], go[200000], c[200000];
int q[2000], dist[2000];
bool used[50][50];

int calc(int x, int y){
	return x * M + y + 1;
}

void floodfilled(int i, int j){
	if (s[i][j] != 'L') return;
	if (used[i][j]) return;
	used[i][j] = 1;
	for (int k = 0; k < 4; k++){
		int x = i + fx[k];
		int y = j + fy[k];
		if (x < 0 || y < 0 || x >= N || y >= M)
			continue;
		floodfilled(x, y);
	}
}

void Add(int x, int y, int cc){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
	c[pt] = cc;
}

bool build(){
	int l, r;
	for (int i = S; i <= T; i++) dist[i] = -1;
	dist[S] = 0;
	q[l = r = 0] = S;
	for (; l <= r; l++){
		int x = q[l];
		for (int i = st[x]; i; i = ne[i])
			if (c[i] && dist[go[i]] == -1){
				dist[go[i]] = dist[x] + 1;
				if (go[i] == T) return 1;
				q[++r] = go[i];
			}
	}
	return 0;
}

int dinic(int x, int up){
	if (x == T) return up;
	int w = 0;
	for (int i = st[x]; w < up && i; i = ne[i])
		if (c[i] && dist[go[i]] == dist[x] + 1){
			int t = dinic(go[i], min(up - w, c[i]));
			w += t;
			c[i] -= t;
			c[i ^ 1] += t;
		}
	if (!w) dist[x] = -1;
	return w;
}

int main(){
	freopen("G.in", "r", stdin);
	freopen("G.out", "w", stdout);
	scanf("%d%d\n", &N, &M);
	for (int i = 0; i < N; i++)
		scanf("%s", s[i]);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (s[i][j] == 'L')
				for (int k = 0; k < 4; k++){
					int x = i + fx[k];
					int y = j + fy[k];
					if (x < 0 || y < 0 || x >= N || y >= M)
						continue;
					if (s[x][y] != 'C')
						continue;
					s[x][y] = 'W';
				}
	S = 0;
	T = N * M + 1;
	pt = 1;
	All = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++){
			if (s[i][j] == 'C'){
				All++;
				int u = calc(i, j);
				if ((i + j) & 1){
					Add(S, u, 1);
					Add(u, S, 0);
					for (int k = 0; k < 4; k++){
						int x = i + fx[k];
						int y = j + fy[k];
						if (x < 0 || y < 0 || x >= N || y >= M)
							continue;
						if (s[x][y] != 'C')
							continue;
						int v = calc(x, y);
						Add(u, v, 1);
						Add(v, u, 0);
					}
				}
				else{
					Add(u, T, 1);
					Add(T, u, 0);
				}
			}
		}
	ans = 0;
	while (build())
		ans += dinic(S, oo);
	ans = All - ans;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (s[i][j] == 'L' && !used[i][j]){
				ans++;
				floodfilled(i, j);
			}
	cout << ans << endl;
	return 0;
}

