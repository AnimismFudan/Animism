#include <bits/stdc++.h>
using namespace std;

int Test;
int A[2][2], B[2][2];
bool flag;

void Rotate(int A[2][2]){
	int C[2][2];
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			C[i][j] = A[j][1 - i];
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			A[i][j] = C[i][j];
}

void Mirror(int A[2][2]){
	for (int i = 0; i < 2; i++)
		swap(A[i][0], A[i][1]);
}

bool same(int A[2][2], int B[2][2]){
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			if (A[i][j] != B[i][j])
				return 0;
	return 1;
}

int main(){
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
	scanf("%d", &Test);
	for (int tt = 1; tt <= Test; tt++){
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				scanf("%d", &A[i][j]);
		for (int i = 0 ; i < 2; i++)
			for (int j = 0; j < 2; j++)
				scanf("%d", &B[i][j]);
		flag = 0;
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 2; j++){
				if (same(A, B)){
					flag = 1;
					break;
				}
//				Mirror(A);
			}
			Rotate(A);
		}
		printf("Case #%d: ", tt);
		if (flag)printf("POSSIBLE\n");
		else printf("IMPOSSIBLE\n");
	}
}