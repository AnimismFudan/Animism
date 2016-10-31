#include <bits/stdc++.h>
using namespace std;

const int MaxN = 256;

int T,N,A,B,tmp[10];
char f[MaxN][MaxN][MaxN];//, p[MaxN][MaxN][MaxN];

int main()
{
    //freopen("D.out", "w", stdout);
    int i,a,b,t,x,y;
    N = A = B = 255;
    for (i=1; i<=N; i++)
    {
        for (a=0; a<=A; a++)
            for (b=0; b<=B; b++)
            {
                tmp[1] = 0; tmp[2] = 1;
                tmp[3] = b; tmp[5] = a;
                tmp[4] = abs(a-b);
                for (int j=1; j<=5; j++)
                {
                    x = tmp[j];
                    if (x>a) continue;
                    y = 0; t = i-1 - f[i-1][b-y][a-x] + 1;
                    y = x+1;
                    if (y <= b)
                    {
                        t = min(t, i - 1 - f[i-1][b-y][a-x]);
                    }
                    if (t>f[i][a][b]) f[i][a][b] = t;//, p[i][a][b] = x;
                }
                //printf("%d %d %d : %d %d\n",i,a,b,f[i][a][b],p[i][a][b]);
            }
    }
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d%d", &N, &A, &B);
        printf("Alice %d Bob %d\n",f[N][A][B], N-f[N][A][B]);
    }
    return 0;
}
