#include <bits/stdc++.h>
using namespace std;

int l;
char str[1000];

int Calc(char c)
{
	if(c>='0' && c<='9') return c-'0';
	if(c=='A') return 10;
	if(c=='B') return 11;
	if(c=='C') return 12;
	if(c=='D') return 13;
	if(c=='E') return 14;
	if(c=='F') return 15;
	return -1;
}

int Change(char a,char b)
{
	return Calc(a) * 16 + Calc(b);
}

int main()
{
	freopen("A.in","r",stdin);
	
	int i,j;
	
	while(scanf("%s",str+1)!=EOF)
	{
		l = strlen(str+1);
		for(i=1;i<=l;i+=2)
		{
			j = Change(str[i],str[i+1]);
			printf("%c",j);
		}
		printf("\n");
	}
	
	return 0;
}

