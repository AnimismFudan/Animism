#include <bits/stdc++.h>
#define maxn 101000

using namespace std;


struct str { int a,b,p; } dot[maxn];

struct pmc {
	bool operator () (int a,int b) {
		return (dot[a].b < dot[b].b);
	}
};
	
set<int,pmc> st;

int n,ans[maxn];

bool cmp(const str &a, const str &b) {
	return (a.a < b.a);
}

int main() {
	freopen("codecoder.in","r",stdin);
	freopen("codecoder.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) {
		int a, b;
		scanf("%d %d",&a,&b);
		dot[i] = (str) { a, b, i };
	}
	sort(dot + 1, dot + n + 1, cmp);

	for (int i = 1; i <= n; i++)
		st.insert(i);

	int q = 1, v = 1, js = 0;
	for (int u = 1; u <= n; u++) {	
		js = max(js, dot[u].b);
		while (true) {
			v = max(v, u);
			bool flag = false;
			for (; q <= v; q++) {
				flag = true;
				js = max(js, dot[q].b);			
			}
			while (!st.empty() && dot[*st.begin()].b < js) {
				int v_ = *st.begin();				
				v = max(v, v_);
				flag = true;
				st.erase(st.begin());
			}
			if (!flag) break;
		}
		ans[dot[u].p] = v;
	}
	for (int i = 1; i <= n; i++)
		printf("%d\n",ans[i] - 1);
	return 0;
}
