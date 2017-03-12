#include <bits/stdc++.h>
using namespace std;

#define LL long long

const int pp=(1e9)+7;
typedef int arr[2][2];
arr A,B;
int Test,N,len,ans;

int q[110];

void Multi(arr A,arr B,arr &C){
	arr s;
	memset(s,0,sizeof(s));
	for (int i=0;i<2;i++)
		for (int j=0;j<2;j++)
			for (int k=0;k<2;k++)
				s[i][j]=(s[i][j]+(LL)A[i][k]*B[k][j]%pp)%pp;
	for (int i=0;i<2;i++)
		for (int j=0;j<2;j++)
			C[i][j]=s[i][j];
}

int quick(int x,int y){
	int s=1,t=x;
	for (;y;y>>=1){
		if (y&1)s=(LL)s*t%pp;
		t=(LL)t*t%pp;
	}
	return s;
}

int phi(int n){
	int s=1;
	for (int i=1;i<=len;i++)
		if (n%q[i]==0){
			s=s*(q[i]-1);
			n/=q[i];
			while (n%q[i]==0){
				n/=q[i];
				s*=q[i];
			}
		}
	return s;
}

int f(int n){
	if (n==1)return 1;
	A[0][0]=1;A[0][1]=3;
	B[0][0]=0;B[0][1]=1;
	B[1][0]=1;B[1][1]=1;
	n-=2;
	for (;n;n>>=1){
		if (n&1)Multi(A,B,A);
		Multi(B,B,B);
	}
	return A[0][1];
}

void split(int N){
	len=0;
	for (int d=2;d<=sqrt(N);d++)
		if (N%d==0){
			if (d>1)q[++len]=d;
			while (N%d==0)
				N/=d;
		}
	if (N>1)q[++len]=N;
	sort(q+1,q+len+1);
}

int main(){
	freopen("1001.in","r",stdin);
	freopen("1001.out","w",stdout);
	while (scanf("%d",&N)!=EOF){
		if (N==1){
			printf("2\n");
			continue;
		}
		split(N);
		ans=0;
		for (int d=1;d<=sqrt(N);d++)
			if (N%d==0){
				ans=(ans+(LL)f(d)*phi(N/d)%pp)%pp;
				if (d*d!=N)
					ans=(ans+(LL)f(N/d)*phi(d)%pp)%pp;
			}
		ans=(LL)ans*quick(N,pp-2)%pp;
		printf("%d\n",ans);
	}
}
