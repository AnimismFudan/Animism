#include <bits/stdc++.h>
using namespace std;
#define LL long long

const double eps=1e-4;
int N,K,pt;
int st[2510],ne[5010],go[5010];
int size[2510],fa[2510];
class rec{
	public:
	int p,s;
}P[2510];
double mid;
double f[2510][2510];

void Add(int x,int y){ne[++pt]=st[x];st[x]=pt;go[pt]=y;}

void dp(int x){
	size[x]=1;
	f[x][0]=0;
	f[x][1]=P[x].p-P[x].s*mid;
	for (int i=st[x];i;i=ne[i]){
		dp(go[i]);
		for (int j=size[x]+1;j<=size[x]+size[go[i]];j++)
			f[x][j]=-2e18;
		for (int k=size[x];k>=1;k--)
			for (int j=size[go[i]];j>=0;j--)
				f[x][j+k]=max(f[x][j+k],f[x][k]+f[go[i]][j]);
		size[x]+=size[go[i]];
	}
}

bool check(){
	dp(0);
	return (f[0][K+1]>=0);
}

int main(){
	scanf("%d%d",&K,&N);
	for (int i=1;i<=N;i++){
		scanf("%d%d%d",&P[i].s,&P[i].p,&fa[i]);
		Add(fa[i],i);
	}
	double l=0,r=10000;
	while (r-l>eps){
		mid=(l+r)/2;
		if (check())l=mid;
		else r=mid;
	}
	printf("%.3lf\n",l);
}
