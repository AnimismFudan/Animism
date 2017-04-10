#include <bits/stdc++.h>
using namespace std;

const int MaxN = 200;

int N = 150;
char str[MaxN][MaxN];

int main()
{
	//freopen("G.out", "w", stdout);
	
	memset(str, '.', sizeof(str));
	
	int i, j, k;
	int line = 0, loc;
	for (i=0; i<11; i++)
	{
		line ++;
		str[line][1] = 'O';
		for (j=1; j<=13; j++)
			str[line][13 * i + j + 1] = 'O';
	}
	for (i=0; i<13; i++)
		for (j=0; j<13; j++)
		{
			line ++; loc = 1 + j;
			for (k=0; k<11; k++)
			{
				str[line][k * 13 + 1 + loc] = 'O';
				loc += i;
				//if (i == 12) cout << k << ' ' << k * 13 + 1 + loc << ';';
				if (loc > 13) loc -= 13;
			}
		}
	
	for (i=13; i<=24; i++) str[i][150] = 'O';
	for (i=150; i>=142; i--) str[i][149] = 'O';
	
	int cnt = 0;
	printf("%d\n", N);
	for (i=1; i<=N; i++)
	{
		for (j=1; j<=N; j++)
		{
			printf("%c", str[i][j]);
			if (str[i][j] == 'O') cnt++;
		}
		printf("\n");
	}
	//cout << cnt << endl;
	/*
	for (int p=1; p<=N; p++)
		for (int q=1; q<=N; q++)
			for (int r=p+1; r<=N; r++)
				for (int s=q+1; s<=N; s++)
					if (str[p][q] == 'O' && str[p][s] =='O' && str[r][q] == 'O' && str[r][s] == 'O')
					 	cout << p << ' ' << q << ' ' << r << ' ' << s << endl;
	*/
	return 0;
}

