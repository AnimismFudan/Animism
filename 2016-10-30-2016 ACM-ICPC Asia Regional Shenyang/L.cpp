#include <bits/stdc++.h>
using namespace std;

bool hahaha;
int T,cl;
int tp,pt;
int wp[10],wp_[10],clo[1010000],Mark[1010000];
double p[1010000],q[1010000];
int fa[10],ST[1010000],TS[1010000];
int po[11];
char s[10][10];
int js,tt,top;
int stt[10100];
int cntt[401000];
int mp[260][3000];
bool heihei;
int find(int a) { return (fa[a] == a ? a : (fa[a] = find(fa[a]))); }
    
void add(int st, double P) {
    if (st == -1) st = 0;
    if (cl != clo[st]) {
		clo[st] = cl, Mark[st] = ++pt;
		TS[pt] = st;
		q[pt] = P;
    } else {
		q[Mark[st]] += P;
    }
    return;
}

int get_(int a,int b) {
    return ((a >> b) & 1);
}

void solve(int u, int mark) {
    cl++; pt = 0;

    tt = 0;
    for (int st = 0; st < (1 << 8); st++) {
		bool flag = true;
		int al = 1;
		for (int i = 0; i < 8; i++) {
			if (s[u][i] == '.') al *= 2;
			if (s[u][i] == 'A' && ((st >> i) & 1) == mark) { flag = false; break; }
			if (s[u][i] == 'B' && ((st >> i) & 1) != mark) { flag = false; break; }        
		}
		if (!flag) continue;
		stt[++tt] = st;
    }
    for (int t = 1; t <= tp; t++) {
		if (!cntt[ST[t]]) cntt[ST[t]] = ++top;
    }
    // 1 choose, 0 not choose;
    for (; tt; tt--) {
		int st = stt[tt];
		int al = 1;
		for (int i = 0; i < 8; i++)
			if (s[u][i] == '.') al *= 2;
		for (int t = 1; t <= tp; t++) {
			int st_ = ST[t];
			int just;
			if ((just = mp[st][cntt[st_]])) {
				add(just, p[t] / (double) al);
				continue;
			}
			for (int i = 0; i < 8; i++) {
				wp[i] = st_ % 5;
				st_ /= 5;
			}
			for (int i = 0; i < 8; i++) fa[i] = i;
			for (int i = 1; i < 8; i++) {
				if (get_(st, i) && get_(st, i - 1)) fa[i] = fa[i - 1];
			}
			for (int i = 0; i < 8; i++) {
				if (get_(st, i) && wp[i] == 1) wp_[i] = 1;
				else wp_[i] = 0;
			}
			for (int i = 0; i < 8; i++) {
				wp_[fa[i]] |= wp_[i];
			}
			for (int i = 0; i < 8; i++)
				wp_[i] |= wp_[fa[i]];
        
			for (int i = 0; i < 8; i++)
				for (int j = i + 1; j < 8; j++) {
					if (!wp[i] || (wp[i] != wp[j])) continue;            
					if (find(i) == find(j)) continue;
					if (!get_(st, i) || !get_(st, j)) continue;
					wp_[fa[i]] |= wp_[fa[j]];
					wp_[fa[j]] |= wp_[fa[i]];
					fa[fa[i]] = fa[j];
				}
			int cnt = 1;
			for (int i = 0; i < 8; i++)
				wp_[i] |= wp_[find(i)];
        
			for (int i = 0; i < 8; i++) {
				if (!get_(st, i)) continue;
				if (wp_[i]) continue;
				if (wp_[fa[i]]) wp_[i] = wp_[fa[i]];
				else {
					wp_[i] = ++cnt;
					wp_[fa[i]] = cnt;
				}
			}
			bool fl = false;
			for (int i = 0; i < 8; i++) {
				if (wp_[i] == 1) fl = true;
			}
			if (!fl) {
				add(0, p[t] / (double) al);
				mp[st][cntt[ST[t]]] = -1;
			}
			else {
				int sing = 0;
				for (int i = 7; i >= 0; i--)
					sing = sing * 5 + wp_[i];
				add(sing, p[t] / (double) al);
				mp[st][cntt[ST[t]]] = sing;
			}
		}
    }

    tp = pt;
    for (int i = 1; i <= pt; i++) ST[i] = TS[i], p[i] = q[i];
    return;
}

double proc(int mark) {
    tp = 0; ST[++tp] = js; p[tp] = 1.0;
    for (int i = 0; i < 8; i++) {
		solve(i, mark);
    }
    double ans = 0;
    for (int i = 1; i <= tp; i++) {
		bool flag = false;
		int st = ST[i];
		for (int j = 0; j < 8; j++) {
			if (st % 5 == 1) { flag = true; break; };
			st /= 5;
		}
		if (flag) ans += p[i];
    }
    return ans;
}

int main() {
    po[0] = 1;
    for (int i = 1; i <= 9; i++) po[i] = po[i - 1] * 5;
    js = 0;
    for (int i = 0; i < 8; i++)
		js += po[i];
    for (scanf("%d",&T); T; T--) {
		for (int i = 0; i < 8; i++)
			scanf("%s",s[i]);
    
    
		double ansa = proc(0);

		for (int i = 0; i < 8; i++)
			for (int j = i + 1; j < 8; j++)
				swap(s[i][j], s[j][i]);
    
		double ansb = proc(1);
		printf("Alice %.6lf Bob %.6lf\n",ansa,ansb);
    
    }
    //printf("%d\n",top);
    return 0;
}
