#include <bits/stdc++.h>
using namespace std;

int A[30];
int T;
bool flag;

bool eq(int a,int b,int c,int d) {
	return (A[a] == A[b] && A[a] == A[c] && A[a] == A[d]);
}

int main() {
	for (scanf("%d",&T); T; T--) {
		for (int i = 1; i <= 24; i++) scanf("%d",&A[i]);
		flag = false;
		if (eq(1,2,3,4) && eq(5,6,7,8) && eq(9,10,11,12) &&
			eq(13,14,15,16) && eq(17,18,19,20) && eq(21,22,23,24))
			flag = true;
		if (eq(1,2,3,4) && eq(9,10,11,12) && eq(5,6,22,24)
			&& eq(21,23,13,14) && eq(15,16,17,19) && eq(18,20,7,8))
			flag = true;
		if (eq(1,2,3,4) && eq(9,10,11,12) && eq(5,6,17,19)
			&& eq(18,20,13,14) && eq(15,16,22,24) && eq(23,21,7,8))
			flag = true;
		if (eq(21,22,23,24) && eq(17,18,19,20) && eq(13,15,2,4)
			&& eq(1,3,6,8) && eq(5,7,10,12) && eq(9,11,14,16))
			flag = true;
		if (eq(21,22,23,24) && eq(17,18,19,20) && eq(13,15,10,12)
			&& eq(9,11,6,8) && eq(5,7,2,4) && eq(1,3,14,16))
			flag = true;
		if (eq(5,6,7,8) && eq(13,14,15,16) && eq(9,10,21,22) &&
			eq(23,24,1,2) && eq(3,4,17,18) && eq(19,20,11,12))
			flag = true;
		if (eq(5,6,7,8) && eq(13,14,15,16) && eq(9,10,17,18) &&
			eq(19,20,1,2) && eq(3,4,21,22) && eq(23,24,11,12))
			flag = true;
		if (flag) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
