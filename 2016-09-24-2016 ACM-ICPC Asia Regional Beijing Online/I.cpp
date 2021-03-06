#include <bits/stdc++.h>
#define maxn 201000
#define intl long long
using namespace std;

int x,ta,tb,Ta[maxn],Ta_[maxn],Da[maxn],Tb[maxn],Tb_[maxn],Db[maxn];
int top,tp,q,n,m;
intl ans,Ans,now,X[maxn];

struct Proc {
    intl L,R,D;
} proc[maxn];
    
struct pmc{
    bool operator () (int a,int b) {
	return (proc[a].R < proc[b].R || (proc[a].R == proc[b].R && a < b));
    }
};
    
set<int,pmc> st;

map<intl,int> mp;

bool cmp(const Proc &a, const Proc &b) {
    return (a.L < b.L);
}

void add(intl L,intl R,intl D) {
    proc[++top] = (Proc) { L, R, D };
    mp[L] = 1; mp[R + 1LL] = 1;
}

void solve_A(intl T,intl T_,intl D) {
    ans += (intl) D;
    T += T_;
    if (T < (intl) x || T > (intl) x + (intl) tb) { ans -= D; return; }
    intl k = (x + (intl) tb - T) / (2LL * T_);
    intl Tr = T + 2LL * T_ * k;
    while (Tr < x) Tr += 2LL * T_;
    while (Tr > x + (intl) tb) Tr -= 2LL * T_;
    while (Tr + 2LL * T_ <= x + (intl) tb) Tr += 2LL * T_;
    intl R = T + T_;
    intl L = Tr + T_ - ta;
    if (L <= R) add(L, R, D);
}

void solve_B(intl T,intl T_,intl D) {
    ans += (intl) D;
    intl R = T + T_;
    T += 2 * T_;
    if (T < (intl) x || T > (intl) x + (intl) tb) {
	add(R - ta, R, D);
	return;
    }
    intl k = ((intl) x + (intl) tb - T) / (2LL * T_);
    intl Tr = T + 2LL * T_ * k;
    while (Tr < x) Tr += 2LL * T_;
    while (Tr > x + (intl) tb) Tr -= 2LL * T_; 
    while (Tr + 2LL * T_ <= x + (intl) tb) Tr += 2LL * T_;
    intl L = Tr + T_ - ta;
    if (L <= R) add(L, R, D);
}

int main() {
    freopen("I.in","r",stdin);
    freopen("I.out","w",stdout);
    while (scanf("%d %d",&ta,&tb) != EOF) {
	scanf("%d",&x);
	scanf("%d %d",&n,&m);
	top = tp = 0;
	ans = 0;
	for (int i = 1; i <= n; i++) {
	    scanf("%d %d %d",&Ta[i], &Ta_[i], &Da[i]);
	}
	for (int i = 1; i <= m; i++) {
	    scanf("%d %d %d",&Tb[i], &Tb_[i], &Db[i]);
	}
	for (int i = 1; i <= n; i++) solve_A(Ta[i], Ta_[i], Da[i]);
	for (int i = 1; i <= m; i++) solve_B(Tb[i], Tb_[i], Db[i]);
	for (map<intl,int> :: iterator i = mp.begin(); i != mp.end(); i++) {
	    X[++tp] = i -> first;
	}
	sort(proc + 1, proc + top + 1, cmp);
	now = ans;
	Ans = ans;
	q = 1;
	for (int i = 1; i <= tp; i++) {
	    intl u = X[i];
	    for (; q <= top && proc[q].L <= u; q++) {
		st.insert(q);
		now -= proc[q].D;
	    }
	    while (!st.empty() && proc[*st.begin()].R < u) {
		now += proc[*st.begin()].D;
		st.erase(st.begin());
	    }
	    Ans = min(Ans, now);
	}
	cout << Ans << endl;
	st.clear(); mp.clear();
    }
    return 0;
}
