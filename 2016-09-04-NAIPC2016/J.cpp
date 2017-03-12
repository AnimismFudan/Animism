#include <bits/stdc++.h>
using namespace std;
#define LL long long

int N,M,K;
LL ans1,ans2,tim;
char s[1000010],ss[1000010];
const int fx[4]={-1,1,0,0};
const int fy[4]={0,0,-1,1};

class rec{
	public:
	int fx,d;
}P[1000010];

class segleaf{
	public:
	LL k,b,s;
};

class Segment_Tree{
	public:
	segleaf seg[4000010];
	void mark_down(int x,int l,int r){
		if (!seg[x].k)return;
		if (l<r){
			seg[x<<1].k=seg[x].k;
			seg[x<<1].b=seg[x].b;
			seg[(x<<1)+1].k=seg[x].k;
			seg[(x<<1)+1].b=seg[x].b;
		}else seg[x].s=seg[x].k*l+seg[x].b;
		seg[x].k=seg[x].b=0;
	}
	void change(int x,int l,int r,int ll,int rr,int k,LL b){
		mark_down(x,l,r);
		if (l==ll&&r==rr){
			seg[x].k=k;seg[x].b=b;
			if (l==r)
				seg[x].s=seg[x].k*l+seg[x].b;
			return;
		}
		int mid=(l+r)>>1;
		if (rr<=mid)change(x<<1,l,mid,ll,rr,k,b);
		else if (ll>mid)change((x<<1)+1,mid+1,r,ll,rr,k,b);
		else change(x<<1,l,mid,ll,mid,k,b),change((x<<1)+1,mid+1,r,mid+1,rr,k,b);
	}
	LL calc(int x,int l,int r,int t){
		mark_down(x,l,r);
		if (l==r)
			return seg[x].s;
		int mid=(l+r)>>1;
		if (t<=mid)return calc(x<<1,l,mid,t);
		else return calc((x<<1)+1,mid+1,r,t);
	}
}Row,Column;

int calc_row(int x,int y){
	return x*M+y+1;
}

int calc_column(int x,int y){
	return y*N+x+1;
}

int main(){
	freopen("J.in","r",stdin);
	freopen("J.out","w",stdout);
	scanf("%d%d%d",&N,&M,&K);
	for (int i=0;i<N;i++){
		scanf("%s",ss);
		for (int j=0;j<M;j++)
			s[calc_row(i,j)]=ss[j];
	}
	for (int i=0;i<K;i++){
		scanf("%s",ss);
		if (ss[0]=='u')P[i].fx=0;
		if (ss[0]=='d')P[i].fx=1;
		if (ss[0]=='l')P[i].fx=2;
		if (ss[0]=='r')P[i].fx=3;
		scanf("%d",&P[i].d);
	}
	int x=N-1,y=0;
	tim=1;
	for (int i=0;i<K;i++){
		int xx=x+P[i].d*fx[P[i].fx];
		int yy=y+P[i].d*fy[P[i].fx];
		if (x==xx){
			if (y<yy)
				Row.change(1,1,N*M,calc_row(x,y),calc_row(xx,yy),1,tim-calc_row(x,y));
			else
				Row.change(1,1,N*M,calc_row(xx,yy),calc_row(x,y),-1,tim+calc_row(x,y));
		}else{
			if (x<xx)
				Column.change(1,1,N*M,calc_column(x,y),calc_column(xx,yy),1,tim-calc_column(x,y));
			else
				Column.change(1,1,N*M,calc_column(xx,yy),calc_column(x,y),-1,tim+calc_column(x,y));
		}
		x=xx;y=yy;tim+=P[i].d;
	}
	ans1=0,ans2=tim+1;
	for (int i=0;i<N;i++)
		for (int j=0;j<M;j++)
			if (s[calc_row(i,j)]=='#'){
				LL t1,t2;
				t1=Row.calc(1,1,N*M,calc_row(i,j));
				t2=Column.calc(1,1,N*M,calc_column(i,j));
				if (t1||t2){
					ans1=max(ans1,t1);
					ans1=max(ans1,t2);
				}else ans1=2e18;
			}else{
				LL t1,t2;
				t1=Row.calc(1,1,N*M,calc_row(i,j));
				t2=Column.calc(1,1,N*M,calc_column(i,j));
				if (t1||t2)
					ans2=min(ans2,max(t1,t2));
			}
	ans2--;
	if (ans1<=ans2)cout<<ans1<<' '<<ans2<<endl;
	else cout<<"-1 -1"<<endl;
}