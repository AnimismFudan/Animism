#include <bits/stdc++.h>
#define intl long long
using namespace std;

struct point {
    intl x,y,val;
    int mark;
    void read() {
	scanf("%lld %lld %lld",&x,&y,&val);
    }
} dot[3010],dt[3010];

intl sumL[2][3010],sumR[2][3010];
intl ans,X,Y;
int n,m;

bool cmp(const point &a, const point &b) {
    return ((a.x * Y - a.y * X < b.x * Y - b.y * X) ||
	    (a.x * Y - a.y * X == b.x * Y - b.y * X && a.x < b.x) ||
	    (a.x * Y - a.y * X == b.x * Y - b.y * X && a.x == b.x && a.y < b.y));
}

void solve() {
    for (int i = 1; i <= n; i++)
	dt[i] = dot[i];
    sort(dt + 1, dt + n + 1, cmp);
    for (int i = 1; i <= n; i++) {
	sumL[0][i] = sumL[0][i - 1];
	sumL[1][i] = sumL[1][i - 1];
	sumL[dt[i].mark][i] += dt[i].val;
    }
    sumR[0][n + 1] = sumR[1][n + 1] = 0;
    for (int i = n; i >= 1; i--) {
	sumR[0][i] = sumR[0][i + 1];
	sumR[1][i] = sumR[1][i + 1];
	sumR[dt[i].mark][i] += dt[i].val;
    }

    for (int i = 0; i <= n; i++)
	ans = min(ans, sumL[0][i] + sumR[1][i + 1]);
    for (int i = 0; i <= n; i++)
	ans = min(ans, sumL[1][i] + sumR[0][i + 1]);
    
}

int main() {
    freopen("G.in","r",stdin);
    freopen("G.out","w",stdout);
    while (scanf("%d %d",&n,&m) != EOF && n && m) {
	ans = 1LL << 60;
	for (int i = 1; i <= n; i++) {
	    dot[i].read();
	    dot[i].mark = 0;
	}
	for (int i = n + 1; i <= n + m; i++) {
	    dot[i].read();
	    dot[i].mark = 1;
	}
	n += m;
	for (int i = 1; i <= n; i++)
	    for (int j = i + 1; j <= n; j++) {
	        X = dot[i].x - dot[j].x;
		Y = dot[i].y - dot[j].y;
		solve();
	    }
	cout << ans << endl;
    }
    return 0;
}
