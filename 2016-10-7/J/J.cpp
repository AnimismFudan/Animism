#include <bits/stdc++.h>
using namespace std;
#define LL long long

int B, P, L, N;
int H[400010];
int seg[400010];

int quick(int x, int y){
	int s = 1, t = x;
	for (;y ; y >>= 1){
		if (y & 1) s = (LL)s * t % P;
		t = (LL)t * t % P;
	}
	return s;
}

int ask(int x, int l, int r, int ll, int rr){
	if (l == ll && r == rr)
		return seg[x];
	int mid = (l + r) >> 1;
	if (rr <= mid)return ask(x << 1, l, mid, ll, rr);
	else if (ll > mid)return ask((x << 1) + 1, mid + 1, r, ll, rr);
	else return (ask(x << 1, l, mid, ll, mid) + ask((x << 1) + 1, mid + 1, r, mid + 1, rr)) % P;
}

void change(int x, int l, int r, int pos, int data){
	if (l == r){
		seg[x] = (LL)data * H[L - l] % P;
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid)change(x << 1, l, mid, pos, data);
	else if (pos > mid)change((x << 1) + 1, mid + 1, r, pos, data);
	seg[x] = (seg[x << 1] + seg[(x << 1) + 1]) % P;
}

int main(){
	freopen("J.in", "r", stdin);
	freopen("J.out", "w", stdout);
	scanf("%d%d%d%d\n", &B, &P, &L, &N);
	while (B || P || L || N){
		H[0] = 1;
		for (int i = 1; i <= L; i++)
			H[i] = (LL)H[i - 1] * B % P;
		int REV = quick(B, P - 2);
		memset(seg, 0, sizeof(seg));
		for (int i = 1; i <= N; i++){
			char ch = getchar();
			if (ch == 'E'){
				int x, t;
				scanf("%d%d\n", &x, &t);
				change(1, 1, L, x, t);
			}
			if (ch == 'H'){
				int l, r;
				scanf("%d%d\n", &l, &r);
				int ans = ask(1, 1, L, l, r);
				ans = (LL)ans * quick(REV, L - r) % P;
				printf("%d\n", ans);
			}
		}
		printf("-\n");
		scanf("%d%d%d%d\n", &B, &P, &L, &N);
	}
	
	return 0;
}
