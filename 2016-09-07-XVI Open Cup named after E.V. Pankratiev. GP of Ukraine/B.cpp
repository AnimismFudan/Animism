#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;

const int MaxN = 2000007;

int n,m,la,lb,A[MaxN],B[MaxN],cut[MaxN];
long long ans;

int main()
{
	//freopen("B.in","r",stdin);
	//freopen("B.out","w",stdout);

	int i,x,y;
	int f,a,b;

	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
		scanf("%d%d",&x,&y),
		A[x+y] = 1, B[i] = x-y;
	sort(B+1,B+m+1);
	for(i=lb=1;i<=m;i++)
		if(B[i]!=B[lb]) B[++lb] = B[i];

	f = 0; a = b = 0;

	for(x=1;x<=lb;x++)
		if(B[x]>0) break;
	for(y=lb;y>=1;y--)
		if(B[y]<0) break;
	for(i=y+1;i<x;i++)
		if(B[i]&1) a++;
		else b++;

	ans = (long long)n*n;

	for(i=2;i<=n+1;i++)
	{
		for(;x<=lb;x++)
		{
			if(B[x]>f) break;
			if(B[x]&1) a++;
			else b++;
		}
		for(;y>=1;y--)
		{
			if(B[y]<-f) break;
			if(B[y]&1) a++;
			else b++;
		}
		if(i&1) cut[f] = a;
		else cut[f] = b;

		if(A[i]==0) ans -= cut[f];
		else ans -= f+1;

		//if(A[i]==0) printf("%d\n",cut[f]);
		//else printf("%d\n",f+1);
		f++;
	}

	f -= 2;
	for(;i<=n+n;i++)
	{
		if(A[i]==0) ans -= cut[f];
		else ans -= f+1;
		//if(A[i]==0) printf("%d\n",cut[f]);
		//else printf("%d\n",f+1);
		f--;
	}
	cout<<ans<<endl;

	return 0;
}
