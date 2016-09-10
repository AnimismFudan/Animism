#include <bits/stdc++.h>
using namespace std;
#define LL long long

int N,M,K,pt,l,r,tot;
bool vis[70000];
int q[7000000];
double ans,f[1<<6][70000];
int st[70000],ne[10000010],go[10000010];
double w[10000010];
int name[50][50][50];

void Add(int x,int y,double ww){ne[++pt]=st[x];st[x]=pt;go[pt]=y;w[pt]=ww;}

class poi{
	public:
	double x,y;
	int c;
	poi operator - (const poi &X)const{
		poi C;
		C.x=x-X.x;
		C.y=y-X.y;
		return C;
	}
}light[310],P[310];

class tri{
	public:
	double l;
	int c;
}T[70000];

double xet(poi A,poi B){
	return A.x*B.y-B.x*A.y;
}

double dot(poi A,poi B){
	return A.x*B.x+A.y*B.y;
}

double dist(poi A,poi B){
	return sqrt(dot(B-A,B-A));
}

bool inside(poi A,poi B,poi C,poi D){
	if (xet(B-A,D-A)*xet(C-A,D-A)>0)return 0;
	if (xet(A-B,D-B)*xet(C-B,D-B)>0)return 0;
	if (xet(A-C,D-C)*xet(B-C,D-C)>0)return 0;
	return 1;
}

int calc(int a,int b,int c){
	if (a>b)swap(a,b);
	if (a>c)swap(a,c);
	if (b>c)swap(b,c);
	return name[a][b][c];
}

int main(){
	scanf("%d%d%d",&N,&M,&K);
	for (int i=1;i<=N;i++)scanf("%lf%lf",&light[i].x,&light[i].y);
	for (int i=1;i<=N;i++)scanf("%d",&light[i].c);
	for (int i=1;i<=M;i++)scanf("%lf%lf",&P[i].x,&P[i].y);
	for (int i=1;i<=M;i++)
		for (int j=i+1;j<=M;j++)
			for (int k=j+1;k<=M;k++){
				if (xet(P[j]-P[i],P[k]-P[i])==0)continue;
				name[i][j][k]=++tot;
				T[calc(i,j,k)].l=dist(P[i],P[j])+dist(P[i],P[k])+dist(P[j],P[k]);
				for (int t=1;t<=N;t++)
					if (inside(P[i],P[j],P[k],light[t]))
						T[calc(i,j,k)].c|=1<<(light[t].c-1);
			}
	for (int i=1;i<=M;i++)
		for (int j=i+1;j<=M;j++)
			if (dist(P[i],P[j])>0)
				for (int a=1;a<=M;a++)
					for (int b=a+1;b<=M;b++){
						if (xet(P[j]-P[i],P[a]-P[i])==0)continue;
						if (xet(P[j]-P[i],P[b]-P[i])==0)continue;
						Add(calc(i,j,a),calc(i,j,b),2*dist(P[i],P[j]));
						Add(calc(i,j,b),calc(i,j,a),2*dist(P[i],P[j]));
					}
	for (int c=0;c<1<<K;c++)
		for (int i=1;i<=M*M*M;i++)
			f[c][i]=1e18;
	for (int i=1;i<=M*M*M;i++)
		if (T[i].c)
			f[T[i].c][i]=T[i].l;
	for (int c=1;c<1<<K;c++){
		l=1;r=0;
		memset(vis,0,sizeof(vis));
		for (int i=1;i<=M*M*M;i++)
			if (f[c][i]<1e18)
				q[++r]=i,vis[i]=1;
		for (;l<=r;l++){
			int x=q[l];
			vis[x]=0;
			for (int i=st[x];i;i=ne[i]){
				int cc=c|T[go[i]].c;
				if (f[cc][go[i]]>f[c][x]+T[go[i]].l-w[i]){
					f[cc][go[i]]=f[c][x]+T[go[i]].l-w[i];
					if (f[cc][go[i]]<0)
						printf("= =");
					if (cc==c&&!vis[go[i]]){
						q[++r]=go[i];
						vis[go[i]]=0;
					}
				}
			}
		}
	}
	ans=2e18;
	for (int i=1;i<=M*M*M;i++)
		ans=min(ans,f[(1<<K)-1][i]);
	if (ans>1e9)printf("-1\n");
	else printf("%.10lf\n",ans);
}