#include <bits/stdc++.h>
using namespace std;


int main() {
	freopen("E.in","r",stdin);
	freopen("E.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++)
		scanf("%d",&A[i]);
	sort(A + 1, A + n + 1);
	f[1][0] = count(A[0]);
	f[1][3] = 1 << 25;
	for (int i = 2; i <= n; i++) {
		for (int a = 0; a < 2; a++)
			for (int b = 0; b < 2; b++) {
				if (A[i] == A[i - 1] + 1) {
					
				}
			}
	}
	return 0;
}
