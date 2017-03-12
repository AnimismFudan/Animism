#include <bits/stdc++.h>
using namespace std;

int w[1010],h[1010],vis[1010];
int n,T;

int main() {
    for (scanf("%d",&T); T; T--) {
		scanf("%d",&n);
		for (int i = 1; i <= n; i++) scanf("%d",&w[i]);
		for (int i = 1; i <= n; i++) scanf("%d",&h[i]);
		sort(h + 1, h + n + 1);
		reverse(h + 1, h + n + 1);
		if (n > 2)
			sort(w + 2, w + n + 1);
		int sing = w[1] * h[1];
		for (int i = 1; i <= n; i++) vis[i] = 0;
		vis[1] = 1;
		bool fl = true;
		for (int i = 2; i <= n; i++) {
			bool flag = false;
			for (int j = 1; j <= n; j++) {
				if (!vis[j] && w[i] * h[j] < sing) {
					flag = true; vis[j] = 1;
					break;
				}		
			}
			if (!flag) { fl = false; break; }
		}
		if (fl) printf("YES\n");
		else printf("NO\n");
    }
    return 0;
}
