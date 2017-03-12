#include <bits/stdc++.h>
using namespace std;

const int MaxN = 25007;

int n,ans,a,b,id[MaxN];
char str[MaxN];

int main()
{
	int i,j;
	scanf("%s",str+1);
	n = strlen(str+1);
	
	a = b = 0;
	for(i=1;i<=n;i++)
		if(str[i]=='1') id[i] = ++a;
		else id[i] = ++b;
	
	ans = 1<<30;
	for(i=1,j=0; i<=n; i++)
		if(str[i]=='1') j += abs(i-id[i]);
	if(j<ans) ans = j;
	for(i=1,j=0; i<=n; i++)
		if(str[i]=='2') j += abs(i-id[i]);
	if(j<ans) ans = j;
	printf("%d\n",ans);
	
	return 0;
}
