#include <bits/stdc++.h>
using namespace std;

const int MaxN = (int)1e5 + 7;

int N, K, R, cnt;
bool flg[MaxN];

int main()
{
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
	
	scanf("%d%d%d", &N, &K, &R);
	for (int i=1; i<=K; i++)
	{
		int a; scanf("%d", &a);
		flg[a] = true;
	}
	
	int s = 0;
	for (int i=1; i<=R; i++)
		if (flg[i]) s++;
	if (s == 0) cnt = 2, s = 2, flg[R] = flg[R-1] = true;
	else if (s == 1)
	{
		cnt = 1; s = 2;
		if (flg[R]) flg[R-1] = true;
		else flg[R] = true;
	}
	for (int i=R+1; i<=N; i++)
	{
		if (flg[i-R]) s--;
		if (flg[i]) s++;
		if (s < 2) flg[i] = true, cnt++, s++;
	}
	printf("%d\n", cnt);
	
	return 0;
}

