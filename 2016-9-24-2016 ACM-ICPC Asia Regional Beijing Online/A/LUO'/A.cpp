#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <algorithm>
using namespace std;

const int MaxN = 60;
const int MaxL = 200;

struct NodeType
{
	int l,n;
	string str;
};

int T,n;
NodeType a[MaxN];

bool Check()
{
	if(a[n].str=="0") return false;
	a[n].l = a[n].str.size();
	int i;
	a[n].n=0;
	for(i=0;i<a[n].l;i++)
		if(a[n].str[i]=='/') a[n].str[i] = 17, a[n].n++;
	return true;
}

bool Cmp(const NodeType A,const NodeType B)
{
	int i,a,b; a = b = 0;
	for(i=0;i<A.l && i<B.l; i++)
	{
		if(A.str[i]==17) a++;
		if(B.str[i]==17) b++;
		if(a==A.n && b<B.n) return false;
		if(a<A.n && b==B.n) return true;
		if(A.str[i]<B.str[i]) return true;
		else if(A.str[i]>B.str[i]) return false;
	}
	if(i>=A.l) return true;
	return false;
}

bool Comp(const NodeType A,const NodeType B)
{
	int i;
	if(A.l!=B.l) return false;
	for(i=0;i<A.l; i++)
		if(A.str[i]<B.str[i]) return false;
		else if(A.str[i]>B.str[i]) return false;
	return true;
}

void PrintN(int x)
{
	int i;
	for(i=1;i<=4*x;i++)
		putchar(' ');
	return;
}

void Print(int idx)
{
	int i,j;
	for(i=0,j=0;i<a[idx].l && i<a[idx-1].l;i++)
	{
		if(a[idx-1].str[i]!=a[idx].str[i]) break;
		if(a[idx].str[i]==17) j++;
	}
	i--;
	while(i>=0 && a[idx].str[i]!=17) i--;
	PrintN(j);
	for(i++;i<a[idx].l;i++)
	{
		if(a[idx].str[i]==17)
		{
			j++;
			putchar('\n');
			PrintN(j);
			continue;
		}
		putchar(idx[a].str[i]);
	}
	putchar('\n');
	return;
}

bool Read()
{
	int i = 1; char c;
	bool flg = false;
	while(scanf("%c",&c)!=EOF)
	{
		if(c!='\n')
		{
			flg = true;
			break;
		}
	}
	if(!flg) return false;
	a[n].str[i++] = c;
	while(scanf("%c",&c) && c!='\n')
		a[n].str[i++] = c;
	a[n].l = i-1;
	return true;
}

int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	
	int i,j;
	
	n = 1;
	while(getline(cin,a[n].str))
	{
		printf("Case %d:\n",++T);
		while(Check())
			getline(cin,a[n].str);//scanf("%s",a[++n].str+1);
		n--;
		
		sort(a+1,a+n+1,Cmp);
		
		for(i=j=1;i<=n;i++)
			if(!Comp(a[j],a[i])) a[++j] = a[i];
		n = j;
//		for(i=1;i<=n;i++)
//			printf("%s\n",a[i].str+1);
		for(i=1;i<=n;i++)
			Print(i);
		n = 1;
	}
	
	return 0;
}
