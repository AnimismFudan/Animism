#include <bits/stdc++.h>
using namespace std;

const int MaxN = (int)3e5 + 7;

struct nodetype
{
	int a, b, w, c;
};

int N, M, Q, deg[MaxN], cnt[MaxN], tmp;
int fa[MaxN], c0[MaxN], c1[MaxN], c2[MaxN], c3[MaxN];
nodetype edg[MaxN];
nodetype ask[MaxN];

bool Comp(const nodetype A, const nodetype B)
{
	return (A.w > B.w);
}

bool Comp1(const nodetype A, const nodetype B)
{
	return (A.a > B.a);
}

bool Comp2(const nodetype A, const nodetype B)
{
	return (A.b < B.b);
}

inline int FindF(int x)
{
	if (fa[x] == 0) return x;
	return fa[x] = FindF(fa[x]);
}

void Update(int x, int fx)
{
	//cout << "update: " << x << ' ' << deg[x] << endl;
	if (c0[fx] == 0 && c1[fx] == 0 && c3[fx] == 0) tmp--;
	if (deg[x] == 1) c0[fx]--, c1[fx]++;
	else if (deg[x] == 2) c1[fx]--, c2[fx]++;
	else if (deg[x] == 3) c2[fx]--, c3[fx]++;
	if (c1[fx] == 0 && c3[fx] == 0) tmp++;
}

int main()
{
//	freopen("E.in", "r", stdin);
//	freopen("E.out", "w", stdout);
	
	scanf("%d%d", &N, &M);
	for (int i=1; i<=M; i++)
		scanf("%d%d%d", &edg[i].a, &edg[i].b, &edg[i].w);
	cnt[0] = N;
	
	sort(edg+1, edg+1+M, Comp);
	
	scanf("%d", &Q);
	for (int i=1; i<=Q; i++)
	{
		scanf("%d", &ask[i].a);
		ask[i].b = i;
	}
	
	for (int i=1; i<=N; i++)
		fa[i] = 0, c0[i] = 1;
	
	sort(ask+1, ask+1+Q, Comp1);
	
	for (int i=1, j=1; i<=Q; i++)
	{
		//cout << ask[i].a << endl;
		while (j<=M && edg[j].w >= ask[i].a)
		{
			//cout << edg[j].a << ' ' << edg[j].b << ' ' << edg[j].w << endl;
			int x, y, fx, fy;
			x = edg[j].a; y = edg[j].b; fx = FindF(x); fy = FindF(y);
			cnt[deg[x]]--; cnt[deg[y]]--;
			deg[x]++; deg[y]++;
			cnt[deg[x]]++; cnt[deg[y]]++;
			Update(x, fx); Update(y, fy);
			if (fx != fy)
			{
				fa[fy] = fx;
				c1[fx] += c1[fy];
				c2[fx] += c2[fy];
				c3[fx] += c3[fy];
			}
			j++;
		}
		//cout << cnt[0] << ' ' << cnt[2] << ' ' << tmp << endl;
		ask[i].w = N - cnt[0] - cnt[2] + tmp;
		ask[i].c = j - 1 - cnt[2] + tmp;
		//cout << ask[i].w << ' '<< ask[i].c << endl << endl;
	}
	
	sort(ask+1, ask+1+Q, Comp2);
	
	for (int i=1; i<=Q; i++)
		printf("%d %d\n", ask[i].w, ask[i].c);
	
	return 0;
}

