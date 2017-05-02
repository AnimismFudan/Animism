#include <bits/stdc++.h>
using namespace std;

const int MaxN = 1007;

int N, p[MaxN], q[MaxN];

void MergeSort(int l, int r)
{
	if (l == r) return;
	int m = (l+r) >> 1;
	MergeSort(l, m);
	MergeSort(m+1, r);
	int i = l, j = m+1, k = l;
	char str[10];
	while (i <= m && j <= r)
	{
		printf("1 %d %d\n", p[i], p[j]);
		fflush(stdout);
		scanf("%s", str);
		if (str[0] == 'Y')
			q[k++] = p[i++];
		else q[k++] = p[j++];
	}
	while (i<=m) q[k++] = p[i++];
	while (j<=r) q[k++] = p[j++];
	for (i=l; i<=r; i++)
		p[i] = q[i];
}

int main()
{
	scanf("%d", &N);
	for (int i=1; i<=N; i++)
		p[i] = i;
	MergeSort(1, N);
	printf("0");
	for (int i=1; i<=N; i++)
		printf(" %d", p[i]);
	printf("\n");
	fflush(stdout);
	return 0;
}
