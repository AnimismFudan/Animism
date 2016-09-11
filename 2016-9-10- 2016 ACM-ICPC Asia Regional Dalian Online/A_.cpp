#include <bits/stdc++.h>
using namespace std;

int maxn=25;
int N,ans1,ans2,len;
int q[100000010];
int ans[110];

bool check(int t){
	int t1,t2;
	for (int i=1;i<N;i++){
		t1=(t>>(i-1))&1;
		t2=(t>>i)&1;
		if (t1&&t2)return 0;
	}
	t1=(t>>(N-1))&1;
	t2=t&1;
	if (t1&&t2&&N>1)return 0;
	return 1;
}

int calc(int t){
	int res=t;
	for (int i=0;i<N;i++){
		int t1=t&1;
		t=(t>>1)^(t1<<(N-1));
		res=min(res,t);
	}
	return res;
}

bool check2(int t){
	for (int i=1;i<=len;i++)
		if (q[i]==t)return 0;
	return 1;
}

int main(){
	
	freopen("A_.out","w",stdout);
	for (N=1;N<=maxn;N++){
		ans1=ans2=0;
		memset(ans,0,sizeof(ans));
		len=0;
		for (int i=0;i<1<<N;i++)
			if (check(i)){
				ans1++;
				int t=calc(i);
				if (check2(t)){
					int step=0;
					for (int j=0;j<N;j++)
						step+=(t>>j)&1;
					ans[step]++;
					ans2++;
					q[++len]=t;
				}
			}
//			for (int i=0;i<N/2+2;i++)
//				printf("% 5d",ans[i]);
			printf("% 8d",ans2);
			printf("\n");
	}
	
	return 0;
}

