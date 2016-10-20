#include <bits/stdc++.h>
#define maxn 2010000
using namespace std;

struct str { int v,nex; } edge[maxn];

typedef int arr32[maxn];

arr32 Ldot,Rdot,Ldis,Rdis,fa,fst,mark,dis,du,que,dot,dep;

int T,A,B,n,e,Ans,Ansa,Ansb;
int top;

void init() {
	for (int i = 1; i <= n; i++)
		fst[i] = mark[i] = dis[i] = du[i] = 0;
	e = 0; top = 0;
	Ans = 2010000000;
}

void make_edge(int a,int b) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b;
	edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a;
	du[a]++; du[b]++;
}

void solve() {
	int L = 0, R = 0;
	for (int i = 1; i <= n; i++)
		if (du[i] == 1) que[++R] = i;
	while (L < R) {
		int u = que[++L];
		if (mark[u]) continue;
		dis[fa[u]] = max(dis[fa[u]], dis[u] + 1);
		du[fa[u]]--;
		if (du[fa[u]] == 1) que[++R] = fa[u];
	}

	Ldis[1] = dis[dot[1]]; Ldot[1] = 1;

	int maxA, maxB;
	
	maxA = dis[dot[1]]; maxB = 0;
	for (int i = 2; i <= top; i++) {
		Ldot[i] = Ldot[i - 1];
		while(true) {
			int v = Ldot[i] + 1;
			if (v > i) break;
			int max2 = max(maxA + 1, max(maxB - 1, dis[dot[i]] + i - v));
			int max1 = max(maxA, max(maxB, dis[dot[i]] + i - Ldot[i]));
			if (max2 <= max1) {
				Ldot[i] = v;
				maxA = max(maxA + 1, dis[dot[v]]);
				maxB = max(maxB - 1, dis[dot[i]] + i - v);
			} else {
				Ldot[i] = v - 1;
				maxB = max(maxB, dis[dot[i]] + i - v + 1);
				break;
			}
		}
		Ldis[i] = max(maxA, maxB);
	}

	Rdis[top] = dis[dot[top]]; Rdot[top] = top;

	maxA = dis[dot[top]]; maxB = 0;
	for (int i = top - 1; i >= 1; i--) {
		Rdot[i] = Rdot[i + 1];
		while(true) {
			int v = Rdot[i] - 1;
			if (v < i) break;
			int max2 = max(maxA + 1, max(maxB - 1, dis[dot[i]] + v - i));
			int max1 = max(maxA, max(maxB, dis[dot[i]] + Rdot[i] - i));
			if (max2 <= max1) {
				Rdot[i] = v;
				maxA = max(maxA + 1, dis[dot[v]]);
				maxB = max(maxB - 1, dis[dot[i]] + v - i);
			} else {
				Rdot[i] = v + 1;
				maxB = max(maxB, dis[dot[i]] + (v + 1) - i);
				break;
			}
		}
		Rdis[i] = max(maxA, maxB);
	}

	for (int i = 1; i < top; i++) {
		if (max(Ldis[i], Rdis[i + 1]) < Ans) {
			Ans = max(Ldis[i], Rdis[i + 1]);
			Ansa = dot[Ldot[i]];
			Ansb = dot[Rdot[i + 1]];
		}
	}

	printf("%d %d %d\n",Ans,Ansa, Ansb);
	
}

int find(int u) {
	dep[u] = dep[fa[u]] + 1;
	int ans = u;
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v;
		if (fa[u] == v) continue;
		fa[v] = u;
		int k = find(v);
		if (dep[k] > dep[ans]) ans = k;
	}
	return ans;
}

int main() {
	for (scanf("%d",&T); T; T--) {
		scanf("%d",&n);
		init();
		for (int i = 1; i < n; i++) {
			int a, b;
			scanf("%d %d",&a,&b);
			make_edge(a, b);
		}
		fa[1] = 0; dep[1] = 0;
		A = find(1);
		fa[A] = 0; dep[A] = 0;
		B = find(A);
		for (int u = B; u; u = fa[u]) {
			mark[u] = 1;
			dot[++top] = u;
		}
		solve();
	}
	return 0;
}