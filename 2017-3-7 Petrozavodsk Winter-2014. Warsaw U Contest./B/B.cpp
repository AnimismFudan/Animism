#include <bits/stdc++.h>
using namespace std;

const int MaxN = (int)2e5 + 7;
const int MaxM = (int)5e5 + 7;

struct nodetype
{
	int a, b, w;
};

int N, M, fa[MaxN];
nodetype lin[MaxM];
long long ans;

inline int FindF(int x)
{
	if (fa[x] == 0) return x;
	return fa[x] = FindF(fa[x]);
}

bool Comp(const nodetype A, const nodetype B)
{
	return (A.w > B.w);
}

int main()
{
	//freopen("B.in", "r", stdin);
	
	scanf("%d%d", &N, &M);
	for (int i=1; i<=M; i++)
	{
		scanf("%d%d%d", &lin[i].a, &lin[i].b, &lin[i].w);
		ans += lin[i].w;
	}
	sort(lin+1, lin+M+1, Comp);
	
	for (int i=1; i<=M; i++)
	{
		if (lin[i].w <= 0) break;
		int a = FindF(lin[i].a);
		int b = FindF(lin[i].b);
		if (a != b)
		{
			ans -= lin[i].w;
			fa[a] = b;
		}
	}
	
	cout << ans << endl;
	return 0;
}

