#include <bits/stdc++.h>
using namespace std;

const int MaxN = 21;
const int MaxM = (1<<20) + 7;

int N, M, p[MaxM];
char str[MaxM];

bool DFS(int l, int r, bool flip, int loc)
{
	//cout << l << ' ' << r << ' ' << flip << endl;
	if ((str[l] == '-') ^ flip) return false;
	if (l == r)
	{
		p[l] = loc + 1;
		//cout << l << ' ' << p[l] << endl;
		return true;
	}
	int x = (l + r) / 2;
	bool nflip = (str[x+1] == '-') ^ flip;
	//cout << x+1 << ' ' << str[x+1] << ' ' << nflip << endl;
	if (nflip == true)
	{
		if (DFS(l, x, flip, loc) == false || DFS(x+1, r, flip ^ nflip, loc + (r-l+1) / 2) == false)
			return false;
	}
	else
	{
		if (DFS(l, x, flip, loc + (r-l+1) / 2) == false || DFS(x+1, r, flip ^ nflip, loc) == false)
			return false;
	}
	return true;
}

int main()
{
	scanf("%d", &N); M = (1 << N);
	scanf("%s", str + 1);
	
	if (DFS(1, M, false, 0))
	{	
		for (int i=1; i<=M; i++)
			printf("%d ", p[i]);
		printf("\n");
	}
	else printf("Impossible\n");
	
	return 0;
}

