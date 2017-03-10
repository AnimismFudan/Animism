#include <bits/stdc++.h>
using namespace std;

#define LL long long

const int upn = 782;

int N, ans;
int px[100010], py[100010];
char s[50010][6];

class exBitset{
	public:
	LL a[upn];
	void set(int x){
		int tx = x / 64;
		int ty = x - tx * 64;
		a[tx] |= 1ll << ty;
	}
	void clr(int x){
		int tx = x / 64;
		int ty = x - tx * 64;
		a[tx] |= 1ll << ty;
		a[tx] ^= 1ll << ty;
	}
	void aaa(const exBitset &A){
		for (int i = 0; i < upn; i++)
			a[i] &= A.a[i];
	}
}ss, B[5][75];

int main(){
//	freopen("A.in", "r", stdin);
//	freopen("A.out", "w", stdout);
	scanf("%d", &N);
	for (int i = 0; i < N; i++){
		scanf("%s", s[i]);
		for (int j = 0; j < 5; j++)
			for (int k = 48; k <= 122; k++)
				if (k != s[i][j])
					B[j][k - 48].set(i);
	}
	ans = 0;
	for (int i = 0; i < N && ans < 100000; i++){
		ss = B[0][s[i][0] - 48];
		for (int j = 1; j < 5; j++)
			ss.aaa(B[j][s[i][j] - 48]);
		for (int j = 0; j < upn && ans < 100000; j++)
			if (ss.a[j])
				for (int k = 0; k < 64; k++)
					if ((ss.a[j] >> k) & 1){
						++ans;
						px[ans] = i;
						py[ans] = j * 64 + k;
						if (ans >= 100000) break;
					}
		for (int j = 0; j < 5; j++)
			for (int k = 48; k <= 122; k++)
				if (k != s[i][j])
					B[j][k - 48].clr(i);
	}
	printf("%d\n", ans);
	for (int i = 1; i <= ans; i++)
		printf("%d %d\n", px[i] + 1, py[i] + 1);
	return 0;
}

