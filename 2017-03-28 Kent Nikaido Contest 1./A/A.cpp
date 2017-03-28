#include <bits/stdc++.h>
using namespace std;

const int MaxN = 100;

int N; char str[MaxN][MaxN];
int s[4];

int main()
{
	scanf("%d", &N);
	for (int i=1; i<=N; i++)
		scanf("%s", str[i] + 1);
	for (int i=1; i<=N; i++)
		for (int j=1; j<=N; j++)
			if (str[i][j] == 'o')
				s[(N-i + j) % 4]++;
	if (s[0] > s[1]) swap(s[0], s[1]);
	if (s[0] > s[2]) swap(s[0], s[2]);
	if (s[0] > s[3]) swap(s[0], s[3]);
	s[1] -= s[0];
	s[2] -= s[0];
	s[3] -= s[0];
	if ((s[1] + s[2] + s[3]) % 8 == 0) printf("0\n");
	else printf("1\n");
	return 0;
}

