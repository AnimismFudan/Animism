#include <bits/stdc++.h>
using namespace std;

const int MaxN = 107;
const int MaxM = 10;

int T,la,lb,sa[MaxM],sb[MaxM];
char a[MaxN],b[MaxN];

inline bool Check()
{
	int i;
	for(i=0; i<10; i++)
		if(sa[i]==0 && sb[i]>0) return false;
		else if(sa[i]>0 && sb[i]==0) return false;
	return true;
}

int main()
{
	int i; bool flg;
	freopen("D.in", "r", stdin);
	scanf("%d", &T);
	while(T--)
	{
		scanf("%s%s",a+1,b+1);
		la = strlen(a+1);
		lb = strlen(b+1);
		memset(sa,0,sizeof(sa));
		memset(sb,0,sizeof(sb));
		for(i=1; i<=la; i++)
			sa[a[i]-'0']++;
		for(i=1; i<=lb; i++)
			sb[b[i]-'0']++;
		if(Check()) {printf("friends\n"); continue;}
		flg = false;
		for(i=1; i<la; i++)
		{
			if(a[i]>'0' && a[i+1]<'9')
			{
				if(!(i==1 && a[i]=='1'))
				{
					sa[a[i]-'0']--, sa[a[i+1]-'0']--;
					sa[a[i]-'0'-1]++, sa[a[i+1]-'0'+1]++;
					if(Check()) {flg = true; break;}
					sa[a[i]-'0']++, sa[a[i+1]-'0']++;
					sa[a[i]-'0'-1]--, sa[a[i+1]-'0'+1]--;
				}
			}
			if(a[i]<'9' && a[i+1]>'0')
			{
				sa[a[i]-'0']--, sa[a[i+1]-'0']--;
				sa[a[i]-'0'+1]++, sa[a[i+1]-'0'-1]++;
				if(Check()) {flg = true; break;}
				sa[a[i]-'0']++, sa[a[i+1]-'0']++;
				sa[a[i]-'0'+1]--, sa[a[i+1]-'0'-1]--;
			}
		}
		if(flg) {printf("almost friends\n"); continue;}
		for(i=1; i<lb; i++)
		{
			if(b[i]>'0' && b[i+1]<'9')
			{
				if(!(i==1 && b[i]=='1'))
				{
					sb[b[i]-'0']--, sb[b[i+1]-'0']--;
					sb[b[i]-'0'-1]++, sb[b[i+1]-'0'+1]++;
					if(Check()) {flg = true; break;}
					sb[b[i]-'0']++, sb[b[i+1]-'0']++;
					sb[b[i]-'0'-1]--, sb[b[i+1]-'0'+1]--;
				}
			}
			if(b[i]<'9' && b[i+1]>'0')
			{
				sb[b[i]-'0']--, sb[b[i+1]-'0']--;
				sb[b[i]-'0'+1]++, sb[b[i+1]-'0'-1]++;
				if(Check()) {flg = true; break;}
				sb[b[i]-'0']++, sb[b[i+1]-'0']++;
				sb[b[i]-'0'+1]--, sb[b[i+1]-'0'-1]--;
			}
		}
		if(flg) printf("almost friends\n");
		else printf("nothing\n");
	}
	return 0;
}
