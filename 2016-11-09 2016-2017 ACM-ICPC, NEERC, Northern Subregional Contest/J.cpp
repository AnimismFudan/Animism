#include <bits/stdc++.h>
using namespace std;

char ans[100];
int n,top;

int main() {
	freopen("java2016.in","r",stdin);
	freopen("java2016.out","w",stdout);
	scanf("%d",&n);
	if (!n) {
		printf("?/?/?\n");
		return 0;
	}
	printf("a = ? max ?\n");
	for (int i = 1; i <= 10; i++) {
		printf("%c = %c max %c\n",'a' + i, 'a' + i - 1, 'a' + i - 1);
	}
	
	printf("l = k / d\n");
	// l = 1;
	for (int i = 1; i <= 8; i++) {
		printf("%c = %c + %c\n",'l' + i, 'l' + i - 1, 'l' + i - 1);
	}
	for (int i = 0; i <= 8; i++) {
		if ((n >> i) & 1) ans[++top] = 'l' + i;
	}
	for (int i = 1; i < top; i++)
		printf("%c + ",ans[i]);
	printf("%c\n",ans[top]);
	return 0;
}
