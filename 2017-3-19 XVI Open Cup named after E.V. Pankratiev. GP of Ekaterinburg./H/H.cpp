#include <bits/stdc++.h>
using namespace std;

int R, N, l, r;
int A[1010][10];
class rec{
	public:
	int a[10];
}p, pp, q[100010];

bool operator < (const rec &A, const rec &B){
	for (int i = 0; i <= 5; i++){
		if (A.a[i] < B.a[i]) return 1;
		if (A.a[i] > B.a[i]) return 0;
	}
	return 0;
}

map <rec, bool> vis;

int main() {
	freopen("H.in","r",stdin);
	//freopen("H_.out","w",stdout);
	scanf("%d%d", &R, &N);
	for (int i = 1; i <= R; i++)
		for (int j = 1; j <= N; j++)
			scanf("%d", &A[i][j]);
	l = r = 1;
	for (int i = 1; i <= N; i++)
		q[1].a[i] = i;
	vis[q[1]] = 1;
	for (; l <= r; l++)
		for (int i = 1; i <= R; i++){
			p = q[l];
			for (int j = 1; j <= N; j++)
				pp.a[A[i][j]] = p.a[j];
			if (vis[pp] == 0){
				vis[pp] = 1;
				q[++r] = pp;
			}
		}
	cout << r << endl;
	return 0;
}
