#include <bits/stdc++.h>
using namespace std;

const int MaxN = (int)1e5 + 7;
const int MaxM = 20;

int N, Q;
int fa[MaxN], dep[MaxN], ff[MaxN][MaxM];
double up[MaxN], down[MaxN], sum[MaxN];
double sumup[MaxN][MaxM], sumdown[MaxN][MaxM];
vector<int> iv[MaxN];

void DFS(int x, int f)
{
	fa[x] = f;
	dep[x] = dep[f] + 1;
	for (int i=0; i<iv[x].size(); i++)
		if (iv[x][i] != f)
			DFS(iv[x][i], x);
}

void GetUp(int x, int f)
{
	up[x] = sum[x] = 0.0;
	for (int i=0; i<iv[x].size(); i++)
	{
		up[x] += 1.0;
		if (iv[x][i] != f)
		{
			GetUp(iv[x][i], x);
			up[x] += up[iv[x][i]];
			sum[x] += up[iv[x][i]];
		}
	}
}

void GetDown(int x, int f)
{
	for (int i=0; i<iv[x].size(); i++)
		if (iv[x][i] != f)
		{
			int j = iv[x][i];
			down[j] = up[x] - up[j] + down[x];
			GetDown(iv[x][i], x);
		}
}

void GetSum()
{
	for (int i=1; i<=N; i++)
	{
		ff[i][0] = fa[i];
		sumup[i][0] = up[i];
		sumdown[i][0] = down[i];
	}
	for (int j=1; (1<<j) <= N; j++)
		for (int i=1; i<=N; i++)
		{
			ff[i][j] = ff[ff[i][j-1]][j-1];
			sumup[i][j] = sumup[i][j-1] + sumup[ff[i][j-1]][j-1];
			sumdown[i][j] = sumdown[i][j-1] + sumdown[ff[i][j-1]][j-1];
		}
}

inline int LCA(int a, int b)
{
	if (dep[a] < dep[b]) swap(a, b);
	int j = (int) (log(dep[a] - dep[b] + 1) / log(2.0)) + 1;
	while (j >= 0)
	{
		if (dep[ff[a][j]] >= dep[b]) a = ff[a][j];
		j--;
	}
	//cerr << a << ' ' << b << endl;
	if (a == b) return a;
	j = (int) (log(dep[a]) / log(2.0)) + 1;
	while (j >= 0)
	{
		if (ff[a][j] != ff[b][j]) a = ff[a][j], b = ff[b][j];
		j--;
	}
	a = ff[a][0];
	return a;
}

double CalcUp(int a, int b)
{
	if (a == b) return 0.0;
	int j = (int) (log(dep[a] - dep[b] + 1) / log(2.0)) + 1;
	double sum = 0.0;
	while (j >= 0)
	{
		if (dep[ff[a][j]] >= dep[b])
		{
			sum += sumup[a][j];
			a = ff[a][j];
		}
		j--;
	}
	return sum;
}

double CalcDown(int a, int b)
{
	if (a == b) return 0.0;
	int j = (int) (log(dep[a] - dep[b] + 1) / log(2.0)) + 1;
	double sum = 0.0;
	while (j >= 0)
	{
		if (dep[ff[a][j]] >= dep[b])
		{
			sum += sumdown[a][j];
			a = ff[a][j];
		}
		j--;
	}
	return sum;
}	

	
int main()
{
	//freopen("G.in", "r", stdin);
	
	scanf("%d", &N);
	for (int i=1; i<N; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		iv[a].push_back(b);
		iv[b].push_back(a);
	}
	DFS(1, 0);
	
	GetUp(1, 0);
	GetDown(1, 0);

	//for (int i=1; i<=N; i++)
	//	cerr << i << ' ' << fa[i] << ' ' << up[i] << ' ' << down[i] << endl;

	GetSum();
	
	scanf("%d", &Q);
	for (int i=1; i<=Q; i++)
	{
		int a, b, f;
		scanf("%d%d", &a, &b);
		f = LCA(a, b);
		//cerr << a << ' ' << b << ' ' << f << endl;
		printf("%.10lf\n", CalcUp(a, f) + CalcDown(b, f));
	}
	
	return 0;
}

