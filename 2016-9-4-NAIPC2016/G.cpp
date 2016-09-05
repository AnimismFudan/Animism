#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int MaxN = 1007;
const int MaxM = 1000007;

struct NodeType
{
	int x,y;
};

struct LineType
{
	int A,B,C;
};

int n,m,ans;
NodeType dot[MaxN];
NodeType nod[MaxM];
LineType lin[MaxM];

inline int Gcd(int A,int B)
{
	int C;
	if(A==0) return B;
	while(B)
	{
		C = A;
		A = B;
		B = C%B;
	}
	return A;
}

bool Cmp1(const NodeType A,const NodeType B)
{
	if(A.x==B.x) return (A.y<B.y);
	return (A.x<B.x);
}

bool Cmp2(const LineType A,const LineType B)
{
	if(A.A==B.A)
	{
		if(A.B==B.B) return (A.C<B.C);
		return (A.B<B.B);
	}
	return (A.A<B.A);
}

int main()
{

	//freopen("G.in","r",stdin);
	//freopen("G.out","w",stdout);

	int i,j,k,x,y,d;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		scanf("%d%d",&dot[i].x,&dot[i].y),
		dot[i].x <<= 1, dot[i].y <<= 1;

	ans = 1<<20;

	m = 0;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
		{
			m++;
			nod[m].x = (dot[i].x+dot[j].x)>>1;
			nod[m].y = (dot[i].y+dot[j].y)>>1;
		}
	sort(nod+1,nod+m+1,Cmp1);
	for(i=1;i<=m;i=j)
	{
		for(j=i+1;j<=m && nod[i].x==nod[j].x && nod[i].y==nod[j].y; j++);
		ans = min(ans, n-(j-i));
	}
	m = 0;
	for(i=1;i<n;i++)
		for(j=i+1;j<=n;j++)
		{
			m++;
			x = (dot[i].x+dot[j].x)>>1;
			y = (dot[i].y+dot[j].y)>>1;
			lin[m].A = dot[j].x - dot[i].x;
			lin[m].B = dot[j].y - dot[i].y;
			d = Gcd(lin[m].A,lin[m].B);
			lin[m].A /= d; lin[m].B /= d;
			lin[m].C = -lin[m].A*x -lin[m].B*y;
			if(lin[m].A<0 || (lin[m].A==0&&lin[m].B<0))
				lin[m].A=-lin[m].A,lin[m].B=-lin[m].B,lin[m].C=-lin[m].C;
			//printf("%d %d %d %d %d\n",i,j,lin[m].A,lin[m].B,lin[m].C);
		}
	sort(lin+1,lin+m+1,Cmp2);
	for(i=1;i<=m;i=j)
	{
		for(j=i+1;j<=m && lin[i].A==lin[j].A && lin[i].B==lin[j].B && lin[i].C==lin[j].C; j++);
		d = (j-i)<<1;
		for(k=1;k<=n;k++)
			if((long long)lin[i].A*dot[k].x+(long long)lin[i].B*dot[k].y+lin[i].C==0LL) d++;
		ans = min(ans,n-d);
	}

	for(i=1;i<n;i++)
		for(j=i+1;j<=n;j++)
		{
			d = 0;
			for(k=1;k<=n;k++)
			{
				if((long long)(dot[i].x-dot[j].x)*(dot[i].y-dot[k].y)==(long long)(dot[i].x-dot[k].x)*(dot[i].y-dot[j].y))
					d++;
			}
			ans = min(ans,n-d);
		}

	printf("%d\n",ans);

	return 0;
}
