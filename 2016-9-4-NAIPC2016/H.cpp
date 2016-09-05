#include <bits/stdc++.h>
using namespace std;
#define LL long long

int N,K;
int f[610][310];
int nex[1000010],pre[310];
LL dp[100010];

class rec{
	public:
	int s,v;
}P[1000010];

bool cmpv(const rec &A,const rec &B){
	return A.v<B.v;
}

int main(){
	freopen("H.in","r",stdin);
	freopen("H.out","w",stdout);
	scanf("%d%d",&N,&K);
	for (int i=1;i<=N;i++)
		scanf("%d%d",&P[i].s,&P[i].v);
	sort(P+1,P+N+1,cmpv);
	for (int i=1;i<=N;i++){
		nex[i]=pre[P[i].s];
		pre[P[i].s]=i;
	}
	memset(dp,128,sizeof(dp));
	for (int i=1;i<=300;i++)f[0][i]=pre[i];
	dp[0]=0;
	for (int i=1;i<=K;i++){
		int t=i%600;
		int Max=0;
		for (int j=1;j<=300;j++){
			if (i-j<0)continue;
			int tt=t-j;
			if (tt<0)tt+=600;
			if (!f[tt][j])continue;
			if (!Max||dp[i-j]+P[f[tt][j]].v>dp[i]){
				dp[i]=dp[i-j]+P[f[tt][j]].v;
				Max=j;
			}
		}
		if (Max){
			int tt=t-Max;
			if (tt<0)tt+=600;
			for (int j=1;j<=300;j++)
				f[t][j]=f[tt][j];
			f[t][Max]=nex[f[t][Max]];
		}
		if (dp[i]<dp[i-1]){
			int tt=t-1;
			if (tt<0)tt+=600;
			for (int j=1;j<=300;j++)
				f[t][j]=f[tt][j];
			dp[i]=dp[i-1];
		}
	}
	for (int i=1;i<=K;i++){
		cout<<dp[i];
		if (i<K)printf(" ");
		else printf("\n");
	}
}
