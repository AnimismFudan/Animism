#include <bits/stdc++.h>
using namespace std;

const int MaxN = 1000;

int N, M, dq[MaxN];

int Query(int a, int b)
{
	char ans[5];
	printf("? %d %d\n", a, b);
	fflush(stdout);
	scanf("%s", ans);
	if (ans[0] == 'A') return 1;
	return 2;
}

int main()
{
	scanf("%d", &N);
	dq[M = 1] = 1;
	dq[M = 2] = 2;
	for (int i=3; i<=N; i++)
	{
		int a = Query(i, dq[1]);
		if (a == 1)
		{
			int b = Query(i, dq[M]);
			if (b == 1)
			{
				M ++;
				for (int j = M; j > 1; j--)
					dq[j] = dq[j-1];
				dq[1] = i;
				dq[0] = dq[M];
				for (int j=M; j>1; j--)
					dq[j] = dq[j-1];
				dq[1] = dq[0];
			}
			else
			{
				M ++;
				for (int j = M; j > 1; j--)
					dq[j] = dq[j-1];
				dq[1] = i;
			}
		}
		else
		{
			int b = Query(i, dq[2]);
			if (b == 1)
			{
				dq[++M] = dq[1];
				dq[1] = i;
			}	
			else if (b == 2)
			{
				dq[0] = dq[1];
				for (int j=1; j<M; j++)
					dq[j] = dq[j+1];
				dq[M] = dq[0];
				dq[++M] = i;
			}
		}
	}
	
	printf("!");
	for (int i=1; i<=N; i++)
		printf(" %d", dq[i]);
	printf("\n");
	
	return 0;
}
