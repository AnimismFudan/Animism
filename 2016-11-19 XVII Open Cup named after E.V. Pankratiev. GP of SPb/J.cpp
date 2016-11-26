#include<bits/stdc++.h>
using namespace std;

char con[10][8][9] = {
						{".XXXXX..","XX..XXX.","XX.XXXX.","XXXX.XX.","XXX..XX.","XXX..XX.",".XXXXX..","........"},
						{"...XX...","..XXX...",".XXXX...","...XX...","...XX...","...XX...",".XXXXXX.","........"},
						{".XXXXX..","XX...XX.",".....XX.","...XXX..",".XXX....","XX......","XXXXXXX.","........"},
						{".XXXXX..","XX...XX.",".....XX.","..XXXX..",".....XX.","XX...XX.",".XXXXX..","........"},
						{"...XXX..","..XXXX..",".XX.XX..","XX..XX..","XXXXXXX.","....XX..","...XXXX.","........"},
						{"XXXXXXX.","XX......","XXXXXX..",".....XX.",".....XX.","XX...XX.",".XXXXX..","........"},
						{".XXXXX..","XX...XX.","XX......","XXXXXX..","XX...XX.","XX...XX.",".XXXXX..","........"},
						{"XXXXXXX.","XX...XX.","X....XX.","....XX..","...XX...","..XX....","..XX....","........"},
						{".XXXXX..","XX...XX.","XX...XX.",".XXXXX..","XX...XX.","XX...XX.",".XXXXX..","........"},
						{".XXXXX..","XX...XX.","XX...XX.",".XXXXXX.",".....XX.","XX...XX.",".XXXXX..","........"}
					};
char mark[12][720];
char s[12][720];

void get_c(int x, int y, char c){
	if (y < 0) y += 720;
	if (y >= 720) y -= 720;
	mark[x][y] = c;
}

void Draw(int t, int sx, int sy){
	if (t < 10){
		for (int i = 0; i < 8; i++)
			for (int j = -3; j <= 4; j++)
				get_c(sx + i, sy + j, con[t][i][j + 3]);
	}
	else{
		int x = t / 10, y = t % 10;
		for (int i = 0; i < 8; i++)
			for (int j = -7; j <= 0; j++)
				get_c(sx + i, sy + j, con[x][i][j + 7]);
		for (int i = 0; i < 8; i++)
			for (int j = 1; j <= 8; j++)
				get_c(sx + i, sy + j, con[y][i][j - 1]);
	}
}

bool same(int x, int y, int xx, int yy){
	if (yy < 0) yy += 720;
	if (yy >= 720) yy -= 720;
	if (s[x][y] != mark[xx][yy])
		return 0;
	return 1;
}

bool same(int t){
	for (int i = 0; i < 12; i++)
		for (int j = -29; j <= 30; j++){
			if (s[i][j + 29] == '-')
				continue;
			if (!same(i, j + 29, i, t + j))
				return 0;
		}
	return 1;
}

void check(){
	for (int i = 0; i < 60; i++)
		for (int j = 0; j < 60; j += 5){
			int t = i * 12 + j / 5;
			if (same(720 - t)){
				printf("%02d:%02d", i, j);
				return;
			}
		}
}

/*void Pri(int i, int j){
	int t = i * 12 + j / 5;
	t = 720 - t;
	for (int i = 0; i < 12; i++){
		for (int j = -29; j <= 30; j++){
			int y = t + j;
			if (y >= 720)
				y -= 720;
			if (y < 0)
				y += 720;
			printf("%c", mark[i][y]);
		}
		printf("\n");
	}
}*/

int main(){
//	freopen("J.in", "r", stdin);
//	freopen("J.out", "w", stdout);
	memset(mark, '.', sizeof(mark));
	for (int i = 0; i < 60; i++){
		int y = 720 - 12 * i;
		get_c(0, y, 'X');
		get_c(1, y, 'X');
		y++;
		get_c(0, y, 'X');
		get_c(1, y, 'X');
	}
	for (int i = 0; i < 60; i += 5){
		int x, y;
		x = 3;
		y = 720 - 12 * i;
		Draw(i, x, y);
	}
/*	for (int i = 0; i < 12; i++){
		for (int j = 0; j < 720; j++)
			printf("%c", mark[i][j]);
		printf("\n");
	}*/
/*	int x, y;
	scanf("%d%d", &x, &y);
	Pri(x, y);*/
	for (int i = 0; i < 12; i++)
		scanf("%s", s[i]);
	check();
	return 0;
}
