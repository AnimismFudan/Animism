#include <bits/stdc++.h>
using namespace std;
#define LL long long

bool stt;

int N,M,x,y,pt,ans,l,r,tot,last,num;
int q[10010],in[10010],data[10010];
int st[10010],ne[20010],go[20010];
int dfn[10010],low[10010],sta[10010],vis[10010],mark[10010];
bool b[10005][10005];

class rec{
	public:
	int x,y;
}P[10010];

bool enn;

void Add(int x,int y){ne[++pt]=st[x];st[x]=pt;go[pt]=y;}

void tarjan(int x){
	dfn[x]=low[x]=++tot;
	sta[++last]=x;
	vis[x]=1;
	for (int i=st[x];i;i=ne[i])
		if (vis[go[i]]==0){
			tarjan(go[i]);
			low[x]=min(low[x],low[go[i]]);
		}else if (vis[go[i]]==1)low[x]=min(low[x],dfn[go[i]]);
	if (dfn[x]==low[x]){
		++num;
		int p;
		do{
			p=sta[last];
			mark[p]=num;
			vis[p]=2;
			sta[last--]=0;
		}while (p!=x);
	}
}

int main(){
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	scanf("%d%d",&N,&M);
	for (int i=1;i<=M;i++)
		scanf("%d%d",&P[i].x,&P[i].y),Add(P[i].x,P[i].y);
	for (int i=1;i<=N;i++)
		if (!dfn[i])
			tarjan(i);
	memset(st,0,sizeof(st));
	for (int i=1;i<=N;i++)data[mark[i]]++;
	pt=1;
	for (int i=1;i<=M;i++)
		if (mark[P[i].x]!=mark[P[i].y]){
			Add(mark[P[i].x],mark[P[i].y]);
			Add(mark[P[i].y],mark[P[i].x]);
			in[mark[P[i].y]]++;
		}
	l=1;r=0;
	for (int i=1;i<=N;i++)
		if (!in[i])q[++r]=i;
	for (;l<=r;l++){
		int x=q[l];
		for (int i=st[x];i;i=ne[i])
			if (!(i&1)){
				in[go[i]]--;
				if (!in[go[i]])q[++r]=go[i];
			}
	}
	ans=0;
	for (int i=1;i<=N;i++)
		for (int j=1;j<=N;j++){
			int x=q[i],y=q[j];
			if (x==y){
				b[x][y]=1;
				ans+=data[x]*data[y];
				continue;
			}
			for (int k=st[x];k&&!b[x][y];k=ne[k])
				if (k&1&&b[go[k]][y]){
					b[x][y]=1;
					ans+=data[x]*data[y];
				}
			for (int k=st[y];k&&!b[x][y];k=ne[k])
				if (k&1&&b[x][go[k]]){
					b[x][y]=1;
					ans+=data[x]*data[y];
				}
		}
	printf("%d\n",ans);
}