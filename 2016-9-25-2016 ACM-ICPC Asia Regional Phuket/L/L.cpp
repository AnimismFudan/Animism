#include <bits/stdc++.h>
using namespace std;

int T,a,b,c,w,x,y,z;

int main()
{
	freopen("L.in","r",stdin);
	x = y = z = 0;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&a,&b,&c);
		x += a; y += b; z += c;
		w = min(x,min(y,z));
		if(w<30) printf("NO\n");
		else
		{
			printf("%d\n",w);
			x -= w; y -= w; z -= w;
		}
	}
	return 0;
}

