#include <bits/stdc++.h>
using namespace std;

const int MaxM = 1007;

int N, M, P[MaxM], Q[MaxM];

int main()
{
	freopen("C.in", "r", stdin);

	scanf("%d%d", &N, &M);
	for (int i=1; i<=M; i++)
		scanf("%d", P+i);
	sort(P+1, P+M+1);
	int id, l, r;
	if (M & 1)
	{
		l = r = (M+1) >> 1;
		Q[l] = P[1]; id = 2;
	}
	else
	{
		l = M >> 1; r = l+1;
		Q[l] = P[1]; Q[r] = P[2]; id = 3;
	}
	while (id < N)
	{
		int s1 = 0, s2 = 0;
		for (int i=l; i<=r; i++)
		{
			s1 += (r+1 - i) * P[id] * Q[i] + (i - l+1) * P[id+1] * Q[i];
			s2 += (r+1 - i) * P[id+1] * Q[i] + (i - l+1) * P[id] * Q[i];
		}
		r++; l--;
		cout << s1 << ' ' << s2 << endl;
		if (s1 > s2)
		{
			Q[r] = P[id]; Q[l] = P[id+1];
		}
		else
		{
			Q[r] = P[id+1]; Q[l] = P[id];
		}
		id += 2;
	}
	for (int i=1; i<=N; i++)
		cout << Q[i] << endl;
	return 0;
}

