#include <bits/stdc++.h>
using namespace std;

double ans;
int n, m;
int N;

int main() {
	//freopen("K.in","r",stdin);
	//freopen("K.out","w",stdout);
	scanf("%d %d",&n,&m);
	int N = 1 << n;
	m = N - m;
	for (int i = 1; (1 << i) <= m + 1; i++) {
		double p = 1;
		for (int j = 0; j <= (1 << i) - 2; j++)
			(p *= (double) (m - j)) /= (double) (N - j);
		p *= (double) (1 << i);
		p *= (double) (1 << (n - i));
		p /= (double) (N - (1 << i) + 1);
		ans += p;
	}
	printf("%.5lf\n",ans);
	return 0;
}
