#include <bits/stdc++.h>
#define maxn 2010000
using namespace std;

int mark[maxn], MARK[maxn], val[maxn];
int f_[maxn];
int *f = f_ + 1000010;
int n, m, top;
int p[maxn];
int Ans, Anss;

int main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++) {
		scanf("%d",&p[i]);
	}
	for (int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d",&a,&b);
		mark[a]++;
		mark[b + 1]--;
	}
	int pas = -1, cnt = 0;
	for (int i = 0; i <= 1000001; i++) {
		cnt += mark[i];
		if (cnt > 0 && pas == -1) pas = i;
		else if (cnt == 0 && pas != -1) {
			MARK[++top] = pas;
			val[top] = 1;
			MARK[++top] = i;
			val[top] = -1;
			pas = -1;
		}
	}

	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= top; j++) {
			f[MARK[j] - p[i]] += val[j];
		}
	cnt = 0; Anss = -1;
	for (int i = -1000001; i <= 1000001; i++) {
		cnt += f[i];
		if (cnt > Anss || (cnt == Anss && abs(i) < Ans)) {
			Ans = abs(i);
			Anss = cnt;
		}
	}

	printf("%d %d\n",Ans, Anss);
	return 0;
}
