#include <bits/stdc++.h>
using namespace std;

int f[110][2][2][2][2][2],A1[110][2][2][2][2][2],A2[110][2][2][2][2][2],A3[110][2][2][2][2][2],A4[110][2][2][2][2][2];
int X[110][2][2][2][2][2],Y[110][2][2][2][2][2],Z[110][2][2][2][2][2],C[110][2][2][2][2][2];
int n,ansx[110],ansy[110],ansz[110];
int jm[6],jr[6],jl[6];
int A[6][110],B[6][110];

struct str {
	int L[2],M[3],R[2];

	void proc(int a,int b,int c,int d,int e,int f,int g) {
		L[0] = a;
		L[1] = b;
		M[0] = c;
		M[1] = d;
		M[2] = e;
		R[0] = f;
		R[1] = g;
	}
} dot[10];

void solve() {
	for (int u = n; u >= 1; u--) {
		int v = u + 1;
		for (int st = 0; st < (1 << 5); st++) {
			int a1,a2,a3,a4,c;
			a1 = st & 1;
			a2 = st >> 1 & 1;
			a3 = st >> 2 & 1;
			a4 = st >> 3 & 1;
			c = st >> 4 & 1;
			for (int x = 0; x < 10; x++)
				for (int y = 0; y < 10; y++)
					for (int z = 0; z < 10; z++) {	
						if ((x + y + c) % 10 != z) continue;
						if (!f[v][c][a1][a2][a3][a4]) continue;
						memset(jr,0,sizeof(jr));
						memset(jm,0,sizeof(jm));
						memset(jl,0,sizeof(jl));
						jr[1] |= a1 | dot[x].R[0];
						jr[2] |= a2 | dot[x].R[1] | dot[y].R[0];
						jr[3] |= a3 | dot[y].R[1] | dot[z].R[0];
						jr[4] |= a4 | dot[z].R[1];
						bool flag = true;
						for (int i = 1; i <= 4; i++)
							if (B[i][v] != jr[i]) flag = false;
						if (!flag) continue;
						jm[1] |= dot[x].M[0];
						jm[2] |= dot[x].M[1] | dot[y].M[0];
						jm[3] |= dot[x].M[2] | dot[y].M[1] | dot[z].M[0];
						jm[4] |= dot[y].M[2] | dot[z].M[1];
						jm[5] |= dot[z].M[2];
						flag = true;
						for (int i = 1; i <= 5; i++)
							if (A[i][u] != jm[i]) flag = false;
						if (!flag) continue;
						jl[1] |= dot[x].L[0];
						jl[2] |= dot[x].L[1] | dot[y].L[0];
						jl[3] |= dot[y].L[1] | dot[z].L[0];
						jl[4] |= dot[z].L[1];
						int k = (x + y + c) / 10;
						if (!f[u][k][jl[1]][jl[2]][jl[3]][jl[4]] && f[v][c][a1][a2][a3][a4]) {
							X[u][k][jl[1]][jl[2]][jl[3]][jl[4]] = x;
							Y[u][k][jl[1]][jl[2]][jl[3]][jl[4]] = y;
							Z[u][k][jl[1]][jl[2]][jl[3]][jl[4]] = z;
							A1[u][k][jl[1]][jl[2]][jl[3]][jl[4]] = a1;
							A2[u][k][jl[1]][jl[2]][jl[3]][jl[4]] = a2;
							A3[u][k][jl[1]][jl[2]][jl[3]][jl[4]] = a3;
							A4[u][k][jl[1]][jl[2]][jl[3]][jl[4]] = a4;
							C[u][k][jl[1]][jl[2]][jl[3]][jl[4]] = c;
						}
						f[u][k][jl[1]][jl[2]][jl[3]][jl[4]] |= f[v][c][a1][a2][a3][a4];						
					}
		}
	}
}

void Print(int u,int c,int a1,int a2,int a3,int a4) {
	if (u > n) { return; }
	ansx[u] = X[u][c][a1][a2][a3][a4];
	ansy[u] = Y[u][c][a1][a2][a3][a4]; 
	ansz[u] = Z[u][c][a1][a2][a3][a4];
	int c_,a1_,a2_,a3_,a4_;
	a1_ = A1[u][c][a1][a2][a3][a4];
	a2_ = A2[u][c][a1][a2][a3][a4];
	a3_ = A3[u][c][a1][a2][a3][a4];
	a4_ = A4[u][c][a1][a2][a3][a4];
	c_ = C[u][c][a1][a2][a3][a4];
	Print(u + 1,c_,a1_,a2_,a3_,a4_);
}

void print() {
	int a1, a2, a3, a4;
	a1 = B[1][1];
	a2 = B[2][1];
	a3 = B[3][1];
	a4 = B[4][1];
	if (!f[1][0][a1][a2][a3][a4]) {
		printf("NO\n");
		exit(0);
	}
	Print(1,0,a1,a2,a3,a4);
}

int main() {
	freopen("digital.in","r",stdin);
	freopen("digital.out","w",stdout);
	dot[0].proc(1,1,1,0,1,1,1);
	dot[1].proc(0,0,0,0,0,1,1);
	dot[2].proc(0,1,1,1,1,1,0);
	dot[3].proc(0,0,1,1,1,1,1);
	dot[4].proc(1,0,0,1,0,1,1);
	dot[5].proc(1,0,1,1,1,0,1);
	dot[6].proc(1,1,1,1,1,0,1);
	dot[7].proc(0,0,1,0,0,1,1);
	dot[8].proc(1,1,1,1,1,1,1);
	dot[9].proc(1,0,1,1,1,1,1);

	scanf("%d",&n);
	for (int i = 1; i <= n; i++) scanf("%d",&A[1][i]);
	for (int i = 1; i <= n + 1; i++) scanf("%d",&B[1][i]);
	for (int i = 1; i <= n; i++) scanf("%d",&A[2][i]);
	for (int i = 1; i <= n + 1; i++) scanf("%d",&B[2][i]);
	for (int i = 1; i <= n; i++) scanf("%d",&A[3][i]);
	for (int i = 1; i <= n + 1; i++) scanf("%d",&B[3][i]);
	for (int i = 1; i <= n; i++) scanf("%d",&A[4][i]);
	for (int i = 1; i <= n + 1; i++) scanf("%d",&B[4][i]);
	for (int i = 1; i <= n; i++) scanf("%d",&A[5][i]);
	
	f[n + 1][0][0][0][0][0] = 1;

	solve();
	print();
	for (int i = 1; i <= n; i++)
		printf("%d",ansx[i]);
	putchar('\n');
	for (int i = 1; i <= n; i++)
		printf("%d",ansy[i]);
	putchar('\n');
	for (int i = 1; i <= n; i++)
		printf("%d",ansz[i]);
	
	return 0;
}
