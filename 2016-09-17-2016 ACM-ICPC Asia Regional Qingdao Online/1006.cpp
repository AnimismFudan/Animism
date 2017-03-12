#include <bits/stdc++.h>
using namespace std;

int Test, N, M, x, y, ans, res, odd;
int du[100010], a[100010];

int main() {
    scanf("%d",&Test);
    while (Test--){
        scanf("%d%d",&N,&M);
        for (int i = 1; i <= N; i++){
            scanf("%d", &a[i]);
            du[i] = 0;
        }
        for (int i = 1; i <= M; i++){
            scanf("%d%d", &x, &y);
            du[x]++;
            du[y]++;
        }
        ans = 0;
        odd = 0;
        for (int i = 1; i <= N; i++){
            if (du[i] & 1)odd++;
            int t = (du[i] + 1) >> 1;
            if (t & 1) ans ^= a[i];
        }
        if (odd == 0){
            res = ans;
            ans = -1;
            for (int i = 1; i <= N; i++)
                ans = max(ans, res ^ a[i]);
            printf("%d\n", ans);
        }
        else if (odd == 2)printf("%d\n",ans);
        else printf("Impossible\n");
    }
    return 0;
}