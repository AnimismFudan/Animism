#include <bits/stdc++.h>
using namespace std;

#define LL long long

typedef vector <int > VI;

const double eps=1e-7;
int N,tot;
double ans;
map <VI , int > Hash;
int aa[30];
double a[30][30];
double dp[1010][30];
int S[30][30];
double P[30];

int sign(double x){
	if (x>eps)return 1;
	if (x<-eps)return -1;
	return 0;
}

VI get_link(VI s,int x,int y){
	VI t;
	t.clear();
	for (int i=0;i<x;i++)
		t.push_back(s[i]);
	for (int i=x+1;i<y;i++)
		t.push_back(s[i]);
	for (int i=y+1;i<s.size();i++)
		t.push_back(s[i]);
	t.push_back(s[x]+s[y]);
	sort(t.begin(),t.end());
	return t;
}

void gauss(){
	int j=1;
	for (int i=1;i<=N;i++){
		int k=j;
		while (k<=N&&!sign(a[k][i]))k++;
		if (k>N)continue;
		for (int t=0;t<=N;t++)swap(a[k][t],a[j][t]);
		for (k=1;k<=N;k++)
			if (k!=j&&sign(a[k][i])){
				double t1=a[j][i],t2=a[k][i];
				for (int t=0;t<=N;t++)
					a[k][t]=a[k][t]-a[j][t]*t2/t1;
			}
		j++;
	}
}

void work(VI s){
	aa[0]=s.size();
	for (int i=0;i<s.size();i++)
		aa[i+1]=s[i];
	int t=Hash[s];
	if (t)return;
	t=Hash[s]=++tot;
	if (s.size()==1){
		for (int i=1;i<=N;i++)dp[t][i]=0;
		return;
	}
	int tot=N*(N-1)/2;
	double P_trans=0;
	for (int i=0;i<s.size();i++)
		for (int j=i+1;j<s.size();j++)
				P_trans+=s[i]*s[j];
	P_trans/=tot;
	for (int x=1;x<=N;x++)
		for (int i=0;i<s.size();i++)
			for (int j=i+1;j<s.size();j++){
				work(get_link(s,i,j));
				int tt=Hash[get_link(s,i,j)];
				for (int k=1;k<=S[x][0];k++)
					dp[t][x]+=dp[tt][S[x][k]]*P[x]*s[i]*s[j]/(tot*S[x][0]);
			}
	memset(a,0,sizeof(a));
	for (int x=1;x<=N;x++){
		a[x][x]+=-1;
		for (int y=1;y<=S[x][0];y++)
			a[x][S[x][y]]+=(1-P[x]*P_trans)/S[x][0];
		a[x][0]+=dp[t][x]+1;
	}
	gauss();
	for (int x=1;x<=N;x++)
		dp[t][x]=-a[x][0]/a[x][x];
}

int main() {
	scanf("%d",&N);
	for (int i=1;i<=N;i++)scanf("%lf",&P[i]);
	for (int i=1;i<=N;i++){
		scanf("%d",&S[i][0]);
		for (int j=1;j<=S[i][0];j++)
			scanf("%d",&S[i][j]);
	}
	work(VI(N,1));
	ans=dp[1][1];
	printf("%.10lf\n",ans);
}