#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, Q;
LL A[200010];

class rec{
	public:
	LL s;
	int x;
}seg[2000010];

void build(int x, int l, int r){
	if (l < r){
		int mid = (l + r) >> 1;
		build(x << 1, l, mid);
		build((x << 1) + 1, mid + 1, r);
		if (seg[x << 1].s <= seg[(x << 1) + 1].s){
			seg[x].s = seg[x << 1].s;
			seg[x].x = seg[x << 1].x;
		}
		else{
			seg[x].s = seg[(x << 1) + 1].s;
			seg[x].x = seg[(x << 1) + 1].x;
		}
	}
	else{
		seg[x].s = A[l];
		seg[x].x = l;
	}
}

int ask(int x, int l, int r, int ll, int rr, LL v){
	if (l == r){
		if (seg[x].s <= v) return l;
		return N + 1;
	}
	if (l == ll && r == rr && seg[x].s > v)
		return N + 1;
	int mid = (l + r) >> 1;
	if (rr <= mid) return ask(x << 1, l, mid, ll, rr, v);
	else if (ll > mid) return ask((x << 1) + 1, mid + 1, r, ll, rr, v);
	else{
		int p = ask(x << 1, l, mid, ll, mid, v);
		if (p == N + 1)
			p = ask((x << 1) + 1, mid + 1, r, mid + 1, rr, v);
		return p;
	}
}

int main(){
//	freopen("J.in", "r", stdin);
//	freopen("J.out", "w", stdout);
	cin >> N >> Q;
	for (int i = 1; i <= N; i++)
		cin >> A[i];
	build(1, 1, N);
	for (int i = 1; i <= Q; i++){
		LL v;
		int l, r;
		cin >> v >> l >> r;
		while (v && l <= r){
			int x = ask(1, 1, N, l, r, v);
			if (x > N) break;
			v = v % A[x];
			l = x + 1;
		}
		cout << v << endl;
	}
	return 0;
}

