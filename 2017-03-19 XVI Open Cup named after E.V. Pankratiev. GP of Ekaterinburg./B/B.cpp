#include <bits/stdc++.h>
using namespace std;

const int MaxN = (int)1e3 + 7;

int N, a[MaxN];
map<int, bool> mp;

int main()
{
	scanf("%d", &N);
	for (int i=1; i<=N; i++)
		scanf("%d", a+i);
	
	for (int i=1; i<=N; i++)
	{
		int d = a[i];
		for (int j=1; j*j <= d; j++)
			if (d % j == 0) mp[j] = true, mp[d/j] = true;
	}
	
	int d = 2;
	while (mp[d]) d ++;
	printf("%d\n", d);
	
	return 0;
}

