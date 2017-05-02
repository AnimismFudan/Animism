#include <bits/stdc++.h>
using namespace std;

int main()
{
	while (true)
	{
		system("./mkd");
		system("./G");
		system("./G1");
		if (system("diff G.out G1.out") != 0)
		{
			printf("WA!\n");
			return 0;
		}
		else printf("YES\n");
	}
	return 0;
}

