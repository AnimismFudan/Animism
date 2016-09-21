#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll tmp = 100000LL;

int Q;
ll a,b,c;
char str[10];

inline ll Read()
{
	int i,j,l; ll s = 0LL;
	scanf("%s",str); l = strlen(str);
	for(i=0;i<l && str[i]!='.';i++)
		s = s*10LL + (str[i]-'0');
	for(j=1,i++;j<=5 && i<l;i++,j++)
		s = s*10LL + (str[i]-'0');
	while(j<=5) s = s*10LL, j++;
	return s;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	
	scanf("%d",&Q);
	while(Q--)
	{
		a = Read();
		b = Read();
		c = Read();
		//cout<<a<<' '<<b<<' '<<c<<endl;
		if(tmp*(a*b+b*c+c*a)<a*b*c) printf("YES\n");
		else printf("NO\n");
	}
	
	return 0;
}

