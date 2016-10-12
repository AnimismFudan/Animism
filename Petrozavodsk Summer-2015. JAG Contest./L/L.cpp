#include <bits/stdc++.h>
using namespace std;

int f[22][22][22][22];
int done[410];
int n,m;
char s[22][22];

int main() {
	//freopen("L.in","r",stdin);
	//freopen("L.out","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++)
		scanf("%s",s[i] + 1);
	for (int A = 1; A <= n; A++)
		for (int B = 1; B <= m; B++) {
			for (int x1 = 1; x1 + A - 1 <= n; x1++)
				for (int y1 = 1; y1 + B - 1 <= m; y1++) {
					int x2 = x1 + A - 1;
					int y2 = y1 + B - 1;
					memset(done,0,sizeof(done));
					for (int a = x1; a <= x2; a++)
						for (int b = y1; b <= y2; b++) {
							if (s[a][b] == 'X') continue;
							int js = 0;
							if (a > x1 && b > y1)
								js ^= f[x1][a - 1][y1][b - 1];
							if (a < x2 && b > y1)
								js ^= f[a + 1][x2][y1][b - 1];
							if (a > x1 && b < y2)
								js ^= f[x1][a - 1][b + 1][y2];
							if (a < x2 && b < y2)
								js ^= f[a + 1][x2][b + 1][y2];
							done[js] = 1;
						}
					for (int i = 0; i <= n * m + 1; i++)
						if (!done[i]) {
							f[x1][x2][y1][y2] = i;
							break;
						}
				}
		}
	if (f[1][n][1][m]) printf("First\n");
	else printf("Second\n");
	return 0;
}
