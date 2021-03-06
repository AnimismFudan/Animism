#include <bits/stdc++.h>
using namespace std;

int N, M, len;
bool b[110];
char s[110][110], ans[110];

int main(){
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
		scanf("%s", s[i]);
	for (int i = 1; i <= M; i++){
		int x;
		scanf("%d", &x);
		b[x] = 1;
	}
	len = 0;
	for (int i = 1; i <= N; i++){
		if (!b[i])
			continue;
		if (!len){
			memcpy(ans, s[i], sizeof(ans));
			len = strlen(ans);
			continue;
		}
		int r = strlen(s[i]);
		if (len != r){
			len = -1;
			break;
		}
		for (int j = 0; j < r; j++)
			if (ans[j] != s[i][j])
				ans[j] = '?';
	}
	for (int i = 1; i <= N; i++){
		if (b[i])
			continue;
		int r = strlen(s[i]);
		if (len != r)
			continue;
		bool flag = 1;
		for (int j = 0; j < r; j++)
			if (ans[j] != s[i][j] && ans[j] != '?')
				flag = 0;
		if (flag){
			len = -1;
			break;
		}
	}
	if (len == -1)
		printf("No\n");
	else{
		printf("Yes\n");
		printf("%s\n", ans);
	}
	return 0;
}

