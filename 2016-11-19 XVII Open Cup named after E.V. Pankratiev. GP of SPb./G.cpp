#include <bits/stdc++.h>
using namespace std;

map<string,int> mp;
char s[210];
int cnt,k;

int main() {
	for (int i = 1; i <= 10000; i++) {
		printf("+\n");
		fflush(stdout);
		scanf("%s",s + 1);
		mp[s + 1]++;
	}
	for (map<string,int> :: iterator i = mp.begin(); i != mp.end(); i++) {
		if (i -> second == 2) cnt++;
	}
	k = mp.size();
	if (k < 11) printf("= 10\n");
	else if (k < 101) printf("= 100\n");
	else if (k < 1001) printf("= 1000\n");
	else if (cnt > 1000) printf("= 10000\n");
	else if (cnt > 100) printf("= 100000\n");
	else if (cnt > 12) printf("= 1000000\n");
	else printf("= 10000000\n");
	fflush(stdout);
	return 0;
}
