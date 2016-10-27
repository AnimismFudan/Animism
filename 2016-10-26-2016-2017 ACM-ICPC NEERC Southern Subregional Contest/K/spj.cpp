#include <bits/stdc++.h>
using namespace std;

int Test, N, M, pt, S, T, l, r;
bool ok;
char s1[400010], s2[400010];
int st[400010], ne[2000010], go[2000010];
int q[400010], in[400010], out[400010];

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

int main(){
	freopen("K.in", "r", stdin);
	scanf("%d", &Test);
	scanf("%d%d", &N, &M);
	scanf("%d%d", &S, &T);
	ok = 1;
	freopen("K.out", "r", stdin);
	scanf("%s", s1);
	if (s1[0] == 'Y'){
		for (int i = 1; i <= M; i++){
			int x, y;
			scanf("%d%d", &x, &y);
			out[x]++;
			in[y]++;
			Add(x, y);
		}
		for (int i = 1; i <= N; i++){
			if (!in[i] && i != S)
				ok = 0;
			if (!out[i] && i != T)
				ok = 0;
		}
		q[l = r = 1] = S;
		for (; l <= r; l++){
			int x = q[l];
			for (int i = st[x]; i; i = ne[i]){
				in[go[i]]--;
				if (!in[go[i]])
					q[++r] = go[i];
			}
		}
		if (r < N)
			ok = 0;
	}
	freopen("K_.out", "r", stdin);
	scanf("%s", s2);
	if (s1[0] != s2[0])
		ok = 0;
	freopen("K.log", "w", stdout);
	ok ? printf("Y") : printf("N");
	return 0;
}

