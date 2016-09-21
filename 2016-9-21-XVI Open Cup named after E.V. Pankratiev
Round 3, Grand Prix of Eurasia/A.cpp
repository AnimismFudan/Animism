#include <bits/stdc++.h>
using namespace std;

const int MaxN = (int)1e5 + 7;
const double eps = 1e-7;

struct NodeType
{
	double x,y;
	NodeType operator-(NodeType A)
	{
		NodeType res;
		res.x = x-A.x;
		res.y = y-A.y;
		return res;
	}
};

int n,m;
NodeType nod[MaxN],A,B,C;

inline double Cross(NodeType A,NodeType B)
{
	return A.x*B.y-A.y*B.x;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	
	int i,j;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
		scanf("%lf%lf",&nod[i].x,&nod[i].y);
	
	for(i=1;i<=m;i++)
	{
		scanf("%lf%lf%lf%lf",&A.x,&A.y,&B.x,&B.y);
		for(j=1;j<=n;j++)
			if(Cross(B-A,nod[j]-A)<eps)
			{
				//printf("%d %d\n",i,j);
				double a1,b1,c1,a2,b2,c2;
				a1 = B.y-A.y;
				b1 = -B.x+A.x;
				c1 = - a1 * A.x - b1 * A.y;
				//cout<<a1<<' '<<b1<<' '<<c1<<endl;
				a2 = A.x-B.x;
				b2 = -B.y+A.y;
				c2 = - a2 * nod[j].x - b2 * nod[j].y;
				//cout<<a2<<' '<<b2<<' '<<c2<<endl;
				C.x = -(c1*b2-c2*b1) / (a1*b2-a2*b1);
				C.y = -(c1*a2-c2*a1) / (a2*b1-a1*b2);
				nod[j].x = C.x*2.0 - nod[j].x;
				nod[j].y = C.y*2.0 - nod[j].y;
			}
	}
	
	for(i=1;i<=n;i++)
		printf("%lf %lf\n",nod[i].x,nod[i].y);
	
	return 0;
}

