#include <bits/stdc++.h>
using namespace std;
#define LL long long

int N,pt,len;
LL ans;
int f[400010];
int dfn[400010],in[200010],out[200010],dep[200010];
int st[200010],ne[400010],go[400010],fa[200010];

inline int lowbit(int x){return x&-x;}

inline void Add(int x,int y){ne[++pt]=st[x];st[x]=pt;go[pt]=y;}

inline void Init(int x,int data){
	for (;x<=len;x+=lowbit(x))
		f[x]+=data;
}

inline int calc(int x){
	int res=0;
	for (;x;x-=lowbit(x))
		res+=f[x];
	return res;
}

void dfs(int x){
	dfn[++len]=x;in[x]=len;
	for (int i=st[x];i;i=ne[i])
		if (go[i]!=fa[x]){
			fa[go[i]]=x;
			dep[go[i]]=dep[x]+1;
			dfs(go[i]);
		}
	dfn[++len]=x;out[x]=len;
}

inline void deal(int x){
	for (int i=x*2;i<=N;i+=x)
		ans+=calc(in[i]);
}

inline void move_root(int x,int y){
	if (fa[y]==x){
		Init(1,1);
		Init(in[y],-2);
		Init(out[y]+1,2);
	}else{
		Init(1,-1);
		Init(in[x],2);
		Init(out[x]+1,-2);
	}
}

void work(int x){
	deal(x);
	for (int i=st[x];i;i=ne[i])
		if (go[i]!=fa[x]){
			move_root(x,go[i]);
			work(go[i]);
			move_root(go[i],x);
		}
}

int main(){
	scanf("%d",&N);
	for (int i=1;i<N;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		Add(x,y);
		Add(y,x);
	}
	dep[1]=1;
	dfs(1);
	for (int i=1;i<=len;i++)
		Init(i,dep[dfn[i]]-dep[dfn[i-1]]);
	work(1);
	cout<<ans<<endl;
}