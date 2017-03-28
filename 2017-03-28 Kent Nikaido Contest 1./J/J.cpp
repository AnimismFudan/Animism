#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000;
int N, ans;
class line{
	public:
	int l, r;
}P[100010];

class rec{
	public:
	int s, mark;
}seg[400010];

inline void mark_down(int x, int l, int r){
	if (!seg[x].mark) return;
	if (l < r){
		seg[x << 1].s += seg[x].mark;
		seg[x << 1].mark += seg[x].mark;
		seg[(x << 1) + 1].s += seg[x].mark;
		seg[(x << 1) + 1].mark += seg[x].mark;
	}
	seg[x].mark = 0;
}

void Init(int x, int l, int r, int ll, int rr, int data){
	mark_down(x, l, r);
	if (l == ll && r == rr){
		seg[x].mark += data;
		seg[x].s += data;
		return;
	}
	int mid = (l + r) >> 1;
	if (rr <= mid) Init(x << 1, l, mid, ll, rr, data);
	else if (ll > mid) Init((x << 1) + 1, mid + 1, r, ll, rr, data);
	else Init(x << 1, l, mid, ll, mid, data), Init((x << 1) + 1, mid + 1, r, mid + 1, rr, data);
	seg[x].s = max(seg[x << 1].s, seg[(x << 1) + 1].s);
}

int main(){
//	freopen("J.in", "r", stdin);
//	freopen("J.out", "w", stdout);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++){
		scanf("%d%d", &P[i].l, &P[i].r);
		P[i].r--;
		Init(1, 1, maxn, P[i].l, P[i].r, 1);
	}
	ans = N - 1;
	for (int i = 1; i <= N; i++){
		Init(1, 1, maxn, P[i].l, P[i].r, -1);
		ans = min(ans, seg[1].s);
		Init(1, 1, maxn, P[i].l, P[i].r, 1);
	}
	printf("%d\n", ans);
}
