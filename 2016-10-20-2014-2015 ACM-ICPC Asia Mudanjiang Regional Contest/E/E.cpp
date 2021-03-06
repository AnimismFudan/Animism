#include <bits/stdc++.h>
using namespace std;

const int MaxN = 520;

int T,n,mat[MaxN][MaxN];
int x,y,d,delta,l,r,s;
int temp[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};

void Matrix1(int n)
{
	int i;
	x = y = 1; d = 0;
	delta = 1; l = 1; r = n*n; s = 1;
	while (n>1)
	{
		if (delta == 1) s = l;
		else s = r;
		for (i=1; i<=n/2; i++)
		{
			mat[x][y] = s; s += delta;
			x += temp[d][0];
			y += temp[d][1]; d = (d+1) % 4;
			mat[x][y] = s; s += delta;
			x += temp[d][0];
			y += temp[d][1]; d = (d+1) % 4;
			mat[x][y] = s; s += delta;
			x += temp[d][0];
			y += temp[d][1]; d = (d+3) % 4;
			mat[x][y] = s; s += delta;
			x += temp[d][0];
			y += temp[d][1]; d = (d+3) % 4;
		}
		
		mat[x][y] = s; s += delta;
		x += temp[d][0]; y += temp[d][1];
		mat[x][y] = s; s += delta;
		x += temp[d][0]; y += temp[d][1];
		d = (d+3) % 4;
		for (i=1; i+1<=n/2; i++)
		{
			mat[x][y] = s; s += delta;
			x += temp[d][0];
			y += temp[d][1]; d = (d+1) % 4;
			mat[x][y] = s; s += delta;
			x += temp[d][0];
			y += temp[d][1]; d = (d+1) % 4;
			mat[x][y] = s; s += delta;
			x += temp[d][0];
			y += temp[d][1]; d = (d+3) % 4;
			mat[x][y] = s; s += delta;
			x += temp[d][0];
			y += temp[d][1]; d = (d+3) % 4;
		}
		mat[x][y] = s; s += delta;
		x += temp[d][0]; y += temp[d][1];
		mat[x][y] = s; s += delta;
		x += temp[d][0] * (n-2);
		y += temp[d][1] * (n-2);
		if (delta == 1) l = s;
		else r = s;
		d = (d+2) % 4;
		delta = -delta;
		n -= 2;
	}
	mat[x][y] = s;
}

void Matrix2(int n)
{
	int i;
	x = y = 1; d = 0;
	delta = 1; l = 1; r = n*n; s = 1;
	while (n>2)
	{
		if (delta == 1) s = l;
		else s = r;
		for (i=1; i<n/2; i++)
		{
			mat[x][y] = s; s += delta;
			x += temp[d][0];
			y += temp[d][1]; d = (d+1) % 4;
			mat[x][y] = s; s += delta;
			x += temp[d][0];
			y += temp[d][1]; d = (d+1) % 4;
			mat[x][y] = s; s += delta;
			x += temp[d][0];
			y += temp[d][1]; d = (d+3) % 4;
			mat[x][y] = s; s += delta;
			x += temp[d][0];
			y += temp[d][1]; d = (d+3) % 4;
		}
		
		mat[x][y] = s; s += delta;
		d = (d+1) % 4;
		x += temp[d][0]; y += temp[d][1];
		mat[x][y] = s; s += delta;
		d = (d+3) % 4;
		x += temp[d][0]; y += temp[d][1];
		d = (d+3) % 4;
		
		
		for (i=1; i<n/2; i++)
		{
			mat[x][y] = s; s += delta;
			x += temp[d][0];
			y += temp[d][1]; d = (d+1) % 4;
			mat[x][y] = s; s += delta;
			x += temp[d][0];
			y += temp[d][1]; d = (d+1) % 4;
			mat[x][y] = s; s += delta;
			x += temp[d][0];
			y += temp[d][1]; d = (d+3) % 4;
			mat[x][y] = s; s += delta;
			x += temp[d][0];
			y += temp[d][1]; d = (d+3) % 4;
		}
		mat[x][y] = s; s += delta;
		x += temp[d][0]; y += temp[d][1];
		mat[x][y] = s; s += delta;
		x += temp[d][0] * (n-2);
		y += temp[d][1] * (n-2);
		if (delta == 1) l = s;
		else r = s;
		d = (d+2) % 4;
		delta = -delta;
		n -= 2;
	}
	if (delta == 1) s = l;
	else s = r;
	mat[x][y] = s; s += delta;
	d = (d+1) % 4;
	x += temp[d][0]; y += temp[d][1];
	mat[x][y] = s; s += delta;
	d = (d+3) % 4;
	x += temp[d][0]; y += temp[d][1];
	mat[x][y] = s; s += delta;
	d = (d+3) % 4;
	x += temp[d][0]; y += temp[d][1];
	mat[x][y] = s; s += delta;
}

int main()
{
	int i,j;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		if (n&1) Matrix1(n);
		else Matrix2(n);
		for (i=1; i<=n; i++)
		{
			for (j=1; j<=n; j++)
				printf("%d ",mat[i][j]);
			printf("\n");
		}
	}
	return 0;
}