#include <bits/stdc++.h>
using namespace std;

#define LL long long

LL N;
int K, len, pt;
LL L[400010];
int st[400010], ne[400010], go[400010];
LL f[400010];

class rec{
	public:
	LL l, r;
}P[400010];

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

int main() {
//	freopen("H.in","r",stdin);
//	freopen("H.out","w",stdout);
	cin >> N >> K;
	for (int i = 1; i <= K; i++){
		cin >> P[i].l >> P[i].r;
		P[i].l--;
		L[++len] = P[i].l;
		L[++len] = P[i].r;
	}
	L[++len] = 0;
	sort(L + 1, L + len + 1);
	len = unique(L + 1, L + len + 1) - L - 1;
	for (int i = 1; i <= K; i++){
		P[i].l = lower_bound(L + 1, L + len + 1, P[i].l) - L;
		P[i].r = lower_bound(L + 1, L + len + 1, P[i].r) - L;
		Add(P[i].r, P[i].l);
	}
	f[1] = 0;
	for (int i = 2; i <= len; i++){
		f[i] = f[i - 1];
		for (int j = st[i]; j; j = ne[j])
			f[i] = max(f[i], f[go[j]] + L[i] - L[go[j]]);
	}
	cout << N - f[len] << endl;
	return 0;
}
