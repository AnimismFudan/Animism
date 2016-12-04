#include <bits/stdc++.h>
#define maxn ((1 << 16) + 10)
#define midl ((L + R) >> 1)
#define midr (midl + 1)
#define lowbit(a) ((a) & (-(a)))
#define uint unsigned int
#define intl long long
using namespace std;

uint n;
uint st[maxn];
uint cnt[10][10];
uint val[10][maxn],p[maxn];
uint A, B, C;
intl Ans = 1LL << 60;
uint Ansa, Ansb, Ansc;

uint cmp(uint a, uint b) {
	return (val[A][a] < val[A][b]);
}

void update(uint A, uint B, uint C, intl ans) {
	//printf("%d %d %d %d\n",A,B,C,ans);
	if (Ans > ans) {
		Ans = ans;
		Ansa = A;
		Ansb = B;
		Ansc = C;
	}
	return;
}

int main() {
	//freopen("I.in","r",stdin);
	//freopen("I.out","w",stdout);
	scanf("%u",&n);
	for (uint i = 1; i <= 9; i++) {
		for (uint j = 1; j <= n; j++) {
			uint a;
			scanf("%d",&a);
			val[i][a] = j;
		}
		for (uint j = 1; j <= n; j++)
			val[i][j] = n - val[i][j] + 1;
	}
	for (A = 1; A <= 9; A++)
		for (B = A + 1; B <= 9; B++) {
			cnt[A][B] = 0;		
			for (uint i = 1; i <= n; i++) p[i] = i;
			sort(p + 1, p + n + 1, cmp);
			memset(st,0,sizeof(st));
			for (uint i = 1; i <= n; i++) {
				for (uint j = val[B][p[i]]; j; j -= lowbit(j))
					cnt[A][B] += st[j];
				for (uint j = val[B][p[i]]; j <= n; j += lowbit(j))
					st[j]++;
			}
		}
	for (A = 1; A <= 9; A++)
		for (B = A + 1; B <= 9; B++)
			for (C = B + 1; C <= 9; C++)
				update(A, B, C, (intl) cnt[A][B] + (intl) cnt[A][C] + (intl) cnt[B][C] - (intl) (n * (n - 1) / 2));
	printf("%u %u %u\n",Ansa, Ansb, Ansc);
	return 0;
}
