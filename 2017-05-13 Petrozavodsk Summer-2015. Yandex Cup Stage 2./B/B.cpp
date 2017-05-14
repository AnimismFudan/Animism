#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VEC;

VEC que[1010000];
int n, m;
int mark[100], val[100][100];
int mk[100][100];
char A[110], B[110];
int ans;

map<int,int> done;

int has(VEC u) {
	int ans = 0;
	for (int i = 0; i < 7; i++)
		ans = ans * 9 + (u[i] + 2);
	ans = ans * 29 + (u[7] + 1);
	return ans;
}

int proc(char a) {
	if (a <= '9' && a >= '0') return a - '0';
	else if (a == 'A') return 1;
	else if (a == 'T') return 10;
	else if (a == 'J') return 11;
	else if (a == 'Q') return 12;
	else return 13;
}

int main() {
	freopen("best.in","r",stdin);
	freopen("best.out","w",stdout);
	scanf("%s",A + 1);
	scanf("%s",B + 1);
	n = 28; m = 24;
	int L = 0, R = 0;
	VEC vec;
	vec.clear();
	for (int i = 0; i < 7; i++) vec.push_back(i);
	vec.push_back(1);
	que[++R] = vec;
	ans = 28;
	int top = 0;
	for (int i = 0; i < 7; i++)
		for (int j = 0; j <= i; j++)
			mk[i][j] = proc(A[++top]);
	for (int i = 0; i < 7; i++)
		for (int j = 0; j <= i; j++)
			val[i][j] = mk[j - i + 6][j];

	for (int i = 1; i <= 24; i++)
		mark[i] = proc(B[i]);
	
	while (L < R) {
		VEC u = que[++L];
		int cnt = 0;
		for (int i = 0; i < 7; i++)
			cnt += u[i] + 1;
		ans = min(ans, cnt);
		for (int a = 0; a < 7; a++) {
			if (a > 0 && u[a] == u[a - 1]) continue;
			if (u[a] < 0) continue;
			for (int b = a + 1; b < 7; b++) {
				if (b > 0 && u[b] == u[b - 1]) continue;
				if (u[b] < 0) continue;
				if (val[a][u[a]] + val[b][u[b]] != 13) continue;
				VEC v = u;
				v[a]--; v[b]--;
				if (done[has(v)]) continue;
				done[has(v)] = 1;
				que[++R] = v;
			}
		}
		for (int a = 0; a < 7; a++) {
			if (a > 0 && u[a] == u[a - 1]) continue;
			if (u[a] < 0) continue;
			if (val[a][u[a]] != 13) continue;
			VEC v = u;
			v[a]--;
			if (done[has(v)]) continue;
			done[has(v)] = 1;
			que[++R] = v;						
		}
		for (int a = 0; a < 7; a++) {
			if (a > 0 && u[a] == u[a - 1]) continue;
			if (u[a] < 0|| u[7] > 24) continue;
			if (val[a][u[a]] + mark[u[7]] != 13) continue;
			VEC v = u;
			v[a]--;
			v[7]++;
			if (done[has(v)]) continue;
			done[has(v)] = 1;
			que[++R] = v;
		}
		if (u[7] <= 24) {
			VEC v = u;
			v[7]++;
			if (done[has(v)]) continue;
			done[has(v)] = 1;
			que[++R] = v;
		}
	}

	printf("%d\n",ans);
	return 0;
}
