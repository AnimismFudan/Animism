#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);

int T;
double R,V;

int main()
{
	int i;
	scanf("%d",&T);
	for(i=1;i<=T;i++)
	{
		scanf("%lf%lf",&R,&V);
		printf("Case %d: %.7lf\n",i,pi * R * .5 / V);
	}
	return 0;
}

