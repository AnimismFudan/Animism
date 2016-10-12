#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);
const double eps = 1e-9;

int x,y,phi_,w_;
double phi,w,a,b,v,r,d;

double Dot(double ax,double ay,double bx,double by,double cx,double cy)
{
	return (bx-ax) * (cx-ax) + (by-ay) * (cy-ay);
}

bool Check(double val)
{
	double tim1, tim2, p, q;
	v = val; r = v/w;
//	printf("%lf %lf\n", v, r);
	tim1 = sqrt(d*d - r*r) / v;
	b = acos(1.0*r/d);
//	printf("%lf %lf\n",a,b);
	p = fabs(a+b-phi);
	q = fabs(a-b-phi); 
	if(p >= 2*pi) p -= 2*pi;
	p = min(p, 2*pi - p);
	if(q >= 2*pi) q -= 2*pi;
	q = min(q, 2*pi - q);
//	printf("%lf %lf\n",p,q);
	tim2 = max(p, q) / w;
//	printf("Check %lf : %lf %lf\n",val,tim1, tim2);
	//return (tim1 < tim2 + eps);
	if (tim1 < tim2 + eps)
		return true;
	double x_, y_;
	x_ = r*cos(phi+pi);
	y_ = r*sin(phi+pi);
	tim1 = sqrt((1.0*x-x_)*(1.0*x-x_) + (1.0*y-y_)*(1.0*y-y_)) / v;
	tim2 = pi / w;
	return (Dot(x_,y_,0,0,x,y)<=0 && (tim1 < tim2 + eps));
}

int main()
{
	scanf("%d%d%d%d",&x,&y,&phi_,&w_);
	phi = pi * phi_ / 180.0;
	w = pi * w_ / 180.0;
	a = 0.0;
	if (x>0 && y==0) a = 0.0;
	else if (x==0 && y>0) a = .5*pi;
	else if (x<0 && y==0) a = 1.0*pi;
	else if (x==0 && y<0) a = 1.5*pi;
	else if (x>0 && y>0) a = atan(1.0 * y/x);
	else if (x<0 && y<0) a = pi + atan(1.0 * y/x);
	else if (x<0 && y>0) a = .5*pi + atan(-1.0 * x/y);
	else if (x>0 && y<0) a = 1.5*pi + atan(-1.0 * x/y);
	//printf("%lf\n",a);
	d = sqrt(1.0 * x*x + 1.0 * y*y);
	double le = eps, ri = w * d, mi;
	while (le+eps < ri)
	{
		mi = (le+ri)*.5;
		if(Check(mi)) ri = mi;
		else le = mi;
	}
	printf("%.9lf\n", (le+ri) *.5);
	return 0;
}

