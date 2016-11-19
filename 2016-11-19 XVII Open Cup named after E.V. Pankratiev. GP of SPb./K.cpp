#include<bits/stdc++.h>
using namespace std;

int N, len;
int q[110];
int a[10];

bool isprime(int x){
	for (int i = 2; i * i <= x; i++)
		if (x % i == 0)
			return 0;
	return 1;
}

bool check(int x){
	int r = 0;
	while (x){
		a[++r] = x % 10;
		x = x / 10;
	}
	bool flag = 1;
	for (int ll = 1, rr = r; ll < rr; ll++, rr--)
		swap(a[ll], a[rr]);	
	for (int ll = 1; ll <= r && flag; ll++){
		int s = 0;
		for (int rr = ll; rr <= r && flag; rr++){
			s = s * 10 + a[rr];
			if (!isprime(s))
				flag = 0;
		}
	}
	return flag;
}

void dfs(int step, int s){
	if (s && check(s))
		q[++len] = s;
	if (step > 3)
		return;
	if (step == 0){
		dfs(step + 1, 2);
		dfs(step + 1, 3);
		dfs(step + 1, 5);
		dfs(step + 1, 7);
	}else{
		dfs(step + 1, s * 10 + 3);
		dfs(step + 1, s * 10 + 7);
	}
}

int main(){
	dfs(0, 0);
	sort(q + 1, q + len + 1);
	scanf("%d", &N);
	if (N <= len)
		printf("%d\n", q[N]);
	else printf("-1\n");
	return 0;
}
