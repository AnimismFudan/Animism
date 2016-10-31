#include <bits/stdc++.h>
using namespace std;

char s[1010];
int T,n,ans;

int main() {
    for (scanf("%d",&T); T; T--) {
    scanf("%s",s + 1);
    n = strlen(s + 1); ans = 0;
    for (int i = 1; i <= n; i++)
        if (s[i] == 'H') ans++;
        else if (s[i] == 'O') ans += 16;
        else ans += 12;
    printf("%d\n",ans);
    }
    return 0;
}
