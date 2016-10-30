#include <bits/stdc++.h>
using namespace std;

const int MaxN = 407;

int T,N,n,m,f[MaxN][4][4][4][4];
int u[MaxN][5],ans;

void Init()
{
	int i,j; char c;
	n = 100; m = 4;
	for (i=1; i<=n; i++)
		for (j=1; j<=m; j++) u[i][j] = 0;
	scanf("%d", &N);
	for (i=1; i<=N; i++)
	{
		scanf("%d%c", &j, &c);
		//printf("%d %c\n",j,c);
		if(c=='y') u[j][1] = 1;
		else if(c=='r') u[j][2] = 1;
		else if(c=='g') u[j][3] = 1;
		else u[j][4] = 1;
	}
}

void Solve()
{
	int i,j,a,b,c,d,t,na,nb,nc,nd,dlt;
	memset(f,0,sizeof(f));
	f[0][0][0][0][0] = 1; ans = 0;
	for (i=0; i<n; i++)
		for (a=0; a<4; a++)
			for (b=0; b<4; b++)
				for (c=0; c<4; c++)
					for (d=0; d<4; d++)
						if(f[i][a][b][c][d])
						{
							j = i+1;
							if(u[j][1] && u[j][2] && u[j][3] && u[j][4])
							{
								f[j][0][0][0][0] = max(f[j][0][0][0][0], f[i][a][b][c][d] + 4*j);
								
								t = min(a+1, 3); dlt = 3*j;
								if (a==2) dlt += j-1 + j-2;
								if (t==3) dlt += j;
								f[j][t][0][0][0] = max(f[j][t][0][0][0], f[i][a][b][c][d] + dlt);
								
								t = min(b+1, 3); dlt = 3*j;
								if (b==2) dlt += j-1 + j-2;
								if (t==3) dlt += j;
								f[j][0][t][0][0] = max(f[j][0][t][0][0], f[i][a][b][c][d] + dlt);
								
								t = min(c+1, 3); dlt = 3*j;
								if (c==2) dlt += j-1 + j-2;
								if (t==3) dlt += j;
								f[j][0][0][t][0] = max(f[j][0][0][t][0], f[i][a][b][c][d] + dlt);
								
								t = min(d+1, 3); dlt = 3*j;
								if (d==2) dlt += j-1 + j-2;
								if (t==3) dlt += j;
								f[j][0][0][0][t] = max(f[j][0][0][0][t], f[i][a][b][c][d] + dlt);
							}
							
							if(u[j][1] + u[j][2] + u[j][3] + u[j][4] == 3)
								f[j][0][0][0][0] = max(f[j][0][0][0][0], f[i][a][b][c][d] + 3*j);
							
							dlt = 0;
							if(u[j][1])
							{
								na = min(a+1, 3);
								if(a==2) dlt += j-1 + j-2;
								if(na==3) dlt += j;
							}
							else na = 0;
							if(u[j][2])
							{
								nb = min(b+1, 3);
								if(b==2) dlt += j-1 + j-2;
								if(nb==3) dlt += j; 
							}
							else nb = 0;
							if(u[j][3])
							{
								nc = min(c+1, 3);
								if(c==2) dlt += j-1 + j-2;
								if(nc==3) dlt += j;
							}
							else nc = 0;
							if(u[j][4])
							{
								nd = min(d+1, 3);
								if(d==2) dlt += j-1 + j-2;
								if(nd==3) dlt += j;
							}
							else nd = 0;
							f[j][na][nb][nc][nd] = max(f[j][na][nb][nc][nd], f[i][a][b][c][d] + dlt);
						}
	for (a=0; a<4; a++)
		for (b=0; b<4; b++)
			for (c=0; c<4; c++)
				for (d=0; d<4; d++)
					ans = max(ans, f[n][a][b][c][d]);
	printf("%d\n",ans-1);
}

int main()
{
	freopen("H.in", "r", stdin);
	
	scanf("%d",&T);
	while(T--)
	{
		Init();
		Solve();
	}
	
	return 0;
}

