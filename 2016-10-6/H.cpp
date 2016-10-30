#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MaxN = (int)1e7;

struct Triangle
{
	int a,b,nxt;
};

int n,m,fir[MaxN];
Triangle tri[MaxN];
ll S,C;

void Add(int c,int a,int b)
{
	//cout << a << ' ' << b << ' ' << c <<endl;
	m++; tri[m].nxt = fir[c]; fir[c] = m;
	tri[m].a = a; tri[m].b = b;
}

void MakeTri()
{
	int i,j,a,b,c,d;
	n = 10000;
	for(i=1; i<=n; i++)
		for(j=0; j<=i; j++)
		{
			d = i*i - j*j; c = sqrt(1.0*d);
			if(d == c*c)
			{
				a = i; b = j;
				Add(a,b,c);
			}
		}
}

bool Check(int a, int b, int c)
{
	int i,j; int x1,x2,x3,y1,y2,y3;
	/*
	cout << "length: " << a << endl;
	for(i=fir[a]; i; i=tri[i].nxt)
		printf("%d %d\n",tri[i].a,tri[i].b);
	cout << endl;
	
	for(i=fir[b]; i; i=tri[i].nxt)
		printf("%d %d\n",tri[i].a,tri[i].b);
	
	for(i=fir[c]; i; i=tri[i].nxt)
		printf("%d %d\n",tri[i].a,tri[i].b);
	*/
	for(i=fir[a]; i; i=tri[i].nxt)
	{
		x1 = tri[i].a; y1 = tri[i].b;
		for(j=fir[b]; j; j=tri[j].nxt)
		{
			x2 = tri[j].a; y2 = tri[j].b;
			x3 = abs(x1-x2); y3 = abs(y1-y2);
			if(x3*x3 + y3*y3 == c*c)
			{
				printf("Dream\n");
				printf("0 0\n%d %d\n%d %d\n",x1,y1,x2,y2);
				return true;
			}
			x3 = abs(x1-x2); y3 = abs(y1+y2);
			if(x3*x3 + y3*y3 == c*c)
			{
				printf("Dream\n");
				printf("0 0\n%d %d\n%d %d\n",x1,y1,x2,-y2);
				return true;
			}
		}
	}
	return false;
}

int main()
{
	//freopen("test.in","r",stdin);
	//freopen("H.out","w",stdout);
	MakeTri();
	
	int a,b,c; ll x,y,t;
	
	cin>>S>>C;
	S = 4*S*S;
	if(S%C != 0)
	{
		printf("Flag\n");
		return 0;
	}
	S /= C;
	for(a=1; a<C; a++)
	{
		x = C-a; // x = b+c
		if(x<=a) continue;
		if(S % (x-a) != 0) continue;
		t = S/(x-a);
		t = a*a - t;
		if(t<0) continue;
		y = (ll)sqrt(1.0*t);
		if(t != y*y) continue;
		if((x&1) != (y&1)) continue;
		b = (x+y)/2;
		c = (x-y)/2;
		//printf("%d %d %d\n",a,b,c);
		if(Check(a,b,c)||Check(a,c,b)) return 0;
	}
	printf("Flag\n");
	return 0;
}

