#include <bits/stdc++.h>
using namespace std;

int n , d;
int p[2000] , r[2000];
int add[2000] , cost[2000];
priority_queue<int> heap;
int main()
{
	return 0;
	int T;
	scanf("%d" , &T);
	for(int t = 1 ; t <= T ; t++)
	{
		scanf("%d%d" , &n , &d);
		for(int i = 0 ; i <= n + 1 ; i++)
			scanf("%d" , &p[i]);
		for(int i = 0 ; i <= n ; i++)
			scanf("%d" , &r[i]);
		r[0] = p[1] - p[0];
		long long sum = 0;
		for(int i = 0 ; i <= n ; i++)
		{
			int pullcost , swimcost;
			if(r[i] >= d)
				pullcost = r[i] - d;
			else
				pullcost = 0;
			swimcost = r[i] - (p[i + 1] - p[i]);
			printf("swim %d, pull %d\n" , swimcost , pullcost);
			add[i] = pullcost - swimcost;
			cost[i] = pullcost;
		}
		while(!heap.empty())heap.pop();
		long long hp = 0;
		for(int i = 0 ; i <= n ; i++)
			hp += r[i] - (p[i + 1] - p[i]);
		int ans = 0;
		for(int i = 0 ; i <= n ; i++)
		{
			hp -= cost[i];
			heap.push(add[i]);
			while(hp < 0)
			{
				int maxadd = heap.top();
				heap.pop();
				hp += maxadd;
				ans++;
			}
		}
		printf("Case %d: %d\n" , t , ans);
	}
	return 0;
}
