#include <bits/stdc++.h>
using namespace std;

#define ll long long

int n,m;
ll score[5];
int color[16][16] = {{},
{0,6,1,1,3,1,1,1,6,1,1,1,3,1,1,6},
{0,1,5,1,1,1,4,1,1,1,4,1,1,1,5,1},
{0,1,1,5,1,1,1,3,1,3,1,1,1,5,1,1},
{0,3,1,1,5,1,1,1,3,1,1,1,5,1,1,3},
{0,1,1,1,1,5,1,1,1,1,1,5,1,1,1,1},
{0,1,4,1,1,1,1,1,1,1,1,1,1,1,4,1},
{0,1,1,3,1,1,1,3,1,3,1,1,1,3,1,1},
{0,6,1,1,3,1,1,1,2,1,1,1,3,1,1,6},
{0,1,1,3,1,1,1,3,1,3,1,1,1,3,1,1},
{0,1,4,1,1,1,1,1,1,1,1,1,1,1,4,1},
{0,1,1,1,1,5,1,1,1,1,1,5,1,1,1,1},
{0,3,1,1,5,1,1,1,3,1,1,1,5,1,1,3},
{0,1,1,5,1,1,1,3,1,3,1,1,1,5,1,1},
{0,1,5,1,1,1,4,1,1,1,4,1,1,1,5,1},
{0,6,1,1,3,1,1,1,6,1,1,1,3,1,1,6}};
int clc[7] = {0,1,1,2,3,1,1}, cwc[7] = {0,1,1,1,1,2,3};
int bv[33] = {0,1,3,2,3,2,1,5,5,1,2,2,2,2,1,1,2,2,2,2,3,10,5,10,5,10,10,10,5,5,10,10,3};
int mp[16][16];
int t[2][2] = {{1,0},{0,1}};

void Updata(int idx)
{
	int T,n,x,y,let[20]; char str[20];
	int i,j;
	ll lp,wp,cnt,sum;
	
	scanf("%d",&T);
	cnt = sum = 0;
	while(T--)
	{
		scanf("%d%s%d%d",&n,str+1,&x,&y);
		for(i=1;i<=n;i++) scanf("%d",let+i);
		if(str[1]=='h') j = 0;
		else j = 1;
		
		lp = 0; wp = 1;
		for(i=1;i<=n;i++)
		{
			if(mp[x][y]==0)
			{
				mp[x][y] = let[i]; cnt++;
			}
			lp += bv[let[i]] * clc[color[x][y]];
			wp *= cwc[color[x][y]];
			x += t[j][0]; y += t[j][1];
		}
		sum += lp * wp;
	}
	if(cnt==7) sum += 15;
	//printf("%d %d\n",idx,sum);
	score[idx] += sum;
	return;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	
	int i,j;
	scanf("%d%d",&n,&m);
	for(i=j=1;i<=m;i++)
	{
		Updata(j);
		j = j%n+1;
	}
	for(i=1;i<=n;i++)
		printf("%lld\n",score[i]);
	
	return 0;
}

