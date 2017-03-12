#include <bits/stdc++.h>
using namespace std;
#define LL long long

int a[5];

void work(){
	if (a[0] == a[1] && a[0] == a[2]){
		if (a[0] == 13){
			printf("*\n");
			return;
		}
		a[0]++;a[1]++;a[2]++;
		printf("%d %d %d\n", a[0], a[1], a[2]);
		return;
	}
	if (a[0] == a[2]) swap(a[1], a[2]);
	if (a[1] == a[2]) swap(a[0], a[2]);
	if (a[0] == a[1]){
		a[2]++;
		if (a[0] == a[2])a[2]++;
		if (a[2] > 13){
			a[2] = 1;
			a[0]++;
			a[1]++;
		}
		if (a[0] > 13)
			a[0] = a[1] = a[2] = 1;
		sort (a, a + 3);
		printf("%d %d %d\n", a[0], a[1], a[2]);
		return;
	}
	a[0] = a[1] = 1;
	a[2] = 2;
	printf("%d %d %d\n", a[0], a[1], a[2]);
}

int main(){
	scanf("%d%d%d", &a[0], &a[1], &a[2]);
	while (a[0] && a[1] && a[2]){
		work();
		scanf("%d%d%d", &a[0], &a[1], &a[2]);
	}
	return 0;
}
