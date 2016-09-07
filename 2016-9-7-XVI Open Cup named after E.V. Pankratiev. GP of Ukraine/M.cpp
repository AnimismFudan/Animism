#include <bits/stdc++.h>
using namespace std;
#define LL long long

int K,N;
LL ans;

class rec{
	public:
	int n,a[8];
	LL s;
	bool operator <(const rec &X)const{
		if (s!=X.s)
			return s<X.s;
		if (n!=X.n)
			return n<X.n;
		for (int j=0;j<=7;j++)
			if (a[j]!=X.a[j])return a[j]<X.a[j];
		return 0;
	}
	bool operator >(const rec &X)const{
		if (s!=X.s)
			return s>X.s;
		if (n!=X.n)
			return n>X.n;
		for (int j=0;j<=7;j++)
			if (a[j]!=X.a[j])return a[j]>X.a[j];
		return 0;
	}
}p;
priority_queue <rec ,vector <rec > ,greater <rec> > q;

int main(){
	scanf("%d",&K);
	for (int i=1;i<=K;i++){
		p.n=1;
		p.s=0;
		for (int j=7;j>=0;j--){
			scanf("%d",&p.a[j]);
			p.s=p.s+p.a[j];
		}
		q.push(p);
	}
	scanf("%d",&N);
	while (N--){
		p=q.top();
		q.pop();
		ans=p.s;
		p.n++;
		LL t=1;
		p.s=0;
		for (int j=0;j<=7;j++){
			p.s+=t*p.a[j];
			t=t*p.n;
		}
		q.push(p);
	}
	cout << ans << endl;
}