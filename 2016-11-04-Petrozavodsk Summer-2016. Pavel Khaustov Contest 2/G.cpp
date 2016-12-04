#include <bits/stdc++.h>
#define LL long long
using namespace std;

LL ans;
int N, M, len;
const int maxn = 400000;

class segleaf{
	public:
	int s, m;
};

class segment_Tree{
	public:
	segleaf a[2000010];
	
	void mark_down(int x, int l, int r){
		if (a[x].m && l < r){
			int mid = (l + r) >> 1;
			a[x << 1].m ^= 1;
			a[x << 1].s = mid - l + 1 - a[x << 1].s;
			a[(x << 1) + 1].m ^= 1;
			a[(x << 1) + 1].s = r - mid - a[(x << 1) + 1].s;
		}
		a[x].m = 0;
	}
	
	void Init(int x, int l, int r, int t, int d){
		mark_down(x, l, r);
		if (l == r){
			a[x].s = d;
			return ;
		}
		int mid = (l + r) >> 1;
		if (t <= mid) Init(x << 1, l, mid, t, d);
		else Init((x << 1) + 1, mid + 1, r, t, d);
		a[x].s = a[x << 1].s + a[(x << 1) + 1].s;
	}
	
	void rev(int x, int l, int r, int ll, int rr){
		mark_down(x, l, r);
		if (l == ll && r == rr){
			a[x].m ^= 1;
			a[x].s = r - l + 1 - a[x].s;
			return;
		}
		int mid = (l + r) >> 1;
		if (rr <= mid) rev(x << 1, l, mid, ll, rr);
		else if (ll > mid) rev((x << 1) + 1, mid + 1, r, ll, rr);
		else rev(x << 1, l, mid, ll, mid), rev((x << 1) + 1, mid + 1, r, mid + 1, rr);
		a[x].s = a[x << 1].s + a[(x << 1) + 1].s;
	}
	
	int calc(int x, int l, int r, int ll, int rr){
		mark_down(x, l, r);
		if (l == ll && r == rr)
			return a[x].s;
		int mid = (l + r) >> 1;
		if (rr <= mid) return calc(x << 1, l, mid, ll, rr);
		else if (ll > mid) return calc((x << 1) + 1, mid + 1, r, ll, rr);
		else return calc(x << 1, l, mid, ll, mid) + calc((x << 1) + 1, mid + 1, r, mid + 1, rr);
	}
}seg[31];

class trienode{
	public:
	bool mxor, msort, mxor2, ldata;
	int lson, rson;
	int s;
	LL sum;
	void clear(){
		mxor = msort = mxor2 = ldata = 0;
		lson = rson = s = sum = 0;
	}
};

class trie{
	public:
	int root, size;
	trienode a[8000010];
	void Pre(){
		root = size = 1;
		a[1].clear();
	}
	void get_xor(int x, int data, int dep){
		if (!x) return;
		a[x].mxor2 ^= data;
		if ((data >> dep) & 1){
			int lson = a[x].lson;
			int rson = a[x].rson;
			if (a[x].ldata == 0)
				a[x].sum += (LL)(a[lson].s - a[rson].s) * (1 << dep);
			else a[x].sum += (LL)(a[rson].s - a[lson].s) * (1 << dep);
			a[x].ldata ^= 1;
		}
	}
	void get_sort(int x){
		if (!x) return;
		a[x].mxor ^= a[1].mxor2;
		a[x].msort = 1;
		a[x].mxor2 = 0;
		if (a[x].ldata)
			swap(a[x].lson, a[x].rson);
	}
	void mark_down(int x, int dep){
		int lson = a[x].lson;
		int rson = a[x].rson;
		get_xor(lson, a[x].mxor, dep - 1);
		get_xor(rson, a[x].mxor, dep - 1);
		if (a[x].msort){
			get_sort(lson);
			get_sort(rson);
		}
		get_xor(lson, a[x].mxor2, dep - 1);
		get_xor(rson, a[x].mxor2, dep - 1);
		a[x].mxor = a[x].mxor2 = a[x].msort = 0;
	}
	int init(int x, int d){
		if (d == 0 && !a[x].lson){
			a[x].lson = ++size;
			a[size].clear();
		}
		if (d == 1 && !a[x].rson){
			a[x].rson = ++size;
			a[size].clear();
		}
		return d == 0 ? a[x].lson : a[x].rson;
	}
	void Init(int x, int data, int dep){
		mark_down(x, dep);
		a[x].sum += data;
		a[x].s++;
		if (dep < 0)
			return;
		Init(init(x, (data >> dep) & 1), data, dep - 1);
	}
	LL calc(int x, int l, int r, int dep){
		mark_down(x, dep);
		if (l == 1 && r == a[x].s)
			return a[x].sum;
		int lson = a[x].lson;
		int rson = a[x].rson;
		if (r <= a[lson].s)
			return calc(lson, l, r, dep - 1);
		else if (l > a[lson].s)
			return calc(rson, l - a[lson].s, r - a[lson].s, dep - 1);
		else return calc(lson, l, a[lson].s, dep - 1) + calc(rson, 1, r - a[lson].s, dep - 1);
	}
	void XOR(int x){
		mark_down(1, 30);
		get_xor(1, x, 30);
	}
	void SORT(){
		mark_down(1, 30);
		get_sort(1);
	}
}Trie;

int main() {
	freopen("G.in","r",stdin);
	freopen("G.out","w",stdout);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++){
		int x;
		scanf("%d", &x);
		for (int j = 0; j <= 30; j++)
			seg[j].Init(1, 1, maxn, i, (x >> j) & 1);
	}
	len = N;
	Trie.Pre();
	scanf("%d", &M);
	for (int i = 1; i <= M; i++){
		int t;
		scanf("%d", &t);
		if (t == 1){
			int x;
			scanf("%d", &x);
			++len;
			for (int j = 0; j <=30; j++)
				seg[j].Init(1, 1, maxn, len, (x >> j) & 1);
		}else if (t == 2){
			int l, r;
			scanf("%d%d", &l, &r);
			if (r <= Trie.a[1].s){
				ans = Trie.calc(1, l, r, 30);
			}else if (l > Trie.a[1].s){
				ans = 0;
				for (int j = 0; j <= 30; j++)
					ans += (LL)seg[j].calc(1, 1, maxn, l - Trie.a[1].s, r - Trie.a[1].s) * (1 << j);
			}else{
				ans = Trie.calc(1, l, Trie.a[1].s, 30);
				for (int j = 0; j <= 30; j++)
					ans += (LL)seg[j].calc(1, 1, maxn, 1, r - Trie.a[1].s) * (1 << j);
			}
			printf("%lld\n", ans);
		}else if (t == 3){
			int x;
			scanf("%d", &x);
			Trie.XOR(x);
			for (int j = 0; j <= 30; j++)
				if ((x >> j) & 1)
					seg[j].rev(1, 1, maxn, 1, len);
		}else if (t == 4){
			Trie.SORT();
			for (int k = 1; k <= len; k++){
				int x = 0;
				for (int j = 0; j <= 30; j++){
					x += (LL)seg[j].calc(1, 1, maxn, k, k) * (1 << j);
				}
				Trie.Init(1, x, 30);
			}
			len = 0;
		}
	}
	return 0;
}
