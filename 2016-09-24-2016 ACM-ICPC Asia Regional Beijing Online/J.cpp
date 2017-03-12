#include <bits/stdc++.h>
using namespace std;

const int fx[4] = {0, 0, 1, -1};
const int fy[4] = {1, -1, 0, 0};

int N, M, C, E;
char s[110];
bool vis[110][110], cant_use[110][110];
int dist[110][110], occu[110][110], G[110][110];
int qx[1000010], qy[1000010];

class rec{
	public:
	int hp, at, mv, al, ar, x, y, g;
}P[110];

bool spfa(int c, int tx, int ty){
	int l, r;
	l = r = 0;
	qx[l] = P[c].x;
	qy[l] = P[c].y;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++){
			dist[i][j] = 1e9;
			vis[i][j] = 0;
			cant_use[i][j] = 0;
		}
	dist[P[c].x][P[c].y] = 0;
	vis[P[c].x][P[c].y] = 1;
	int x, y, xx, yy;
	for (;l <= r; l++){
		x = qx[l];
		y = qy[l];
		vis[x][y] = 0;
		if (x != P[c].x || y != P[c].y){
			for (int i = 0; i < 4; i++){
				xx = x + fx[i];
				yy = y + fy[i];
				if (xx <= 0 || xx > N || yy <= 0 || yy > M)
					continue;
				if (occu[xx][yy] != -1 && occu[xx][yy] != P[c].g){
					dist[x][y] = P[c].mv;
					cant_use[x][y] = 1;
				}
			}
		}
		for (int i = 0; i < 4; i++){
			xx = x + fx[i];
			yy = y + fy[i];
			if (xx <= 0 || xx > N || yy <= 0 || yy > M || occu[xx][yy] != -1 || cant_use[xx][yy])
				continue;
			if (dist[xx][yy] > dist[x][y] + G[xx][yy]){
				dist[xx][yy] = dist[x][y] + G[xx][yy];
				if (dist[xx][yy] <= P[c].mv && dist[xx][yy] < dist[tx][ty] && !vis[xx][yy]){
					vis[xx][yy] = 1;
					++r;
					qx[r] = xx;
					qy[r] = yy;
				}
			}
		}
	}
	return (dist[tx][ty] <= P[c].mv);
}

int main() {
    freopen("J.in","r",stdin);
    freopen("J.out","w",stdout);
	while (scanf("%d%d%d%d", &N, &M, &C, &E) != EOF){
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= M; j++)
				scanf("%d", &G[i][j]);
		memset(occu, 255, sizeof(occu));
		for (int i = 1; i <= C; i++){
			scanf("%d%d%d%d", &P[i].hp, &P[i].at, &P[i].mv, &P[i].al);
			scanf("%d%d%d%d", &P[i].ar, &P[i].x, &P[i].y, &P[i].g);
			occu[P[i].x][P[i].y] = P[i].g;
		}
		int turn = 0, c = 0;
		for (int i = 1; i <= E; i++){
			scanf("%s", s);
			if (s[0] == 'R'){
				scanf("%s", s);
				scanf("%d", &turn);
				continue;
			}
			if (s[0] == 'A' && s[1] == 'c'){
				scanf("%s%s", s, s);
				scanf("%d", &c);
				continue;
			}
			if (s[0] == 'M'){
				scanf("%s%s", s, s);
				int x = 0, y = 0;
				int t = 0;
				while (s[t] < '0' || s[t] > '9')t++;
				while (s[t] >= '0' && s[t] <= '9'){
					x = x * 10 + s[t] - '0';
					t++;
				}
				while (s[t] < '0' || s[t] > '9')t++;
				while (s[t] >= '0' && s[t] <= '9'){
					y = y * 10 + s[t] - '0';
					t++;
				}
				bool flag = spfa(c, x, y);
				if (!flag || P[c].hp <= 0)printf("INVALID\n");
				else{
					printf("%d\n", P[c].mv - dist[x][y]);
					occu[P[c].x][P[c].y] = -1;
					occu[x][y] = P[c].g;
					P[c].x = x;
					P[c].y = y;
				}
				continue;
			}
			if (s[0] == 'A' && s[1] == 't'){
				int tar;
				scanf("%d", &tar);
				int dis = abs(P[c].x - P[tar].x) + abs(P[c].y - P[tar].y);
				if (P[c].hp >0 && dis >= P[c].al && dis <= P[c].ar && P[tar].hp > P[c].at && P[c].g != P[tar].g){
					P[tar].hp -= P[c].at;
					printf("%d\n", P[tar].hp);
				}else	printf("INVALID\n");
				continue;
			}
			if (s[0] == 'D'){
				scanf("%s", s);
				int tar;
				scanf("%d", &tar);
				int dis = abs(P[c].x - P[tar].x) + abs(P[c].y - P[tar].y);
				if (P[c].hp >0 && dis >= P[c].al && dis <= P[c].ar && P[tar].hp > 0 && P[tar].hp <= P[c].at && P[c].g != P[tar].g){
					P[tar].hp -= P[c].at;
					printf("%d\n", P[tar].hp);
				}else	printf("INVALID\n");
				continue;
			}
		}
	}
    return 0;
}
