#include <bits/stdc++.h>
using namespace std;

#define LL long long

const int pp = (1e7) + 19;
int N, res, Test, a[20], b[20], pt;
int st[pp], ne[12000010], w[12000010];
LL go[12000010];

void dfs(int step){
	LL hh = 0;
	for (int i = 0; i < N; i++)
		hh = hh * N + a[i];
	int h = hh % pp;
	bool flag = 1;
	for (int i = st[h]; i; i = ne[i])
		if (go[i] == hh){
			w[i] = min(w[i], step);
			flag = 0;
		}
	if (flag){
		ne[++pt] = st[h];
		st[h] = pt;
		go[pt] = hh;
		w[pt] = step;
	}
	if (step > 1)
		return;
	for (int l = 0; l < N; l++)
		for (int m = l + 1; m < N; m++)
			for (int r = m + 1; r <= N; r++){
				int mm = r - m + l;
				for (int t = l; t < r; t++)
					b[t] = a[t];
				for (int t = m; t < r; t++)
					a[t - m + l] = b[t];
				for (int t = l; t < m; t++)
					a[t - l + mm] = b[t];
				dfs(step + 1);
				for (int t = l; t < r; t++)
					b[t] = a[t];
				for (int t = mm; t < r; t++)
					a[t - mm + l] = b[t];
				for (int t = l; t < mm; t++)
					a[t - l + m] = b[t];
			}
}

void find(int step){
	if (step >= res)
		return;
	LL hh = 0;
	for (int i = 0; i < N; i++)
		hh = hh * N + a[i];
	int h = hh % pp;
	for (int i = st[h]; i; i = ne[i])
		if (go[i] == hh)
			res = min(res, w[i] + step);
	if (step > 1)return;
	for (int l = 0; l < N; l++)
		for (int m = l + 1; m < N; m++)
			for (int r = m + 1; r <= N; r++){
				int mm = r - m + l;
				for (int t = l; t < r; t++)
					b[t] = a[t];
				for (int t = m; t < r; t++)
					a[t - m + l] = b[t];
				for (int t = l; t < m; t++)
					a[t - l + mm] = b[t];
				find(step + 1);
				for (int t = l; t < r; t++)
					b[t] = a[t];
				for (int t = mm; t < r; t++)
					a[t - mm + l] = b[t];
				for (int t = l; t < mm; t++)
					a[t - l + m] = b[t];
			}
}

int main(){
	freopen("J.in", "r", stdin);
	freopen("J.out", "w", stdout);
	scanf("%d", &Test);
	while (Test--){
		scanf("%d", &N);
		memset(st, 0, sizeof(st));
		pt = 0;
		for (int i = 0; i < N; i++){
			scanf("%d", &a[i]);
			a[i]--;
		}
		res = 5;
		dfs(0);
		for (int i = 0; i < N; i++)
			a[i] = i;
		find(0);
		if (res < 5)printf("%d\n", res);
		else printf("5 or more\n");
	}
}
