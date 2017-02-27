#include <bits/stdc++.h>
#define maxn 201000
using namespace std;

// 0 -> win, 1 -> lose, 2 -> draw

struct str { int v, nex; } edge[maxn];

int n,m;
int sta[maxn][2], mark[maxn][2][3];
int fst[maxn];
int e,du[maxn],res[maxn][2];
char MARK[3] = { 'W', 'L', 'D' };

void make_edge(int a, int b) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b;
}

void UPDATE0(int u);

void UPDATE1(int u);

void update0(int u);

void update1(int u);

void UPDATE0(int u) {
	if (mark[u][0][2]) { sta[u][0] = 2; return; }
	else if (mark[u][0][1]) { sta[u][0] = 0; return; }
	else sta[u][0] = 1;
}

void UPDATE1(int u) {
	if (mark[u][1][1]) sta[u][1] = 0;
	else if (mark[u][1][0]) sta[u][1] = 1;
	else sta[u][1] = 2;
}

void update0(int u) {
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v;
		res[v][1]--;
		mark[v][1][sta[u][0]]++;
		if (!res[v][1] && sta[v][1] == -1) {
			UPDATE1(v);
			update1(v);
		} else if (sta[u][0] == 1 && sta[v][1] == -1) {
			UPDATE1(v);
			update1(v);
		}
	}
}

void update1(int u) {
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v;
		res[v][0]--;
		mark[v][0][sta[u][1]]++;
		if (!res[v][0] && sta[v][0] == -1) {
			UPDATE0(v);
			update0(v);
		} else if (sta[u][1] == 2 && sta[v][0] == -1) {
			UPDATE0(v);
			update0(v);
		}
	}
}

int main() {
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d",&a,&b);
		make_edge(b, a);
		du[a]++;		
	}

	for (int i = 1; i <= n; i++) sta[i][1] = sta[i][0] = -1;
	for (int i = 1; i <= n; i++) {
		res[i][0] = res[i][1]  = du[i]; 
	}
	
	for (int i = 1; i <= n; i++) {
		if (!du[i]) {
			sta[i][0] = sta[i][1] = 1;
			update0(i);
			update1(i);
		}
	}

	while (true) {
		bool flag = false;
		for (int i = 1; i <= n; i++) {
			if (sta[i][1] == -1) {
				if (mark[i][1][0]) {
					UPDATE1(i);
					update1(i);
					flag = true;			
				}
			}
		}
		if (!flag) break;
	}
	
	for (int i = 1; i <= n; i++) {
		if (sta[i][0] == -1) sta[i][0] = 2;
		if (sta[i][1] == -1) sta[i][1] = 2;
	}
	
	for (int i = 1; i <= n; i++) {
		putchar(MARK[sta[i][0]]);		
	}
	
	putchar('\n');
	for (int i = 1; i <= n; i++) {
		putchar(MARK[sta[i][1]]);
	}
	return 0;
}
