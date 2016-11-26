#include <bits/stdc++.h>
using namespace std;

int Test, N;

int main(){
	freopen("L.in", "r", stdin);
	freopen("L.out", "w", stdout);
	scanf("%d", &Test);
	for (int tt = 1; tt <= Test; tt++){
		scanf("%d", &N);
		printf("Case #%d: ", tt);
		cout << 2 * N - 1 << endl;
	}
}