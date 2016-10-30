#include <bits/stdc++.h>
using namespace std;
#define LL long long

int h[110];
char c0[10] = {'.', '*', '*', '*', '*', '*', '*', '*', '*', '.'};
char c1[10] = {'*', '.', '.', '*', '*', '.', '*', '*', '.', '*'};
char c2[10] = {'*', '.', '*', '.', '.', '.', '*', '*', '*', '*'};
char c3[10] = {'*', '.', '.', '.', '*', '*', '.', '*', '*', '.'};
char c4[10] = {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'};
char c5[10] = {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'};

int D;
char s[1010], s1[1010], s2[1010], s3[1010];

void read(char *a){
	char ch = getchar();
	while (ch != '\n' && ch != '\r'){
		*a = ch;
		a++;
		ch = getchar();
	}
	*a = 0;
}

int main(){
	freopen("I.in", "r", stdin);
	freopen("I.out", "w", stdout);
	h[1] = 1;
	h[5] = 2;
	h[3] = 3;
	h[11] = 4;
	h[9] = 5;
	h[7] = 6;
	h[15] = 7;
	h[13] = 8;
	h[6] = 9;
	h[14] = 0;
	scanf("%d\n", &D);
	while (D){
		scanf("%s\n", s);
		if (s[0] == 'S'){
			scanf("%s\n", s);
			for (int i = 0; i < D; i++){
				if (i)printf(" ");
				int x = s[i] - '0';
				printf("%c%c", c0[x], c1[x]);
			}
			printf("\n");
			for (int i = 0; i < D; i++){
				if (i)printf(" ");
				int x = s[i] - '0';
				printf("%c%c", c2[x], c3[x]);
			}
			printf("\n");
			for (int i = 0; i < D; i++){
				if (i)printf(" ");
				int x = s[i] - '0';
				printf("%c%c", c4[x], c5[x]);
			}
			printf("\n");
		}else{
			read(s1);
			read(s2);
			read(s3);
			for (int i = 0; i < D; i++){
				int p = i * 3;
				int x = 0;
				x = (x << 1) ^ (s3[p + 1] == '*');
				x = (x << 1) ^ (s3[p] == '*');
				x = (x << 1) ^ (s2[p + 1] == '*');
				x = (x << 1) ^ (s2[p] == '*');
				x = (x << 1) ^ (s1[p + 1] == '*');
				x = (x << 1) ^ (s1[p] == '*');
				printf("%d",h[x]);
			}
			printf("\n");
		}
		scanf("%d", &D);
	}
	return 0;
}
