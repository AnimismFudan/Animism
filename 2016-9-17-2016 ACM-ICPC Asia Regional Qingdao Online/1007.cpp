#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MaxN = (int) 1e5 + 7;

int T,n,m,a[MaxN];
priority_queue<ll,vector<ll>,greater<ll> > mq;

void Init()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	sort(a+1,a+n+1);
}

bool Check(int k)
{
	while(!mq.empty()) mq.pop();
	int i,j,tp,fr,tmp;
	ll s,sum = 0;
	tmp = n % (k-1);
	tmp = (tmp + k-3) % (k-1) + 1;
	tmp ++;
	j = (n - tmp)/(k-1);
	tp = 1;
	for(i=1,s=0;i<=tmp;i++)
		s += a[tp++];
	mq.push(s); sum += s;
	fr = s;
	while(j--)
	{
		for(i=1,s=0;i<=k;i++)
			if(tp <= n && a[tp] <= fr) s += a[tp++];
			else
			{
				s += fr;
				mq.pop();
				if(!mq.empty()) fr = mq.top();
				else fr = 1<<20;
			}
		sum += s;
		if(sum>m) return false;
		mq.push(s);
		if(s<fr) fr = s;
	}
	return true;
}

void Solve()
{
	int le,ri,mi;
	le = 2; ri = n;
	while(le<=ri)
	{
		mi = (le+ri)>>1;
		if(Check(mi)) ri = mi-1;
		else le = mi+1;
	}
	printf("%d\n",le);
}

int main()
{
	freopen("1007.in","r",stdin);
	//freopen("1007.out","w",stdout);

	scanf("%d",&T);
	while(T--)
	{
		Init();
		Solve();
	}
	return 0;
}

