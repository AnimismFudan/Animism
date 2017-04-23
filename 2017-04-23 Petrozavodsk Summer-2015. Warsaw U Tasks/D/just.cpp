#include <bits/stdc++.h>
using namespace std;

vector <int> vec[1010000];
int n;
int f[1010000];

int main() {
	freopen("just.out","w",stdout);
	vec[1].push_back(1);
	for (int i = 2; i <= 100000; i++) {				
		int u = sqrt(i);		
		while (u * u < i) u++;
		if (u * u == i) vec[i].push_back(u);
		for (int j = 1; j * j < i; j++) {
			if (!vec[i - j * j].empty() && vec[i - j * j].back() < j) {
				vec[i] = vec[i - j * j];
				vec[i].push_back(j);
				break;
			}
		}
	}
	for (int i = 1; i <= 100000; i++)
		if (!vec[i].empty()) printf("%d\n",vec[i].back());
		else printf("-\n");
	
				 /*for (int i = 1; i <= 300; i++) {
		for (int j = 0; j < (int) vec[i].size(); j++) {
			printf("%d ",vec[i][j]);
		}
		putchar('\n');
		}*/
	
	return 0;
	for (int i = 1; i <= 100; i++) {
		int just = 1;
		for (int j = 0; j < (int) vec[i].size(); j++) {		
			for (; just < vec[i][j]; just++)
				printf("%d ",just);
			just++;
			//printf("%d ",vec[i][j]);
		}
		putchar('\n');
	}
	return 0;
}
