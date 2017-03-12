#include <bits/stdc++.h>
using namespace std;

int Test,N,M,l,r,S;
int dist[200010],f[200010],q[200010];

int findset(int x){
	if (x==f[x])return x;
	return f[x]=findset(f[x]);
}

class line{
	public:
	int x,y;
	bool operator < (const line &X)const{
		if (x!=X.x)return x<X.x;
		return y<X.y;
	}
}p,P[5600];

set <line > Has;

int main(){
	freopen("1009.in","r",stdin);
	freopen("1009.out","w",stdout);
	scanf("%d",&Test);
	while (Test--){
		scanf("%d%d",&N,&M);
		for (int i=1;i<=M;i++){
			scanf("%d%d",&P[i].x,&P[i].y);
			p=P[i];
			Has.insert(p);
			swap(p.x,p.y);
			Has.insert(p);
		}
		scanf("%d",&S);
		for (int i=1;i<=N+1;i++)f[i]=i,dist[i]=2e9;
		dist[S]=0;f[S]=S+1;
		for (q[l=r=0]=S;l<=r;l++){
			int x=q[l];
			int y=findset(1);
			for (;y<=N;y=findset(y+1)){
				p.x=x;p.y=y;
				if (Has.find(p)!=Has.end())continue;
				dist[y]=dist[x]+1;
				f[y]=y+1;
				q[++r]=y;
			}
		}
		Has.clear();
		int num=0;
		for (int i=1;i<=N;i++)
			if (i!=S){
				if (num)printf(" ");
				if (dist[i]!=2e9)printf("%d",dist[i]);
				else printf("-1");
				num++;
			}
		printf("\n");
	}
}
