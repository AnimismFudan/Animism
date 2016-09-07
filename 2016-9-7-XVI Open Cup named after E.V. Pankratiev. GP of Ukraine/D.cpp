#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

map<int,int> mp;

int d[101000],done[101000];
int n,k;

int main() {
	//freopen("D.in","r",stdin);
	//freopen("D.out","w",stdout);
	scanf("%d %d",&n,&k);
	for (int i = 0; i <= n; i++) scanf("%d",&d[i]);
	int res = d[n] / k;
	for (int i = 1; i < n; i++) {
		mp[d[i]] = i; mp[d[i] + d[n]] = i;
	}
	mp[0] = n; mp[d[n]] = n;
	d[n] = 0;
	for (int i = 1; i <= n; i++) {
		if (done[i]) continue;
		done[i] = 1;
		int wp = 1;
		for (int v = mp[d[i] + res]; v; v = mp[d[v] + res]) {
			if (done[v]) break;
			done[v] = 1;
			wp++;
		}
		if (wp == k) { printf("1"); return 0; }
	}
	printf("0");
	return 0;
}
