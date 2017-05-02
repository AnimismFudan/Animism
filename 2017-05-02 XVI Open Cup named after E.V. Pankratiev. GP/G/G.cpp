#include <bits/stdc++.h>
using namespace std;

const unsigned int MOD = 1<<16;

int main()
{
	srand(233);
	char str[10];
	unsigned int loc = 0;
	while (loc != 1)
	{
		printf("1\n");
		fflush(stdout);
		scanf("%s", str);
		if (str[0] == 'y')
			loc = 1;
		else
		{
			while (true)
			{
				unsigned int x, y, z;
				y = rand() % MOD;
				z = rand() % MOD;
				x = (y << 16) | z;
				printf("%u\n", x);
				fflush(stdout);
				scanf("%s", str);
				if (str[0] == 'y')
				{
					loc = x;
					break;
				}
			}
		}
	}
	return 0;
}

