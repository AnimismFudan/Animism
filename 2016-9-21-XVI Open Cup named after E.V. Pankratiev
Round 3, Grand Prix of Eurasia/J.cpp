#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define UI unsigned int

const int oo = 2e9;

const int fx[6] = {-1, 1, 0, 0, -1, 1};
const int fy[6] = {0, 0, -1, 1, 1, -1};

int ans, tot, S, T, pt, l, r, W, H, N, C, M, len;
int num[1000010], q[1000010], dist[1000010];
int st[1000010], ne[4000010], go[4000010], c[4000010];
int Link[110][110];

class poi{
	public:
	int x, y;
	bool operator < (const poi &X)const{
		if (x != X.x)return x < X.x;
		return y < X.y;
	}
}P[1000010], p;

map<poi, int> Hash;

class rec{
	public:
	int x, y, p;
}City[6], Catapult[110], Mountain[1010], Res[110];

bool dist_2(const poi &A, const poi &B){
	poi p;
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++){
			p.x = A.x + fx[i] + fx[j];
			p.y = A.y + fy[i] + fy[j];
			if (p.x == B.x && p.y == B.y)
				return 1;
		}
	return 0;
}

void Add(int x, int y, int cc){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
	c[pt] = cc;
}

bool build(){
	for (int i = S; i <= T; i++)
		dist[i] = -1;
	dist[S] = 0;
	q[l = r = 0] = S;
	for (; l <= r; l++){
		int x = q[l];
		for (int i = st[x]; i; i = ne[i])
			if (c[i] && dist[go[i]] == -1){
				dist[go[i]] = dist[x] + 1;
				if (go[i] == T)
					return 1;
				q[++r] = go[i];
			}
	}
	return 0;
}

int dinic(int x, int up){
	if (x == T)
		return up;
	int w = 0;
	for (int i = st[x]; w < up && i; i = ne[i])
		if (c[i] && dist[go[i]] == dist[x] + 1){
			int t = dinic(go[i], min(up - w, c[i]));
			w += t;
			c[i] -= t;
			c[i ^ 1] += t;
		}
	if (!w)dist[x] = -1;
	return w;
}

bool check(const int &d){
	S = 0;
	T = C + tot + N + 1;
	memset(st, 0, sizeof(st));
	pt = 1;
	for (int i = 1; i <= C; i++){
		Add(S, i, 1);
		Add(i, S, 0);
		for (int j = 1; j <= Link[i][0]; j++){
			Add(i, C + Link[i][j], 1);
			Add(C + Link[i][j], i, 0);
		}
	}
	int All = 0;
	for (int k = 1; k <= N; k++)
		if ((d >> (k - 1)) & 1){
			Add(C + tot + k, T, City[k].p);
			Add(T, C + tot + k, 0);
			All += City[k].p;
			for (int j = 1; j <= tot; j++)
				if (dist_2(P[j], P[k]) && (!num[j] || j == k)){
					Add(C + j, C + tot + k, 1);
					Add(C + tot + k, C + j, 0);
				}
		}
	int ans = 0;
	while (build())
		ans += dinic(S, oo);
	return ans == All;
}

void dfs(const poi &p, int step){
	if (!step)return;
	if (p.x < 0 || p.y < 0 || p.x >= W || p.y >= H)
		return;
	if (!Hash[p]){
		Hash[p] = ++tot;
		P[tot] = p;
		num[tot] = 0;
	}
	int t = Hash[p];
	if (num[t] > 1)return;
	q[++len] = t;
	poi pp;
	for (int i = 0; i < 6; i++){
		pp.x = p.x + fx[i];
		pp.y = p.y + fy[i];
		dfs(pp, step - 1);
	}
}

void get_result(){
	for (int i = 1; i <= C; i++){
		bool flag = 1;
		for (int j = st[i]; j; j = ne[j])
			if (!c[j] && go[j] > C){
				int y = go[j] - C;
				Res[i].x = P[y].x;
				Res[i].y = P[y].y;
				for (int k = st[C + y]; k; k = ne[k])
					if (!c[k] && go[k] > C + tot){
						Res[i].p = go[k] - C - tot;
						flag = 0;
						break;
					}
				break;
			}
		if (flag){
			Res[i].x = Catapult[i].x;
			Res[i].y = Catapult[i].y;
		}
	}
}

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	
	scanf("%d%d", &W, &H);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++){
		scanf("%d%d%d", &City[i].x, &City[i].y, &City[i].p);
		p.x = City[i].x;
		p.y = City[i].y;
		Hash[p] = ++tot;
		P[tot] = p;
		num[tot] = 2;
	}
	scanf("%d", &C);
	for (int i = 1; i <= C; i++){
		scanf("%d%d%d", &Catapult[i].x, &Catapult[i].y, &Catapult[i].p);
		p.x = Catapult[i].x;
		p.y = Catapult[i].y;
		Hash[p] = ++tot;
		P[tot] = p;
		num[tot] = 1;
	}
	scanf("%d", &M);
	for (int i = 1; i <= M; i++){
		scanf("%d%d", &Mountain[i].x, &Mountain[i].y);
		p.x = Mountain[i].x;
		p.y = Mountain[i].y;
		Hash[p] = ++tot;
		P[tot] = p;
		num[tot] = 3;
	}
	for (int i = 1; i <= C; i++){
		p.x = Catapult[i].x;
		p.y = Catapult[i].y;
		len = 0;
		dfs(p, Catapult[i].p);
		sort(q + 1, q + len + 1);
		len = unique(q + 1, q + len + 1) - q - 1;
		for (int j = 1; j <= len; j++)
			Link[i][j] = q[j];
		Link[i][0] = len;
	}
	ans = 0;
	for (int i = 1; i < (1 << N); i++)
		if (check(i)){
			int t = 0;
			for (int j = 0; j < N; j++)
				t += (i >> j) & 1;
			if (ans < t){
				ans = t;
				get_result();
			}
		}
	printf("%d\n", ans);
	for (int i = 1; i <= C; i++)
		printf("%d %d %d\n", Res[i].x, Res[i].y, Res[i].p);
	return 0;
}

