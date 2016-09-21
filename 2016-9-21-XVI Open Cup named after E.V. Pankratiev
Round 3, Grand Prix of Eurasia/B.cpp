#include <bits/stdc++.h>
#define intl long long
using namespace std;

char s[3100000];
int n,m,K,top,T;
int mark[2010000],sou[2010000];

map <intl,int> mp;

intl get_hash(char *s, int n) {
	intl ans = 0LL;
	for (int i = 1; i <= n; i++) ans = (ans * 73LL + (intl) (s[i] - 'a' + 1)) % 1000000007LL;
	return ans;
}

int main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d",&K);
	n = 1 << K;
	for (int i = 1; i <= n; i++) {
		scanf("%s",s + 1);
		m = strlen(s + 1);
		intl has = get_hash(s, m);
		mp[has] = ++top;
		sou[n + n - i] = i; mark[i] = n + n - i;
	}

	scanf("%s",s + 1);
	int u = n * 2 - 1; int len = strlen(s + 1);
	for (int i = 1; i <= len; i++) {
		if (s[i] == 'W') sou[u / 2] = sou[u];
		else sou[u / 2] = sou[u - 1];
		mark[sou[u / 2]] = u / 2;
		u -= 2;
	}

	for (scanf("%d",&T); T; T--) {
		scanf("%s",s + 1);
		len = strlen(s + 1);
		int A = mp[get_hash(s, len)];
		scanf("%s",s + 1);
		len = strlen(s + 1);
		int B = mp[get_hash(s, len)];
		A = mark[A]; B = mark[B];
		bool flag = false;
		if (A > B) {
			for (; A && A != B; A /= 2);
			if (A == B) {
				flag = true;
				printf("Lose\n");
			}
		} else {
			for (; B && B != A; B /= 2);
			if (A == B) {
				flag = true;
				printf("Win\n");
			}
		}
		if (!flag) printf("Unknown\n");
	}
	return 0;
}
