#include <bits/stdc++.h>
using namespace std;

int n,mp[5][5],m,x[30],id[30][5];
int vis[30],ans,sum,flg[30];

void Pretreat(int idx)
{
	if(idx>4)
	{
		m++;
		for(int i=1; i<=4; i++)
			id[m][i] = x[i];
		return;
	}
	for(int i=idx; i<=4; i++)
	{
		int t = x[i]; x[i] = x[idx]; x[idx] = t;
		Pretreat(idx+1);
		t = x[i]; x[i] = x[idx]; x[idx] = t;
	}
}

inline int DFS(int idx)
{
	vis[idx] = 1;
	if(vis[x[idx]]) return 0;
	return 1 + DFS(x[idx]);
}

inline int Calc(int n)
{
	int i, s = 0;
	for(i=1;i<=n;i++) vis[i] = 0;
	for(i=1;i<=n;i++)
		if(vis[i]==0) s += DFS(i);
	return s;
}

inline void Print(int idx,int t)
{
	vis[idx] = x[idx];
	flg[x[idx]] = flg[idx];
	if(t==0 && flg[idx]!=idx) printf("%c%c-%c%c\n",'a'-1+(flg[idx]+3)/4,'0'+(flg[idx]-1)%4+1,'a'-1+(idx+3)/4,'0'+(idx-1)%4+1);
	if(vis[x[idx]]) return;
	if(t!=0) printf("%c-%c\n",t+x[idx],t+idx);
	Print(x[idx],t);
}

int main()
{
	freopen("puzzle-swap-plus.in","r",stdin);
	freopen("puzzle-swap-plus.out","w",stdout);
	
	int i,j,k,l,r; char str[10];
	for(i=1;i<=4;i++)
		for(j=1;j<=4;j++)
		{
			scanf("%s",str);
			mp[i][j] = (str[0]-'0') * 10 + (str[1]-'0');			
		}
	
	for(i=1;i<=4;i++) x[i] = i;
	Pretreat(1);
	/*
	cout << m << endl;
	for(i=1;i<=m;i++)
	{
		for(j=1;j<=4;j++)
			printf("%d ",id[i][j]);
		printf("\n");
	}
	*/
	ans = 1<<30;
	
	for(i=1;i<=m;i++)
		for(j=1;j<=m;j++)
		{
			sum = 0;
			for(k=1;k<=4;k++) x[k] = id[i][k];
			sum += Calc(4);
			for(k=1;k<=4;k++) x[k] = id[j][k];
			sum += Calc(4);
			k = 1;
			for(int a=1; a<=4; a++)
				for(int b=1; b<=4; b++)
					x[k++] = mp[id[i][a]][id[j][b]];
			//printf("%d : ",sum);
			//for(k=1;k<=16;k++)
			//	printf("%d ",x[k]);
			//printf("\n");
			sum += Calc(16);
			if(ans > sum) ans = sum, l = i, r = j;
		}
	
	printf("%d\n",ans);
	
	for(i=1;i<=4;i++) x[i] = id[l][i], vis[i] = flg[i] = 0;
	for(i=1;i<=4;i++)
		if(vis[i]==0) flg[i] = i , Print(i,96);
	
	for(i=1;i<=4;i++) x[i] = id[r][i], vis[i] = flg[i] = 0;
	for(i=1;i<=4;i++)
		if(vis[i]==0) flg[i] = i,Print(i,48);
	
	i = 0;
	
	for(int a=1;a<=4;a++)
		for(int b=1;b<=4;b++)
			x[++i] = mp[id[l][a]][id[r][b]], vis[i] = flg[i] = 0; 

	for(i=1;i<=16;i++)
		if(vis[i]==0) flg[i] = i,Print(i,0);
	
	return 0;
}

