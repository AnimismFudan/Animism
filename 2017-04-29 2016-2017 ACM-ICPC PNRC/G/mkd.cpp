#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("G.in", "w", stdout);
	
	int N = 6, M = 6;
	srand(time(0));
	printf("%d %d\n", N, M);
	for (int i=1; i<=N; i++)
	{
		for (int j=1; j<=M; j++)
		{
			int a = rand() % 5;
			if (a == 0) printf("L");
			else if (a == 1) printf("W");
			else printf("C");
		}
		printf("\n");
	}
	return 0;
}

