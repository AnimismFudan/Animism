#include <bits/stdc++.h>
using namespace std;
#define LL long long

int N,M,Q;
int a[60];
int f[60][70];
LL l,r,mid,res;

LL lcm(LL x,LL y){
	return x*y/__gcd(x,y);
}

LL quick(LL x,LL y){
	LL s=1,t=x;
	for (;y;y>>=1){
		if (y&1)s=s*t;
		t=t*t;
	}
	return s;
}

double quickd(LL x,LL y){
	double s=1,t=x;
	for (;y;y>>=1){
		if (y&1)s=s*t;
		t=t*t;
	}
	return s;
}

bool check(LL mid){
	res=0;
	for (int i=1;i<=60;i++)
		if (f[M][i]){
			double t=log(mid)/i;
			LL up=(LL)(exp(t))-1;
			while (1){
				double t=quickd(up+1,i);
				if (t<=mid&&quick(up+1,i)<=mid)
					up++;
					else break;
			}
			res+=(up-1)*f[M][i];
		}
	res+=1;
	return res>=N;
}

int main(){
	scanf("%d",&Q);
	while (Q--){
		scanf("%d%d",&N,&M);
		for (int i=1;i<=M;i++)scanf("%d",&a[i]);
		memset(f,0,sizeof(f));
		f[1][a[1]]=1;
		for (int i=2;i<=M;i++){
			memcpy(f[i],f[i-1],sizeof(f[i]));
			for (int j=1;j<=60;j++)
				if (lcm(j,a[i])<=60)
					f[i][lcm(j,a[i])]-=f[i-1][j];
			f[i][a[i]]++;
		}
		l=1;r=1e17;
		while (l<r){
			mid=(l+r)>>1;
			if (check(mid))r=mid;
			else l=mid+1;
		}
		cout << l <<endl;
	}
}