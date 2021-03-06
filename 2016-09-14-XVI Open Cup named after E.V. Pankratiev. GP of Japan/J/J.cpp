#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, M, x, y, pt;
LL ans;
int st[100010], ne[400010], go[400010];
int s[100010], f[100010], fs[100010];

int findset(int x){
	if (f[x] == x)return x;
	return f[x] = findset(f[x]);
}

class peo{
	public:
	int c, n, ans;
}P[100010];

bool cmpc(const peo &A, const peo &B){
	return A.c < B.c;
}

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

int main(){
//	freopen("J.in", "r", stdin);
//	freopen("J.out", "w", stdout);
	
	scanf("%d", &N);
	for (int i = 1; i <= N; i++){
		scanf("%d", &P[i].c);
		P[i].n = i;
	}
	scanf("%d", &M);
	for (int i = 1; i <= M; i++){
		scanf("%d%d", &x, &y);
		Add(x, y);
		Add(y, x);
	}
	sort(P + 1, P + N + 1, cmpc);
	for (int i = 1; i <= N; i++){
		f[i] = i;
		fs[i] = 0;
	}
	for (int i = 1; i <= N; i++){
		int j = i;
		while (i < N && P[i+1].c == P[j].c)
			i++;
		for (int k = j; k <= i; k++){
			int x = P[k].n;
			P[k].ans = s[x];
			for (int t = st[x]; t; t = ne[t])
				P[k].ans = max(P[k].ans, s[go[t]]);
			P[k].ans++;
		}
		for (int k = j; k <= i; k++){
			int x = P[k].n;
			fs[x] = P[k].ans;
		}
		for (int k = j; k <= i; k++){
			int x = P[k].n;
			for (int t = st[x]; t; t = ne[t]){
				int y = go[t];
				if (findset(x) != findset(y)){
					fs[findset(x)] = max(fs[findset(x)], fs[findset(y)]);
					f[findset(y)] = findset(x);
				}
			}
		}
		for (int k = j; k <= i; k++){
			int x = P[k].n;
			P[k].ans = fs[findset(x)];
		}
		for (int k = j; k <= i; k++){
			int x = P[k].n;
			s[x] = max(s[x], P[k].ans);
			f[x] = x;
			fs[x] = 0;
			for (int t = st[x]; t; t = ne[t]){
				int y = go[t];
				s[y] = max(s[y], P[k].ans);
				f[y] = y;
				fs[y] = 0;
			}
			ans += P[k].ans;
		}
	}
	cout << ans << endl;
	return 0;
}

