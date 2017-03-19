#include <bits/stdc++.h>
using namespace std;

const int MaxN = (int)1e3 + 7;

int N, M, a[MaxN];

int main()
{
	scanf("%d%d", &N, &M);
	for (int i=1; i<=N; i++)
	{
		if (M >= (N-i) / 2)
		{
			a[i] = M - (N - i) / 2;
			for (int j = i+2; j<=N; j+=2)
				a[j] = 1;
			break;
		}
		a[i] = -1;
	}
	for (int i=1; i<=N; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}

