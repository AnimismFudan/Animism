#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MaxN = (int)3e5 + 7;
const int mod = (int)1e9 + 7;

int N, M;
char str[MaxN];
ll ans, sum, f, sumf;

int main()
{
	scanf("%d%d", &N, &M);
	scanf("%s", str+1);
	
	sum = 0; f = sumf = 1;
	for (int i=1; i<=N; i++)
	{
		sum = sum * 10 + (str[i] - '0');
		sum %= M;
		if (sum == 0)
		{
			ans = sumf;
			f = sumf;
			sumf += f;
			sumf %= mod;
		}
		else ans = 0;
	}
	cout << ans << endl;
	
	return 0;
}

