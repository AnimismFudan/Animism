#include <bits/stdc++.h>
using namespace std;

int N, L, R, mid1, mid2, ans;

int main()
{
	while (scanf("%d", &N) && N != 0)
	{
		L = 0; R = N / 2;
		mid1 = L + (R - L) / 3; mid2 = 0;
		printf("? %d\n", 2 * mid1);
		fflush(stdout);
		scanf("%d", &ans);
		while (L + 1 < R)
		{
			//cerr << L << ' ' << R << endl;
			if (mid2 == 0)
			{
				mid2 = R - (R - L) / 3;
				printf("? %d\n", 2 * mid2);
				fflush(stdout);
				scanf("%d", &ans);
				if (ans == 0)
				{
					L = (L + R) / 2;
					mid1 = mid2;
					mid2 = 0;
				}
				else
				{
					R = (L + R + 1) / 2;
					mid2 = mid1;
					mid1 = 0;
				}
			}
			else
			{
				mid1 = L + (R - L) / 3;
				printf("? %d\n", 2 * mid1);
				fflush(stdout);
				scanf("%d", &ans);
				if (ans == 0)
				{
					R = (L + R + 1) / 2;
					mid2 = mid1;
					mid1 = 0;
				}
				else
				{
					L = (L + R) / 2;
					mid1 = mid2;
					mid2 = 0;
				}
			}
			//cerr << L << ' ' << R << endl;
		}
		printf("! %d\n", L + L + 1);
		fflush(stdout);
	}
	return 0;
}

