#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int MaxN = 5007;
const int oo = 2147483647;

int n,m,a[MaxN];
int f[2][MaxN],cost[MaxN][MaxN];
int tp,st[MaxN],l[MaxN],r[MaxN];

inline int Calc(int flg,int loc,int duan)
{
	if(duan>=loc) return oo;
	return f[flg][duan] + cost[duan+1][loc];
}

int main()
{
	//freopen("K.in","r",stdin);
	//freopen("K.out","w",stdout);

	int i,j,k,nw,ed;

	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
		scanf("%d",a+i);
	for(i=1;i<=n;i++)
		for(j=i;j<=n;j++)
			cost[i][j] = cost[i][j-1] + a[j]*(j-i+1);

	for(i=1;i<=n;i++) f[1][i] = cost[1][i];

	for(j=2;j<=m;j++)
	{
		nw = j&1; ed = nw^1;
		tp = 1; st[tp] = j-1; l[tp] = j; r[tp] = n;
		for(i=j;i<=n;i++)
		{
			while(tp>=1 && Calc(ed,l[tp],st[tp])>Calc(ed,l[tp],i)) tp--;
			int le = l[tp], ri = n, mi;
			while(le<=ri)
			{
				mi = (le+ri)>>1;
				if(Calc(ed,mi,st[tp])<=Calc(ed,mi,i)) le = mi+1;
				else ri = mi-1;
			}
			k = le;
			if(k<=n)
			{
				r[tp] = k-1; st[++tp] = i;
				l[tp] = k; r[tp] = n;
			}
		}
		//printf("%d\n",j);
		//for(i=1;i<=tp;i++) printf("%d : %d %d\n",st[i],l[i],r[i]);
		for(i=1;i<=tp;i++)
			for(k=l[i];k<=r[i];k++)
			{
				f[nw][k] = f[ed][st[i]]+cost[st[i]+1][k];
				//printf("%d(%d %d) ",f[nw][k],k,st[i]);
			}
		//printf("\n");
	}

	printf("%d\n",f[m&1][n]);
	return 0;
}
