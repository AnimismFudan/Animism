#include <bits/stdc++.h>
using namespace std;
#define LL long long

LL s,t1,t2;
int b[10][10];

int main(){
	memset(b,255,sizeof(b));
	s=1;t2=1;
	for (int i=0;i<=100000;i++){
		t1=s;
		while (t1>9)t1/=10;
		if (b[t1][t2]==-1)
			b[t1][t2]=i;
		s*=2;t2=t2*2%10;
		while (s>1e15)s/=10;
	}
	cin >> t1 >> t2;
	printf("%d",b[t1][t2]);
}