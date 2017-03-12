#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

bool notp[10000001];
int prime[5000000] , tot;
void seive()
{
	for(int i = 2 ; i <= 10000000 ; i++)
	{
		if(!notp[i])prime[++tot] = i;
		for(int j = 1 ; j <= tot ; j++)
		{
			if(i * prime[j] > 10000000)break;
			notp[i * prime[j]] = true;
			if(i % prime[j] == 0)break;
		}
	}
}

vector<long long> pt;

int s[2000001];
void multi(int ind , int v)
{
	while(ind <= 2000000)
	{
		s[ind] = (long long)s[ind] * v % mod;
		ind += ind & (-ind);
	}
}
int getans(int ind)
{
	int ans = 1;
	while(ind >= 1)
	{
		ans = (long long)ans * s[ind] % mod;
		ind -= ind & (-ind);
	}
	return ans;
}

int main()
{
	seive();
	for(int i = 1 ; i <= tot ; i++)
	{
		long long now = 1;double tmp = prime[i];
		while(tmp <= 1e15)
		{
			now = now * prime[i];
			if(now > 100000000000000LL)break;
			pt.push_back(now);
			tmp = tmp * prime[i];
		}
	}
	sort(pt.begin() , pt.end());
	pt.resize(unique(pt.begin() , pt.end()) - pt.begin());
	for(int i = 1 ; i <= 2000000 ; i++)
		s[i] = 1;
	for(int i = 1 ; i <= tot ; i++)
	{
		long long now = 1;double tmp = prime[i];
		int cnt = 0;
		while(tmp <= 1e15)
		{
			now = now * prime[i];
			if(now > 100000000000000LL)break;
			++cnt;
			if(cnt >= 2)
			multi(lower_bound(pt.begin() , pt.end() , now) - pt.begin() + 1
			, prime[i]);
			tmp = tmp * prime[i];
		}
	}
	for(int i = 0 ; i < 10 ; i++)
		cout << pt[i] << " ";
	cout << endl;
	int T;
	scanf("%d" , &T);
	for(int i = 1 ; i <= T ; i++)
	{
		long long N;
		scanf("%lld" , &N);
		printf("Case %d: %d\n" , i , getans(upper_bound(pt.begin() , pt.end() , N) - pt.begin()));
	}
	return 0;
}
