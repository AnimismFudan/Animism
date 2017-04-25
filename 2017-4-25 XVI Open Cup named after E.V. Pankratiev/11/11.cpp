#include <bits/stdc++.h>
#define maxn 101000
using namespace std;


struct str { int v,nex; } edge[maxn << 1];
	}
	return;
}

int main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d %d %d",&n,&m,&q);
	for (int i = 1; i <= m; i++) {
		int a;
		scanf("%d",&a);
		mark[a] = 1;
	}
	for (; q; q--) {
		int a, b;
		scanf("%d %d",&a,&b);
		if (mark[a]) { printf("%d\n", m); continue; }
		if (!mark[b]) make_edge(b, a);
		else {
			paint(a);			
		}
		printf("%d\n",m);
	}
	return 0;
}
