#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MaxN = 500;

int n,p,s[MaxN];
ll ans;
ll xx,yy;

inline ll ExGCD(ll a,ll b)
{
	if(b==0)
	{
		xx = 1; yy = 0;
		return a;
	}
	ll d = ExGCD(b, a%b), t = xx;
	xx = yy;
	yy = t - a/b * yy;
	return d;
}

void Calc(int st,int ln)
{
	int i; ll a,b,c,d; a = b = c = 0LL;
	double mint, maxt;
	ll t1,t2;
	
	for(i=st;i+ln<=400;i+=ln)
	{
		a += (ll) (s[i+ln-1]-s[i-1]);
		b += (ll) (s[i+ln-1]-s[i-1]) * c;
		c ++;
	}
	a += (ll) (s[400] - s[i-1]);
	b += (ll) (s[400] - s[i-1]) * c;
	
	if(a==0) return;
	
	d = ExGCD(a,b);
	
	if(p%d!=0) return;
	
	if(b==0)
	{
		d = (100-p/a) / c;
		if(d<1) return;
		ans += d;
		return;
	}
	
	xx *= p/d; yy *= p/d;
	a /= d; b /= d;
	
	maxt = 1.0 * (xx-1) / b;
	mint = 1.0 * (1-yy) / a;
	
	if(a*c-b == 0)
		if(100-xx-c*yy<0) return;
	if(a*c-b > 0) maxt = min(maxt, 1.0 * (100-xx-c*yy) / (a*c-b));
	if(a*c-b < 0) mint = max(mint, 1.0 * (100-xx-c*yy) / (a*c-b));
	
	t1 = (ll) mint;
	while(1.0*t1 < mint) t1 ++;
	t2 = (ll) maxt;
	while(maxt < 1.0*t2) t2 --;
	
	/*
	if(st+ln<=400 && st+ln+ln>400)
	{
		printf("%d %d : %d %d %d\n",st,ln, a,b,p);
		printf("%d %d\n",xx,yy);
		printf("%lf %lf : %d %d\n",mint,maxt,t1,t2);
	}
	*/
	
	if(t1<=t2) ans += (t2-t1+1);
	
	return;
}

int main()
{
	freopen("H.in","r",stdin);
	freopen("H.out","w",stdout);
	
	int i,j; char sco[10];
	
	while(scanf("%d%d",&n,&p))
	{
		if(n==0 && p==0) break;
		for(i=0; i<=400; i++) s[i] = 0;
		for(i=1; i<=n; i++)
		{
			scanf("%s",sco);
			j = (sco[0]-'0')*100 + (sco[2]-'0')*10 + (sco[3]-'0');
			s[j] ++;
		}
		for(i=1; i<=400; i++) s[i] += s[i-1];
		
		ans = 0LL;
		for(i=250; i<=400; i++)
			for(j=1; i+j<=400; j++) Calc(i,j);
		
		printf("%lld\n",ans);
	}
	
	return 0;
}

