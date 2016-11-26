#include <bits/stdc++.h>
#define intl long long
using namespace std;

struct point {
	int x,y;

	void read() {
		scanf("%d %d",&x,&y);
	}
} dot[40],ans[100];

bool operator < (point a, point b) {
	return (a.x < b.x || (a.x == b.x && a.y < b.y));
}

bool operator > (point a, point b) {
	return (a.x > b.x || (a.x == b.x && a.y > b.y));
}

bool operator == (point a, point b) {
	return (a.x ==b.x && a.y == b.y);
}

typedef vector <point> Vec;

Vec st;

struct Proc {
	int a, b;
} proc[1010];

intl f[40];
int n,top;
intl K;

void count() {
	f[0] = 1;
	for (int i = 2; i <= 30; i++) {
		for (int j = 1; j <= i; j++) {
			for (int k = j + 1; k <= i; k += 2)
				f[i] += f[k - j - 1] * f[j - 1 + (i - k)];
		}
	}
	return;
}

void solve(Vec vec, intl K) { 
	int tp = 0;
	int n = (int) vec.size();
	if (!n) return;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j += 2) {
			int a = i, b = j;
			if (vec[a] > vec[b]) swap(a, b);
			proc[++tp] = (Proc) { a, b };
		}
	for (int i = 1; i <= tp; i++) {
		for (int j = tp; j > i; j--) {
			if (vec[proc[i].a] > vec[proc[j].a] ||
				(vec[proc[i].a] == vec[proc[j].a] && vec[proc[i].b] > vec[proc[j].b]))
				swap(proc[i], proc[j]);
		}
	}
	intl cnt = 0;
	for (int i = 1; i <= tp; i++) {
		intl sing = 0;
		int a = proc[i].a, b = proc[i].b;
		int A = 0, B = 0;
		for (int u = (b + 1) % n; u != a; u = (u + 1) % n) A++;
		for (int u = (a + 1) % n; u != b; u = (u + 1) % n) B++;
		sing = f[A] * f[B];
		if (cnt + sing >= K) {
			K -= cnt;
			ans[++top] = vec[a];
			ans[++top] = vec[b];
			Vec vecl, vecr;
			vecl.clear(); vecr.clear();
			for (int u = (b + 1) % n; u != a; u = (u + 1) % n) vecl.push_back(vec[u]);
			for (int u = (a + 1) % n; u != b; u = (u + 1) % n) vecr.push_back(vec[u]);
			solve(vecl, (K - 1) / f[B] + 1);
			solve(vecr, (K - 1) % f[B] + 1);
			return;
		}
		cnt += sing;
	}
}

int main() {	
	//freopen("E.in","r",stdin);
	//freopen("E.out","w",stdout);
	scanf("%d",&n);
	count();
	for (int i = 1; i <= n; i++)
		dot[i].read();
	st.clear();
	for (int i = 1; i <= n; i++)
		st.push_back(dot[i]);
	cin >> K;
	solve(st, K + 1LL);
	for (int i = 1; i <= n; i++)
		printf("%d %d\n",ans[i].x, ans[i].y);
	return 0;
}
