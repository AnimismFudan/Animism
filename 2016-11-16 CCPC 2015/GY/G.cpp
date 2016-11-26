#include <bits/stdc++.h>
using namespace std;

#define LL long long

int Test;
char s[10][10];
bool vis[10][10];
const int fx[4] = {1, -1, 0, 0};
const int fy[4] = {0, 0, 1, -1};
int flag;

bool dfs(int x, int y){
	bool flag = 0;
	if (s[x][y] == '.')
		return 1;
	vis[x][y] = 1;
	for (int k = 0; k < 4; k++){
		int xx = x + fx[k];
		int yy = y + fy[k];
		if (xx < 0 || yy < 0 || xx == 9 || yy == 9)
			continue;
		if (vis[xx][yy] || s[xx][yy] == 'x')
			continue;
		if (dfs(xx, yy))
			flag = 1;
	}
	return flag;
}

bool check(){
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (s[i][j] == 'o' && !vis[i][j]){
				bool tt = dfs(i, j);
				if (!tt)return 1;
			}
	return 0;
}

int main(){
	freopen("G.in", "r", stdin);
	freopen("G.out", "w", stdout);
	scanf("%d", &Test);
	for (int tt = 1; tt <= Test; tt++){
		for (int i = 0; i < 9; i++)
			scanf("%s", s[i]);
		flag = 0;
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				if (s[i][j] == '.'){
					s[i][j] = 'x';
					if (check())
						flag++;
					s[i][j] = '.';
				}
		if (flag)printf("Case #%d: Can kill in one move!!!\n", tt);
		else printf("Case #%d: Can not kill in one move!!!\n", tt);
	}
}