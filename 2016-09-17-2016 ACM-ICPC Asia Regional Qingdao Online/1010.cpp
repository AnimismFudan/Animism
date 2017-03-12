#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, T, len;
LL ans;
LL pre_t[110], pre_s[110];

class herb{
    public:
    int t, s;
    double d;
}P[110], p;

bool cmpd(const herb &A, const herb &B){
    return A.d > B.d;
}

double f1(int step, int t){
    LL tt = pre_t[step - 1] + T - t;
    int x = lower_bound(pre_t + 1, pre_t + N + 1, tt) - pre_t;
    if (pre_t[x] == tt)return pre_s[x] - pre_s[step - 1];
    tt = tt - pre_t[x - 1];
    return pre_s[x - 1] - pre_s[step - 1] + P[x].d * tt;
}

void dfs(int step, int t, LL s){
    if (s + f1(step, t) <= ans)
        return;
    ans = max(ans, s);
    //can get more cut
    
    if (step > N)
        return;
    if (t + P[step].t <= T)
        dfs(step + 1, t + P[step].t, s + P[step].s);
    dfs(step + 1, t, s);
}

int main() {
    while (scanf("%d%d", &N, &T)!=EOF){
        len = 0;
        ans = 0;
        for (int i = 1; i <= N; i++){
            scanf("%d%d", &p.t, &p.s);
            if (p.t == 0)
                ans+=p.s;
            else if (p.s > 0 && p.t <= T){
                P[++len] = p;
                P[len].d = double(P[len].s) / P[len].t;
            }
        }
        N = len;
        sort(P + 1, P + N + 1, cmpd);
        for (int i = 1; i <= N; i++){
            pre_t[i] = pre_t[i - 1] + P[i].t;
            pre_s[i] = pre_s[i - 1] + P[i].s;
        }
        dfs(1, 0, ans);
        cout << ans << endl;
    }
    return 0;
}