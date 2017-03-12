#include <bits/stdc++.h>
using namespace std;
#define LL long long

const int maxl = 2;
const int pp[2] = {1000000007, 19985857};

int N, pt, ans;
LL size[100010];
int st[100010], ne[200010], go[200010], fa[200010];

class rec{
	public:
	LL a[2];
	void clr(){
		memset(a, 0, sizeof(a));
	}
	bool operator < (const rec &X)const{
		for (int i = 0; i < maxl; i++){
			if (a[i] < X.a[i]) return 1;
			if (a[i] > X.a[i]) return 0;
		}
		return 0;
	}
}Hash[100010];

set <rec > USED;

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

void Pre(int x){
	size[x] = 1;
	Hash[x].clr();
	for (int i = st[x]; i; i = ne[i])
		if (go[i] != fa[x]){
			fa[go[i]] = x;
			Pre(go[i]);
			for (int j = 0; j < maxl; j++)
				Hash[x].a[j] = (Hash[x].a[j] + Hash[go[i]].a[j] * Hash[go[i]].a[j] % pp[j]) % pp[j];
			size[x] += size[go[i]];
		}
	for (int j = 0; j < maxl; j++)
		Hash[x].a[j] = (Hash[x].a[j] + size[x] * size[x] % pp[j]) % pp[j];
}

void move_root(int x, int y){
	for (int j = 0; j < maxl; j++)
		Hash[x].a[j] = (Hash[x].a[j] - size[x] * size[x] % pp[j] + pp[j]) % pp[j];
	size[x] -= size[y];
	for (int j = 0; j < maxl; j++){
		Hash[x].a[j] = (Hash[x].a[j] - Hash[y].a[j] * Hash[y].a[j] % pp[j] + pp[j]) % pp[j];
		Hash[x].a[j] = (Hash[x].a[j] + size[x] * size[x] % pp[j]) % pp[j];
	}
	
	for (int j = 0; j < maxl; j++)
		Hash[y].a[j] = (Hash[y].a[j] - size[y] * size[y] % pp[j] + pp[j]) % pp[j];
	size[y] += size[x];
	for (int j = 0; j < maxl; j++){
		Hash[y].a[j] = (Hash[y].a[j] + Hash[x].a[j] * Hash[x].a[j] % pp[j] + pp[j]) % pp[j];
		Hash[y].a[j] = (Hash[y].a[j] + size[y] * size[y] % pp[j]) % pp[j];
	}
}

void find(int x, bool flag){
	if (!flag){
		USED.insert(Hash[x]);
	}else{
		for (int i = st[x]; i; i = ne[i]){
			if (USED.find(Hash[go[i]]) != USED.end())
				ans = min(ans, x);
		}
	}
	for (int i = st[x]; i; i = ne[i])
		if (go[i] != fa[x]){
			move_root(x, go[i]);
			find(go[i], flag);
			move_root(go[i], x);
		}
}

int main(){
	freopen("unexpected-leaf.in", "r", stdin);
	freopen("unexpected-leaf.out", "w", stdout);
	scanf("%d", &N);
	for (int i = 1; i < N; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		Add(x, y);
		Add(y, x);
	}
	Pre(1);
	find(1, 0);
	memset(st, 0, sizeof(st));
	memset(fa, 0, sizeof(fa));
	pt = 0;
	for (int i = 1; i <= N; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		Add(x, y);
		Add(y, x);
	}
	Pre(1);
	ans = 2e9;
	find(1, 1);
	printf("%d\n", ans);
	return 0;
}

