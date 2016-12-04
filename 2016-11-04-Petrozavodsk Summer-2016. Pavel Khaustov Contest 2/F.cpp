#include <bits/stdc++.h>
using namespace std;
const int S[6][6] = {
	{1,1,0,0,0,0},
	{0,0,1,1,0,0},
	{1,0,1,0,1,0},
	{0,1,0,1,1,0},
	{0,1,1,0,0,1},
	{1,0,0,1,0,1}
};

int T[6][6];
int flag[2],p[2][6];
char s[110];

int dis(int a,int b) {
	int cnt = 0;
	for (int i = 0; i < 6; i++)
		cnt += S[a][i] ^ T[b][i];
	return cnt;
}

int Dis(int a,int b) {
	int cnt = 0;
	for (int i = 0; i < 6; i++)
		cnt += S[i][a] ^ T[i][b];
	return cnt;
}

int main() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) 
			putchar('A' + S[i][j]);
		putchar('\n');
	}
	fflush(stdout);
	while (scanf("%s",s + 1) != EOF && s[1] == 'R') {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				char ch;
				do ch = getchar();
				while (ch != 'A' && ch != 'B');
				T[i][j] = ch - 'A';
			}
		}
		flag[0] = flag[1] = 1;
		for (int j = 0; j < 6; j++)
			p[0][j] = p[1][j] = -1;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++)
				if (dis(i, j) <= 1) p[0][j] = i;
		}
		for (int i = 0; i < 6; i++)
			if (p[0][i] == -1) flag[0] = 0;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++)
				if (Dis(i, j) <= 1) p[1][j] = i;
		}
		for (int i = 0; i < 6; i++)
			if (p[1][i] == -1) flag[1] = 0;		
		if (flag[0] && flag[1]) {		
			printf("0\n");			
			for (int i = 0; i < 6; i++){
				if (i) printf(" ");
				printf("%d",p[0][i] + 1);
			}
			putchar('\n');			
			for (int i = 0; i < 6; i++){
				if (i) printf(" ");
				printf("%d",p[1][i] + 1);
			}
			putchar('\n');		
		
		} else if (flag[0]){
			printf("1\n");
			for (int i = 0; i < 6; i++){
				if (i) printf(" ");
				printf("%d",p[0][i] + 1);
			}
			putchar('\n');		
		} else {
			printf("2\n");
			for (int i = 0; i < 6; i++){
				if (i) printf(" ");
				printf("%d",p[1][i] + 1);
			}
			putchar('\n');					
		}
		fflush(stdout);
	}
	return 0;
}
