#include <bits/stdc++.h>
using namespace std;

int n,m;

int main()
{
	scanf("%d",&n);
	m = 3;
	while(n>=m)
	{
		n -= m;
		m++;
	}
	printf("%d\n",m-3);
	return 0;
}
