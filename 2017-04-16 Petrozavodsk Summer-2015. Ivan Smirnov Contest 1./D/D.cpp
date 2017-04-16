#include <bits/stdc++.h>
#define intl long long
#define comp complex<double>
using namespace std;

int N, pt;
int q[100010], dist[100010];
bool used[100010];
int st[100010], ne[200010], go[200010];

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

class rec{
	public:
	int x, d;
} p;

bool operator < (const rec &A, const rec &B){
	if (A.d != B.d) return A.d > B.d;
	return A.x < B.x;
}

bool operator > (const rec &A, const rec &B){
	if (A.d != B.d) return A.d < B.d;
	return A.x > B.x;
}

set <rec> Heap;
set <rec> :: iterator cp;

void spfa(int x){
	int l, r;
	q[l = r = 0] = x;
	dist[x] = 0;
	for (; l <= r; l++){
		int x = q[l];
		for (int i = st[x]; i; i = ne[i]){
			int y = go[i];
			if (used[y]) continue;
			if (dist[y] > dist[x] + 1){
				p.x = y;
				p.d = dist[y];
				cp = Heap.find(p);
				Heap.erase(cp);
				dist[y] = dist[x] + 1;
				p.d = dist[y];
				Heap.insert(p);
				q[++r] = y;
			}
		}
	}
}

int main() {
	freopen("D.in","r",stdin);
	freopen("D.out","w",stdout);
	scanf("%d", &N);
	for (int i = 1; i < N; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		Add(x, y);
		Add(y, x);
	}
	for (int i = 1; i <= N; i++){
		dist[i] = 2e9;
		p.x = i;
		p.d = dist[i];
		Heap.insert(p);
	}
	for (int step = 1; step < N; step++){
		cp = Heap.begin();
		Heap.erase(cp);
		p = *cp;
		used[p.x] = 1;
		spfa(p.x);
	}
	for (int i = 1; i <= N; i++)
		if (!used[i]){
			printf("%d\n", i);
			break;
		}
	return 0;
}
