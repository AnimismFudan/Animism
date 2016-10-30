#include <bits/stdc++.h>
using namespace std;
#define LL long long

int N, l, r, pt;
int c[10010], in[10010][6];
int q[4000010];
int st[10010], ne[400010], go[400010];

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

void get_know(int x){
	if (x < 2){
		c[x] = x;
		return;
	}
	if (!in[x][3] && !in[x][4] && !in[x][5] && in[x][0] == in[x][1]){
		c[x] = 2;
		return;
	}
	if (in[x][0] > in[x][1] + in[x][3] + in[x][5]){
		c[x] = 0;
		return;
	}
	if (in[x][1] > in[x][0] + in[x][4] + in[x][5]){
		c[x] = 1;
		return;
	}
	if (in[x][0] >= in[x][1] + in[x][3] + in[x][5]){
		c[x] = 4;
		return;
	}
	if (in[x][1] >= in[x][0] + in[x][4] + in[x][5]){
		c[x] = 3;
		return;
	}
	c[x] = 5;
	return;
}

int main(){
	freopen("L.in", "r", stdin);
	freopen("L.out", "w", stdout);
	scanf("%d", &N);
	pt = 1;
	for (int i = 2; i < N; i++){
		int k, x;
		scanf("%d", &k);
		for (int j = 1; j <= k; j++){
			scanf("%d", &x);
			Add(x, i);
			Add(i, x);
			in[i][5]++;
		}
	}
	//c[x] = 0 -> 0 1 -> 1 2 -> 1/2 3 -> -0 4 -> -1 5 -> ?
	for (int i = 0; i < N; i++)c[i] = 5;
	q[l = 1] = 0;q[r = 2] = 1;
	for (;l <= r; l++){
		int x = q[l];
		int cc = c[x];
		get_know(x);
		if (c[x] == cc)continue;
		for (int i = st[x]; i; i = ne[i])
			if (!(i & 1)){
				int y = go[i];
				in[y][cc]--;
				in[y][c[x]]++;
				q[++r] = y;
			}
	}
	for (int i = 0; i < N; i++)
		if (c[i] == 0)printf("0\n");
		else if (c[i] == 1)printf("1\n");
		else if (c[i] == 2)printf("1/2\n");
		else printf("?\n");
	return 0;
}
