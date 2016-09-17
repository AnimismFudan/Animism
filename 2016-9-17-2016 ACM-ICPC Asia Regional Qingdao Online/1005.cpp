#include <bits/stdc++.h>
using namespace std;
int main() {
    int T,n;
    for (scanf("%d",&T); T; T--) {
	scanf("%d",&n);
	if(n & 1) printf("Balanced\n");
	else printf("Bad\n");
    }
}
