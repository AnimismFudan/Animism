#include <bits/stdc++.h>
using namespace std;

#define LL long long

LL Test,N,pt,len,tot,lslen;
LL K,ans,res;
LL st[100010],ne[200010],go[200010],fa[100010];
LL a[100010],ls[100010];
LL dfn[100010],in[100010],out[100010];
LL root[100010];

class segleaf{
	public:
	LL l,r,s;
}seg[3000010];

void Add(LL x,LL y){ne[++pt]=st[x];st[x]=pt;go[pt]=y;}

void get_dfn(LL x){
	dfn[++len]=x;in[x]=len;
	for (LL i=st[x];i;i=ne[i])
		if (go[i]!=fa[x]){
			fa[go[i]]=x;
			get_dfn(go[i]);
		}
	out[x]=len;
}

void Insert(LL &x,LL xx,LL l,LL r,LL t){
	x=++tot;
	seg[x]=seg[xx];
	seg[x].s++;
	if (l==r)return;
	LL mid=(l+r)>>1;
	if (t<=mid)Insert(seg[x].l,seg[xx].l,l,mid,t);
	else Insert(seg[x].r,seg[xx].r,mid+1,r,t);
}

LL calc(LL xl,LL xr,LL l,LL r,LL ll,LL rr){
	if (l==ll&&r==rr)return seg[xr].s-seg[xl].s;
	LL mid=(l+r)>>1;
	if (rr<=mid)return calc(seg[xl].l,seg[xr].l,l,mid,ll,rr);
	else if (ll>mid)return calc(seg[xl].r,seg[xr].r,mid+1,r,ll,rr);
	else return calc(seg[xl].l,seg[xr].l,l,mid,ll,mid)+calc(seg[xl].r,seg[xr].r,mid+1,r,mid+1,rr);
}

register char *_sp __asm__("rsp");

int main(){
	const LL size=32*1024*1024;
	static char *sys, *mine(new char[size]+size-4096);
	sys=_sp;
	_sp=mine;
	
	freopen("1010.in","r",stdin);
	freopen("1010.out","w",stdout);
	scanf("%I64d",&Test);
	while (Test--){
		memset(st,0,sizeof(st));pt=0;
		memset(fa,0,sizeof(fa));
		scanf("%I64d%I64d",&N,&K);
		for (LL i=1;i<=N;i++)scanf("%I64d",&a[i]);
		memcpy(ls,a,sizeof(ls));
		sort(ls+1,ls+N+1);
		lslen=unique(ls+1,ls+N+1)-(ls+1);
		for (LL i=1;i<=N;i++)
			a[i]=lower_bound(ls+1,ls+lslen+1,a[i])-ls;
		for (LL i=1;i<N;i++){
			LL x,y;
			scanf("%I64d%I64d",&x,&y);
			Add(x,y);
			Add(y,x);
		}
		len=0;
		get_dfn(1);
		root[0]=0;tot=0;
		for (LL i=1;i<=N;i++)
			Insert(root[i],root[i-1],1,lslen,a[dfn[i]]);
		ans=0;
		for (LL i=1;i<=N;i++){
			LL up=upper_bound(ls+1,ls+lslen+1,K/ls[a[i]])-ls-1;
			if (!up)continue;
			res=calc(root[in[i]-1],root[out[i]],1,lslen,1,up);
			if ((LL)ls[a[i]]*ls[a[i]]<=K)res--;
			ans+=res;
		}
		printf("%I64d\n",ans);
	}
	
	_sp=sys;
}
