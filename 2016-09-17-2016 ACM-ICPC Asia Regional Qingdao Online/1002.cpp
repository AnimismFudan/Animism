#include <bits/stdc++.h>
using namespace std;
double Ans[1010000];
char s[5010000];
int len,T,n;

int main() {
    double ans = 0;
    for (int i = 1; i <= 1000000; i++) {
    ans += 1.0 / (double) i / (double) i;
    Ans[i] = ans;
    }
    while(scanf("%s",s + 1) != EOF) {
    len = strlen(s + 1);
    if (len >= 7) printf("%.5lf\n",Ans[1000000]);
    else {
        n = 0;
        for (int i = 1; i <= len; i++)
        n = n * 10 + (int) (s[i] - '0');
        printf("%.5lf\n",Ans[n]);
    }
    }
    return 0;
}