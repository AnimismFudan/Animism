#include <bits/stdc++.h>
using namespace std;
#define LL long long

int N,K;
int f[40000010];
class rec{
	public:
	int a,c,s;
}P[100010];

bool cmp(const rec &A,const rec &B){
	if (A.c!=B.c)return A.c>B.c;
	int t1=A.a,t2=B.a;
	if (t1!=1)t1=5-t1;
	if (t2!=1)t2=5-t2;
	return t1<t2;
}

int calc(int i,int j,int k){
	return i*(K+1)*(K+1)+j*(K+1)+k;
}

int main(){
	scanf("%d%d",&N,&K);
	for (int i=1;i<=N;i++)scanf("%d%d%d",&P[i].a,&P[i].c,&P[i].s);
	sort(P+1,P+N+1,cmp);
	memset(f,61,sizeof(f));
	f[calc(0,0,0)]=0;
	for (int i=1;i<=N;i++)
		for (int j=0;j<=K;j++)
			for (int k=0;k<=j;k++){
				int t;
				int tt=calc(i-1,j,k);
				if (f[tt]<0)continue;
				if (P[i].a==1||P[i].a==3){
					t=calc(i,j+1,k);
					f[t]=min(f[t],f[tt]+P[i].s);
				}
				if ((P[i].a==2||P[i].a==3)&&j>=k+1){
					t=calc(i,j,k+1);
					f[t]=min(f[t],f[tt]+P[i].s);
				}
				t=calc(i,j,k);
				f[t]=min(f[t],f[tt]);
			}
	printf("%d",f[calc(N,K,K)]);
}