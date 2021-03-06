#include <bits/stdc++.h>
#define intl long long
using namespace std;

int N, k;

class rec{
	public:
	char c;
	int t;
	double ans;
}P[100010];

class mat{
	public:
	double a[3][3];
	void Z(){
		memset(a, 0, sizeof(a));
	}
	void E(){
		Z();
		a[0][0] = a[1][1] = a[2][2] = 1;
	}
}A, B;

mat operator *(const mat &A, const mat &B){
	mat C;
	C.Z();
	for (int k = 0; k < 3; k++)
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				C.a[i][j] += A.a[i][k] * B.a[k][j];
	return C;
}

int main() {
	freopen("L.in","r",stdin);
	freopen("L.out","w",stdout);
	scanf("%d\n", &N);
	N <<= 1;
	for (int i = 1; i <= N; i++)
		scanf("%c%d\n", &P[i].c, &P[i].t);
	B.E();
	k = 0;
	for (int i = N; i >= 1; i--)
		if (P[i].c == '+'){
			A.Z();
			A.a[0][0] = 1;
			A.a[0][1] = P[i].t;
			A.a[0][2] = 0;
			A = A * B;
			P[i].ans = A.a[0][2];
			k--;
		}else{
			A.Z();
			k++;
			A.a[0][0] = double (k - 1) / k;
			A.a[1][1] = double (k - 1) / k;
			A.a[0][2] = double (P[i].t) / k;
			A.a[1][2] = -1.0 / k;
			A.a[2][2] = 1;
			B = A * B;
		}
	for (int i = 1; i <= N; i++)
		if (P[i].c == '+')
			printf("%.10lf\n", P[i].ans);
	return 0;
}
