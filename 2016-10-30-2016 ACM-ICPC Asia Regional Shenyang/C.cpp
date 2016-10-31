#include <bits/stdc++.h>
#define intl long long
using namespace std;

const intl Mo = 2147493647LL;

struct matrix {
    intl v[7][7];

    void operator *= (matrix b) {
    matrix a; memcpy(a.v,v,sizeof(a.v));
    memset(v,0,sizeof(v));
    for (int i = 0; i <= 6; i++)
        for (int j = 0; j <= 6; j++)
        for (int k = 0; k <= 6; k++)
            (v[i][j] += a.v[i][k] * b.v[k][j]) %= Mo;
    } 
} trans,ans;

intl Ans,a,b,n;
int T;

void fpm(intl n) {
    memset(ans.v,0,sizeof(ans.v));
    for (int i = 0; i <= 6; i++) ans.v[i][i] = 1;
    matrix a = trans;
    for (; n; n >>= 1) {
    if (n & 1LL) ans *= a;
    a *= a;
    }
    return;
}

int main() {
    trans.v[0][0] = 1;
    trans.v[0][1] = 1; trans.v[1][1] = 1;
    trans.v[0][2] = 1; trans.v[1][2] = 2; trans.v[2][2] = 1;
    trans.v[0][3] = 1; trans.v[1][3] = 3; trans.v[2][3] = 3; trans.v[3][3] = 1;
    trans.v[0][4] = 1; trans.v[1][4] = 4; trans.v[2][4] = 6; trans.v[3][4] = 4; trans.v[4][4] = 1;
    trans.v[6][5] = 1;
    trans.v[5][6] = 2; trans.v[6][6] = 1;
    trans.v[0][6] = 1; trans.v[1][6] = 4; trans.v[2][6] = 6; trans.v[3][6] = 4; trans.v[4][6] = 1;  
    for (scanf("%d",&T); T; T--) {
    scanf("%I64d %I64d %I64d",&n,&a,&b);
    if (n == 1LL) printf("%I64d\n",a);
    else if (n == 2LL) printf("%I64d\n", b);
    else {
        fpm(n - 2);
        Ans = 0;
        intl js = 1LL;
        for (int i = 0; i <= 4; i++) {
        (Ans += js * ans.v[i][6]) %= Mo;
        js *= 2LL;
        }
        Ans += ((ans.v[5][6] * a) % Mo + ans.v[6][6] * b) % Mo;
        Ans %= Mo;
        printf("%I64d\n",Ans);
    }
    }
    return 0;
    
}
