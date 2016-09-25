#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;



int p,pri[(int)1e7];

void GetPrime(int d)
{
	int i;
	for(i=2;i*i<=d;i++)
		if(d%i==0)
		{
			pri[++pri[0]] = i;
			while(d%i==0) d/=i;
		}
	if(d>1) pri[++pri[0]] = d;
	return;
}

int main()
{
	freopen("prime.out","w",stdout);
	
	p = (int)1e9 + 7;
	
	GetPrime(p-1);
	
	if(Check(2)) {printf("2\n"); return 0;}
	
	for(int i=3; i*i<=d; i+=2)
		if(d%i==0)
		{
			
	
	return 0;
}

