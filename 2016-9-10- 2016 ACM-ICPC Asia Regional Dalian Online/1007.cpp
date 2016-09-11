#include <bits/stdc++.h>
using namespace std;

#define LL long long

LL N,M,ans,UP;

int main(){
	while (scanf("%lld%lld",&N,&M)!=EOF){
		ans=N-1;
		UP=N/2;
		ans+=(0+UP-1)*UP/2;
		UP=(N-1)/2;
		ans+=(0+UP-1)*UP/2;
		if (ans<=M)printf("T\n");
		else printf("F\n");
	}
}
