#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	scanf("%d",&n);
	T = 1e10;
	for (int i = 1; i <= n; i++) {
		scanf("%lf",&t[i]);
		T = min(T, t[i]);
	}
	for (int i = 1; i <= n; i++)
		solve(i);
	
	return 0;
}
