#include <bits/stdc++.h>
using namespace std;

const int MaxN = (int)2e5 + 7;

struct nodetype
{
	int id,deg;
};

int N, M, D, deg[MaxN];
vector<int> iv[MaxN];
bool vis[MaxN];
int pr[MaxN], tp[MaxN];

struct cmp {
	bool operator () (nodetype a, nodetype b) {
		return (a.deg < b.deg || (a.deg == b.deg && a.id < b.id));
	}
};
set<nodetype,cmp> iset;

void DFS(int x)
{
	tp[++tp[0]] = x;
	vis[x] = true;
	for (int i=0; i<(int)iv[x].size(); i++)
		if (!vis[iv[x][i]])
		{
			DFS(iv[x][i]);
		}
	return;
}

int main()
{
	//freopen("D.in", "r", stdin);
	
	scanf("%d%d%d", &N, &M, &D);
	for (int i=1; i<=M; i++)
	{
		int a,b;
		scanf("%d%d", &a, &b);
		deg[a]++; deg[b]++;
		iv[a].push_back(b);
		iv[b].push_back(a);
	}
	
	int i; nodetype tmp;
	for (i=1; i<=N; i++)
	{
		tmp.id = i; tmp.deg = deg[i];
		iset.insert(tmp);
	}
	
	while ((!iset.empty()) && (iset.begin()) -> deg < D)
	{
		tmp = *iset.begin();
		i = tmp.id;
		
		//cerr << i << endl;
		
		vis[i] = true;
		iset.erase(tmp);
		for (int j=0; j<(int)iv[i].size(); j++)
			if (!vis[iv[i][j]])
			{
				tmp.id = iv[i][j]; tmp.deg = deg[iv[i][j]];
				deg[iv[i][j]]--;
				iset.erase(tmp);
				tmp.deg--;
				iset.insert(tmp);
			}
	}
	
	for (i=1; i<=N; i++)
		if (!vis[i])
		{
			tp[0] = 0;
			DFS(i);
			if (tp[0] > pr[0])
			{
				for (int j=0; j<=tp[0]; j++)
					pr[j] = tp[j];
			}
		}
	sort(pr+1, pr+1+pr[0]);
	if (pr[0] == 0)
		printf("NIE\n");
	else
	{
		printf("%d\n", pr[0]);
		for (int i=1; i<=pr[0]; i++)
			printf("%d ", pr[i]);
		printf("\n");
	}
	
	return 0;
}

