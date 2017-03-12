#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MaxL = (int)1e5 + 7;

ll l,k,n,m;
ll q[MaxL],a[MaxL];

int main()
{
	freopen("next-partition-rle.in","r",stdin);
	freopen("next-partition-rle.out","w",stdout);
	
	int i,j;
	
	scanf("%lld",&l);
	for(i=1;i<=l;i++)
	{
		scanf("%lld%lld",q+i,a+i);
	}
	
	for(i=l-1;i>=1;i--)
	{
		n += (ll) q[i+1] * a[i+1];
		m += q[i+1];
		if((a[i]-1) * m >= n + 1)
		{
	    	ll x = a[i];
	    	ll t = (n+1-m)/(x-2);
	    	if((n+1-m) % (x-2) == 0)
	    	{
	    		if(q[i]==1) a[i]--, q[i] = t+1;
	    		else q[i]--, i++, a[i] = a[i-1]-1,q[i] = t+1;
	    		l = i;
	    		if(t!=m)
	    		{
	    			l++;
	    			a[l] = 1; q[l] = m-t;
	    		}
	    	}
	    	else
	    	{
	    		if(q[i]==1) a[i]--, q[i] = t+1;
	    		else q[i]--, i++, a[i] = a[i-1]-1, q[i] = t+1;
	    		l = i;
	    		a[++l] = (n+1-m) % (x-2) + 1;
	    		q[l] = 1;
	    		if(t!=m-1)
	    		{
	    			l++;
	    			a[l] = 1; q[l] = m-t-1;
	    		}
	    	}
			printf("%lld\n",l);
			for(j=1;j<=l;j++)
				printf("%lld %lld\n",q[j],a[j]);
			return 0;
		}
	}
	printf("-1\n");
	
	return 0;
}

