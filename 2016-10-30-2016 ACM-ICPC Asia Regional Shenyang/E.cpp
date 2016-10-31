#include <bits/stdc++.h>
using namespace std;

const int MaxN = 107;

int T,n,m,s,p[MaxN],ans;
bool lnk[MaxN][MaxN];
bitset<MaxN> bst[MaxN],now,tmp;

void DFS(int x, int s)
{
    if (s==0) { ans++; return; }
    if (x>p[0]) return;
    if (p[0]-x >= s) DFS(x+1, s);
    tmp = now & bst[p[x]];
    if (tmp == now)
    {
        now[p[x]] = true;
        DFS(x+1, s-1);
        now[p[x]] = false;
    }
    return;
}

int main()
{
    int i,j,a,b;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &n, &m, &s);
        for (i=1; i<=n; i++)
        {
            bst[i].reset();
            bst[i][i] = true;
        }
        for (i=1; i<=m; i++)
        {
            scanf("%d%d", &a, &b);
            bst[a][b] = bst[b][a] = true;
        }
        ans = 0;
        for (i=1; i<=n; i++)
        {
            p[0] = 0;
            for (j=i+1; j<=n; j++)
                if(bst[i][j]) p[++p[0]] = j;
            if (p[0]>=s-1)
            {
                now.reset();
                now[i] = true;
                DFS(1,s-1);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
