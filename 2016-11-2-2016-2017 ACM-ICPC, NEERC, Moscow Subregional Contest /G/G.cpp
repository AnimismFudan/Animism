#include <bits/stdc++.h>
using namespace std;

int A[101000],B[101000];
int n,top;

int main() {
	freopen("G.in","r",stdin);
	freopen("G.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n - 1; i++) {
		for (int j = n; j >= i + 2; j--) {
			A[++top] = i; B[top] = j;
			A[++top] = j; B[top] = i;
		}
		A[++top] = i; B[top] = i + 1;
	}
	for (int i = n; i >= 2; i--) {
		A[++top] = i;
		B[top] = i - 1;
	}
	printf("%d %d %d\n",B[top], B[top], 0);
	for (int i = top; i > 1; i--) {
		printf("%d %d %d\n",A[i],A[i],B[i]);
	}
	printf("%d %d %d\n",0, B[top], B[1]);
	return 0;
}
