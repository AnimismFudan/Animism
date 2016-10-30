#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("test.in","w",stdout);
	int x1,x2,y1,y2;
	for(x1 = -100; x1<=100; x1++)
		for(y1 = -100; y1<=100; y1++)
			for(x2 = -100; x2<=100; x2++)
				for(y2 = -100; y2<=100; y2++)
				{
					if(x1==0&&y1==0) continue;
					if(x2==0&&y2==0) continue;
					if(x1==x2 && y1==y2) continue;
					int a = (int) sqrt(1.0*x1*x1 + 1.0*y1*y1);
					if(a*a != x1*x1+y1*y1) continue;
					int b = (int) sqrt(1.0*x2*x2 + 1.0*y2*y2);
					if(b*b != x2*x2+y2*y2) continue;
					int c = (int) sqrt(1.0*(x2-x1)*(x2-x1) + 1.0*(y2-y1)*(y2-y1));
					if(c*c != (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)) continue;
					if(a+b<=c || b+c<=a || a+c<=b) continue;
					long long ss = (long long)x1*y2-(long long)x2*y1;
					if(ss<0) ss = -ss;
					if(ss<=10000)
					{
						cout << ss << ' ' << a+b+c << endl;
						cout << a << ' '<< b << ' '<<c<<endl;
						printf("(%d,%d)\n",0,0);
						printf("(%d,%d)\n",x1,y1);
						printf("(%d,%d)\n",x2,y2);
					}
				}
	return 0;
}

