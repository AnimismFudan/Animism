#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MaxN = 51;
const int mod = (int)1e9 + 7;

int T,idx,n,m,id[10];
bool lnk[MaxN][MaxN];
ll ans;

inline ll QckM(ll a, ll b)
{
	ll s = 1;
	while(b)
	{
		if(b&1) s = s*a%mod;
		a = a*a%mod; b>>=1;
	}
	return s;
}

void DFS(int x,int s)
{
	if(x>n || s==5)
	{
		if(s<3) {ans--; return;}
		int i,j,k;
		for(i=1;i<=s;i++)
			for(j=i+1;j<=s;j++)
				for(k=j+1;k<=s;k++)
					if(lnk[id[i]][id[j]] && lnk[id[i]][id[k]] && lnk[id[j]][id[k]]) return;
					else if(!lnk[id[i]][id[j]] && !lnk[id[j]][id[k]] && !lnk[id[i]][id[k]]) return;
		ans--; return;
	}
	DFS(x+1,s);
	id[s+1] = x;
	DFS(x+1,s+1);
}

int main()
{
	int i,a,b;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		for(a=1; a<=n; a++)
			for(b=1; b<=n; b++) lnk[a][b] = false;
		for(i=1; i<=m; i++)
			scanf("%d%d",&a,&b),
			lnk[a][b] = lnk[b][a] = true;
		printf("Case #%d: ",++idx);
		ans = QckM(2,n);
		DFS(1,0);
		ans %= mod;
		if(ans<0) ans += mod;
		printf("%lld\n",ans);
	}
	return 0;
}

