#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

#define ll long long

const int MaxL = 1000007;

struct SegmentType
{
	int l,r,f,k; ll b;
};

int h,w,n,m; ll tot;
bool tu[MaxL]; char st[MaxL];
SegmentType seg[2][MaxL<<2];

inline int ID_Hang(int x,int y) {return x*w+y;}
inline int ID_Lie(int x,int y) {return y*h+x;}

void MakeSeg(int x,int l,int r)
{
	seg[0][x].l = seg[1][x].l = l;
	seg[0][x].r = seg[1][x].r = r;

	seg[0][x].f = seg[1][x].f = 0;
	seg[0][x].k = seg[1][x].k = 0;
	seg[0][x].b = seg[1][x].b = 0LL;

	if(l!=r)
	{
		int lc = x<<1, mi = (l+r)>>1;
		MakeSeg(lc,l,mi);
		MakeSeg(lc+1,mi+1,r);
	}
}

inline void Download(int x,int f)
{
	int lc = x<<1;
	seg[f][lc].f = seg[f][lc+1].f = 1; seg[f][x].f = 0;
	seg[f][lc].k = seg[f][lc+1].k = seg[f][x].k; seg[f][x].k = 0;
	seg[f][lc].b = seg[f][lc+1].b = seg[f][x].b; seg[f][x].b = 0;
}

inline void Updata(int x,int f,int l,int r,int k,ll b)
{
	if(l<=seg[f][x].l && seg[f][x].r<=r)
	{
		seg[f][x].f = 1;
		seg[f][x].k = k; seg[f][x].b = b;
		return;
	}
	if(seg[f][x].f) Download(x,f);
	int lc = x<<1;
	if(l<=seg[f][lc].r) Updata(lc,f,l,r,k,b);
	if(r>seg[f][lc].r) Updata(lc+1,f,l,r,k,b);
}

void Init()
{
	int i,j,x,y,nx,ny;
	scanf("%d%d%d",&h,&w,&n); m = h*w;
	for(i=0;i<h;i++)
	{
		scanf("%s",st);
		for(j=0;j<w;j++)
			tu[ID_Hang(i,j)] = (st[j]=='#');
	}
	MakeSeg(1,0,m-1);

	//printf("Finish Make Segment-tree!\n");

	ll tim = 1; x = h-1; y = 0;
	for(i=1;i<=n;i++)
	{
		scanf("%s%d",st,&j);
		//printf("%s %d\n",st,j);
		if(st[0]=='u')
		{
			nx = x-j; ny = y;
			Updata(1,1,ID_Lie(nx,ny),ID_Lie(x,y),-1,tim+ID_Lie(x,y));
		}
		else if(st[0]=='r')
		{
			nx = x; ny = y+j;
			Updata(1,0,ID_Hang(x,y),ID_Hang(nx,ny),1,tim-ID_Hang(x,y));
		}
		else if(st[0]=='d')
		{
			nx = x+j; ny = y;
			Updata(1,1,ID_Lie(x,y),ID_Lie(nx,ny),1,tim-ID_Lie(x,y));
		}
		else if(st[0]=='l')
		{
			nx = x; ny = y-j;
			Updata(1,0,ID_Hang(nx,ny),ID_Hang(x,y),-1,tim+ID_Hang(x,y));
		}
		//printf("(%d,%d)  (%d,%d)\n",x,y,nx,ny);
		tim += j; x = nx; y = ny;
	}
	tot = tim+1;
}

inline ll Calc(int x,int f,int id)
{
	if(seg[f][x].l==seg[f][x].r)
		return (ll)seg[f][x].l * seg[f][x].k + seg[f][x].b;
	if(seg[f][x].f) Download(x,f);
	int lc = x<<1;
	if(id<=seg[f][lc].r) return Calc(lc,f,id);
	return Calc(lc+1,f,id);
}

void Solve()
{
	int i,j; ll tim,sttim,edtim;

	sttim = 0; edtim = tot; 

	for(i=0;i<h;i++)
		for(j=0;j<w;j++)
		{
			tim = max(Calc(1,0,ID_Hang(i,j)),Calc(1,1,ID_Lie(i,j)));
			//printf("%d %d %d %lld\n",i,j,tu[ID_Hang(i,j)],tim);
			if(tu[ID_Hang(i,j)])
			{
				if(tim==0) sttim = (ll) 1e18;
				else sttim = max(sttim,tim);
			}
			else
			{
				if(tim!=0) edtim = min(edtim,tim);
			}
		}

	edtim --;
	//printf("%lld %lld\n",sttim,edtim);
	if(sttim > edtim) printf("-1 -1\n");
	else printf("%lld %lld\n",sttim,edtim);
}

int main()
{
	//freopen("J.in","r",stdin);
	//freopen("J.out","w",stdout);

	Init();
	Solve();

	return 0;
}
