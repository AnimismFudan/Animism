#include <bits/stdc++.h>
using namespace std;

int N = 6;

int ans, s, p[20], tp[20];
int d[20] = {0,1,1,2,3,3,4};

void DFS(int x)
{
	if (x > N)
	{
		s = 0;
		for (int i=1; i<=N; i++)
			for (int j=i+1; j<=N; j++)
				s += (j-i) * d[p[i]] * d[p[j]];
		if (s ==2998){
		for (int i=1; i<=N; i++)
			cout << d[p[i]] << ' ';
		cout << s << endl;
		}
		if (s > ans)
		{
			for (int i=1; i<=N; i++)
				tp[i] = p[i];
			ans = s;
		}
		return;
	}
	for (int i=x; i<=N; i++)
	{
		swap(p[i], p[x]);
		DFS(x+1);
		swap(p[i], p[x]);
	}
	return;
}

int main()
{
	for (int i=1; i<=N; i++)
		p[i] = i;
	DFS(1);
	for (int i=1; i<=N; i++)
		cout << d[tp[i]] << ' ';
	cout << ans << endl;
	return 0;
}

