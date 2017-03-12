#include <bits/stdc++.h>
using namespace std;

const int MaxN = (int)1e6 + 7;

int N, K, a[MaxN], b[MaxN];
bool inq[MaxN];
priority_queue<int, vector<int>, greater<int> > mq;

int main()
{
	int i, j;
	scanf("%d%d", &N, &K);
	for (i=1; i<=N; i++)
		scanf("%d", a+i);
	for (i=N; i>=1; i--)
	{
		mq.push(a[i]); inq[a[i]] = true;
		if (i+K <= N) inq[a[i+K]] = false;
		j = mq.top();
		//cout << i << ' ' << a[i] << ' ' << j << endl;
		while (!inq[j])
		{
			mq.pop();
			j = mq.top();
		}
		b[i] = j;
	}
	for (i=1; i+K-1<N; i++)
		if (a[i] != b[i]) break;
	sort(a+i, a+i+K);
	for (i=1; i<=N; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}

