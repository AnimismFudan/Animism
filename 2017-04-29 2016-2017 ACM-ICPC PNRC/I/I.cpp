#include <bits/stdc++.h>
using namespace std;

const int MaxN = 1007;

struct nodetype
{
	int x, m;
};

int N, K;
nodetype node[MaxN];
long long tim;

bool Comp(const nodetype A, const nodetype B)
{
	return (A.x < B.x);
}

int main()
{
	freopen("I.in", "r", stdin);
	//freopen("I.out", "w", stdout);
	
	scanf("%d%d", &N, &K);
	for (int i=1; i<=N; i++)
		scanf("%d%d", &node[i].x, &node[i].m);
	sort(node+1, node+N+1, Comp);
	
	for (int i=1; i<=N && node[i].x < 0; )
	{
		int j = node[i].m / K;
		node[i].m %= K;
		tim += (long long) j  * (-node[i].x) * 2;
		if (node[i].m == 0)
		{
			i++;
			continue;
		}
		j = K - node[i].m;
		tim += (-node[i].x) * 2;
		while (j > 0)
		{
			i++;
			if (node[i].x >=0) break;
			int t = min(j, node[i].m);
			node[i].m -= t;
			j -= t;
		}
	}
	
	for (int i=N; i>=1 && node[i].x > 0; )
	{
		int j = node[i].m / K;
		node[i].m %= K;
		tim += (long long) j * (node[i].x) * 2;
		if (node[i].m == 0)
		{
			i--;
			continue;
		}
		j = K - node[i].m;
		tim += (long long) (node[i].x) * 2;
		while (j > 0)
		{
			i--;
			if (node[i].x <= 0) break;
			int t = min(j, node[i].m);
			node[i].m -= t;
			j -= t;
		}
	}
			
	cout << tim << endl;
	return 0;
}

