#include <bits/stdc++.h>
using namespace std;

#define LL long long

int Test, N, len, ans;
int a[100];

void dfs(int step){
	if (step > N){
		bool flag = 1;
		for (int j = 3; j <= len; j++)
			if (a[j - 2] + a[j - 1] > a[j])
				flag = 0;
		if (flag)
			ans = min(ans, N - len);
		return;
	}
	a[++len] = step;
	dfs(step + 1);
	a[len--] = 0;
	dfs(step + 1);
}

int main() {
    freopen("D.in","r",stdin);
    freopen("D.out","w",stdout);
    scanf("%d", &Test);
    for (int tt = 1; tt <= Test; tt++){
    	scanf("%d", &N);
    	len = 0;
    	ans = N;
    	dfs(1);
    	printf("Case #%d: %d\n", tt, ans);
    }
    return 0;
}
