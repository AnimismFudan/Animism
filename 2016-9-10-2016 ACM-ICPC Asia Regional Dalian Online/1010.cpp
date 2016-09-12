#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

#define ll long long

const int MaxN = 100007;

int T,n,lsn;
int a[MaxN],b[MaxN],tre[MaxN];
ll m,cnt;
vector<int> iv[MaxN];
bool in[MaxN];

inline int BinS(ll dt)
{
	int le,ri,mi;
	le = 1; ri = lsn;
	while(le<=ri)
	{
		mi = (le+ri)>>1;
		if(b[mi]<=dt) le = mi+1;
		else ri = mi-1;
	}
	return le-1;
}

inline int lowbit(int x) {return x&(x^(x-1));}

inline int Calc(int x)
{
	int s = 0;
	//printf("Calc %d\n",x);
	while(x)
		s += tre[x], x -= lowbit(x);
	return s;
}

void Add(int x,int d)
{
	while(x<=lsn)
		tre[x] +=d, x += lowbit(x);
}

void DFS(int x)
{
	cnt += Calc(BinS(m/b[a[x]]));
	Add(a[x],1);
	for(int i=0;i<iv[x].size();i++)
		DFS(iv[x][i]);
	Add(a[x],-1);
}

register char *_sp __asm__("rsp");

int main()
{
	const int size=32*1024*1024;
	static char *sys, *mine(new char[size]+size-4096);
	sys=_sp;
	_sp=mine;
	
	freopen("1010.in","r",stdin);
	//freopen("1010.out","w",stdout);
	
	int i,j,u,v;
	
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%lld",&n,&m);
		for(i=1;i<=n;i++) iv[i].clear();
		for(i=1;i<=n;i++)
			scanf("%d",a+i), in[i] = false, b[i] = a[i];
		
		sort(b+1,b+n+1);
		for(i=j=1;i<=n;i++)
			if(b[i]!=b[j]) b[++j] = b[i];
		lsn = j;
		for(i=1;i<=n;i++) a[i] = BinS(a[i]);
		
		for(i=1;i<n;i++)
			scanf("%d%d",&u,&v), in[v] = true,
			iv[u].push_back(v);
		for(i=1;i<=n;i++)
			if(!in[i]) break;
		
		cnt = 0;
		DFS(i);
		printf("%lld\n",cnt);
	}
	
	_sp=sys;
	
	return 0;
}

