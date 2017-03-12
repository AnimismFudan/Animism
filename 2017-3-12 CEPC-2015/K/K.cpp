#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N;
int du[200010], go[200010], vis[200010];

void dfs(int x){
	if (vis[x] == 1){
		if (vis[go[x]] == 2) return;
		vis[go[x]] = 2;
		dfs(go[x]);
	}else{
		du[go[x]]--;
		if (!du[go[x]]){
			vis[go[x]] = 1;
			dfs(go[x]);
		}
	}
}

register char *_sp __asm__("rsp");

int main(){
	const int size = 64 * 1024 * 1024;
	static char *sys, *mine(new char[size] + size - 4096);
	sys = _sp;
	_sp = mine;
	
//	freopen("K.in", "r", stdin);
//	freopen("K.out", "w", stdout);
	scanf("%d", &N);
	for (int i = 1; i <= N * 2; i++){
		scanf("%d", &go[i]);
		du[go[i]]++;
	}
	for (int i = 1; i <= N * 2; i++)
		if (!du[i]){
			vis[i] = 1;
			dfs(i);
		}
	for (int i = 1; i <= N; i++)
		if (!vis[i])
			vis[i] = 1;
	for (int i = 1; i <= N * 2; i++)
		if (vis[i] == 1)
			printf("%d ", i);
	
	_sp = sys;
	return 0;
}

