#include <bits/stdc++.h>
using namespace std;
int ans,n,m;
int f[1010000];

struct str { int a,b; } dot[1010000];

bool cmp(const str &a, const str &b) {
	return (a.b < b.b);
}

int main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d",&dot[i].a,&dot[i].b);
	}
	sort(dot + 1,dot + n + 1,cmp);
	for (int i = 1; i <= n; i++) {
		if (m < dot[i].b) break;
		if (!f[dot[i].a]) {
			f[dot[i].a] = 1;
			m -= dot[i].b;
			ans++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
