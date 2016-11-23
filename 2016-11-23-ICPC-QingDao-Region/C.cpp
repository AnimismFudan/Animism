#include <bits/stdc++.h>
using namespace std;

const double e = 2.718281828;

int N;
double L,D;

int main()
{
	scanf("%d", &N);
	while (N--)
	{
		scanf("%lf%lf", &D, &L);
		D /= L;
		if (D <= 1.0) printf("0.000000\n");
		else printf("%.6lf\n", log(D) / log(e) + 1.0);
	}
	return 0;
}
