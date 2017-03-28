#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VEC;

int n, l;

set <VEC> st;

queue <VEC> que;

int ans[100],done[110];

VEC mul(VEC a, VEC b) {
	VEC ans;
	ans.resize(n);
	for (int i = 0; i < n; i++)
		ans[i] = b[a[i]];
	return ans;
}

void print(VEC u) {
	for (int i = 0; i < n; i++) printf("%d ",u[i]);
	int cnt = 0;
	//for (int i = 0; i < n; i++)
	//	for (int j = i + 1; j < n; j++)
	//		if (u[i] > u[j]) cnt++;
	//printf("%d",cnt);
	for (int i = 0; i < n; i++) done[i] = 0;
	for (int i = 0; i < n; i++) {
		if (done[i]) continue;
		cnt++;
		for (int j = i; !done[j]; j = u[j]) done[j] = 1;		
	}
	ans[cnt]++;
	putchar('\n');	
}

int main() {
	freopen("just.in","r",stdin);
	freopen("just.out","w",stdout);
	scanf("%d %d",&n,&l);
	VEC just;
	just.resize(n);
	for (int i = 0; i < n; i++) just[i] = i;  
	que.push(just);
	st.insert(just);
	for (int i = 0; i + l <= n; i++) {
		for (int j = 0; j < l - 1; j++)
			just[i + j] = i + j + 1;
		just[i + l - 1] = i;
		for (int j = 0; j < i; j++)
			just[j] = j;
		for (int j = i + l; j < n; j++)
			just[j] = j;
		que.push(just);
		st.insert(just);
	}
	while (!que.empty()) {		
		VEC u = que.front(); que.pop();		
		for (auto i = st.begin(); i != st.end(); i++) {
			VEC v;
			v = mul(u, *i);
			if (st.find(v) == st.end()) {
				st.insert(v);
				que.push(v);
			}
			v = mul(*i, u);
			if (st.find(v) == st.end()) {
				st.insert(v);
				que.push(v);
			}
		}
	}
	printf("%d\n",(int) st.size());
	for (auto i = st.begin(); i != st.end(); i++)
		print(*i);
	for (int i = 1; i <= n; i++) printf("%d ",ans[i]);
	return 0;
}
