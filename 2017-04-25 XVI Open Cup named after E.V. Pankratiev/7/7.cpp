#include <bits/stdc++.h>
using namespace std;

int f[22][22][22][22], mark[22][22][22][22];
vector <int> vec[10100];
vector <pair<int,int>> VEC[10100];

int n, m, k;
int g[10100][10];
int p[10100], size[10100];
int MARK;

void getmin(int &a, int b) {
	if (a > b) a = b;
}

void dfs(int u) {
	if (u <= n) {
		for (int i = 0; i <= 3; i++)
			g[u][i] = (p[u] != i);
		return;
	}
	for (auto i = vec[u].begin(); i != vec[u].end(); i++)
		dfs(*i);
	memset(f[0], 1, sizeof(f[0]));
	f[0][0][0][0] = 0;
	int o = 0;
	for (auto i = vec[u].begin(); i != vec[u].end(); i++) {
		o++;
		memset(f[o], 1, sizeof(f[o]));
		int v = *i;		
		//dfs(v);
		for (int a = 0; a <= size[u]; a++)
			for (int b = 0; b <= size[u]; b++)
				for (int c = 0; c <= size[u] * MARK; c++) {
					getmin(f[o][a][b][c], f[o - 1][a][b][c] + g[v][0]);
					getmin(f[o][a + 1][b][c], f[o - 1][a][b][c] + g[v][1]);
					getmin(f[o][a][b + 1][c], f[o - 1][a][b][c] + g[v][2]);
					getmin(f[o][a][b][c + 1], f[o - 1][a][b][c] + g[v][3]);
				}
	}
	memset(g[u],1,sizeof(g[u]));
	for (int a = 0; a <= size[u]; a++)
		for (int b = 0; b <= size[u]; b++)
			for (int c = 0; c <= size[u] * MARK; c++) {
				if (a > b && a > c) getmin(g[u][1], f[o][a][b][c]);
				else if (b > a && b > c) getmin(g[u][2], f[o][a][b][c]);
				else if (c > a && c > b) getmin(g[u][3], f[o][a][b][c]);
				else getmin(g[u][0], f[o][a][b][c]);
			}
	return;
}

void DFS(int u, int x) {
	if (u <= n) {
		if (p[u] != x) printf("%d %d\n", u, x);
		return;
	}

	memset(f[0], 1, sizeof(f[0]));
	f[0][0][0][0] = 0;
	int o = 0;
	for (auto i = vec[u].begin(); i != vec[u].end(); i++) {
		o++;
		memset(f[o], 1, sizeof(f[o]));
		int v = *i;
		for (int a = 0; a <= size[u]; a++)
			for (int b = 0; b <= size[u]; b++)
				for (int c = 0; c <= size[u] * MARK; c++) {
					if (f[o][a][b][c] > f[o - 1][a][b][c] + g[v][0]) {
						f[o][a][b][c] = f[o - 1][a][b][c] + g[v][0];
						mark[o][a][b][c] = 0;
					}
					if (f[o][a + 1][b][c] > f[o - 1][a][b][c] + g[v][1]) {
						f[o][a + 1][b][c] = f[o - 1][a][b][c] + g[v][1];
						mark[o][a + 1][b][c] = 1;
					}
					if (f[o][a][b + 1][c] > f[o - 1][a][b][c] + g[v][2]) {
						f[o][a][b + 1][c] = f[o - 1][a][b][c] + g[v][2];
						mark[o][a][b + 1][c] = 2;
					}
					if (f[o][a][b][c + 1] > f[o - 1][a][b][c] + g[v][3]) {
						f[o][a][b][c + 1] = f[o - 1][a][b][c] + g[v][3];
						mark[o][a][b][c + 1] = 3;
					}
				}
	}

	bool flag = true;
	for (int a = 0; a <= size[u] && flag; a++)
		for (int b = 0; b <= size[u] && flag; b++)
			for (int c = 0; c <= size[u] * MARK && flag; c++) {
				if (a > b && a > c && x == 1 && g[u][1] == f[o][a][b][c]) {
					int A = a, B = b, C = c;
					for (int q = o; q; q--) {
						VEC[u].push_back(make_pair(vec[u][q - 1], mark[q][A][B][C]));
						//DFS(vec[u][q - 1], mark[q][A][B][C]);
						if (mark[q][A][B][C] == 1) A--;
						else if (mark[q][A][B][C] == 2) B--;
						else if (mark[q][A][B][C] == 3) C--;
					}
					flag = false; break;
				}
				else if (b > a && b > c && x == 2 && g[u][2] == f[o][a][b][c]) {
					int A = a, B = b, C = c;
					for (int q = o; q; q--) {
						VEC[u].push_back(make_pair(vec[u][q - 1], mark[q][A][B][C]));
						if (mark[q][A][B][C] == 1) A--;
						else if (mark[q][A][B][C] == 2) B--;
						else if (mark[q][A][B][C] == 3) C--;
					}
					flag = false; break;
				}
				else if (c > a && c > b && x == 3 && g[u][3] == f[o][a][b][c]) {
					int A = a, B = b, C = c;
					for (int q = o; q; q--) {
						VEC[u].push_back(make_pair(vec[u][q - 1], mark[q][A][B][C]));
						if (mark[q][A][B][C] == 1) A--;
						else if (mark[q][A][B][C] == 2) B--;
						else if (mark[q][A][B][C] == 3) C--;
					}
					flag = false; break;
				}
				else if (x == 0 && g[u][0] == f[o][a][b][c]) {
					if (a > b && a > c) continue;
					if (b > a && b > c) continue;
					if (c > a && c > b) continue;
					int A = a, B = b, C = c;
					for (int q = o; q; q--) {
						VEC[u].push_back(make_pair(vec[u][q - 1], mark[q][A][B][C]));
						if (mark[q][A][B][C] == 1) A--;
						else if (mark[q][A][B][C] == 2) B--;
						else if (mark[q][A][B][C] == 3) C--;
					}
					flag = false; break;
				}
			}
	for (auto i = VEC[u].begin(); i != VEC[u].end(); i++) {
		DFS(i -> first, i -> second);
	}
	return;
}

int main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d %d %d",&n,&m,&k);
	MARK = (k == 3);
	for (int i = 1; i <= n; i++) scanf("%d",&p[i]);
	for (int i = n + 1; i <= m + n; i++) {
		scanf("%d",&size[i]);
		for (int j = 1; j <= size[i]; j++) {
			int a;
			scanf("%d",&a);
			if (a > 0) vec[i].push_back(a);
			else vec[i].push_back(n - a);
		}
	}
	dfs(n + 1);
	printf("%d\n",g[n + 1][1]);
	DFS(n + 1, 1);
	return 0;
}
