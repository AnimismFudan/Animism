#include <bits/stdc++.h>
using namespace std;

#define LL long long

const int pp = (1e9) + 9;

int N, M, ans, len;
int f[3000010], s[3000010], H[3000010], Hrev[3000010], dp[3000010];
bool vis[3000010];

class rec{
	public:
	int a, b, c;
}PC[20];

int findset(int x){
	if (f[x] == x) return x;
	return f[x] = findset(f[x]);
}

bool cmpc(const rec &A, const rec &B){
	return A.c > B.c;
}

int quick(int x, int y){
	int s = 1, t = x;
	for (; y; y >>= 1){
		if (y & 1) s = (LL)s * t % pp;
		t = (LL)t * t % pp;
	}
	return s;
}

int C(int n, int m){
	int res = H[n];
	res = (LL)res * Hrev[m] % pp;
	res = (LL)res * Hrev[n - m] % pp;
	return res;
}

int P(int n, int m){
	int res = H[n];
	res = (LL)res * Hrev[n - m] % pp;
	return res;
}

int check(int t){
	for (int i = 0; i < M; i++)
		if (!PC[i].c || ((t >> i) & 1))
			if (findset(PC[i].a) != findset(PC[i].b)){
				s[findset(PC[i].a)] += s[findset(PC[i].b)];
				f[findset(PC[i].b)] = findset(PC[i].a);
			}
	bool bad = 0;
	int s1 = 3 * N, s2 = 0, s3 = 0;
	for (int i = 0; i < M; i++){
		if (f[PC[i].a] == PC[i].a && vis[PC[i].a]){
			if (s[PC[i].a] == 2)s2++;
			if (s[PC[i].a] == 3)s3++;
			if (s[PC[i].a] > 3)bad = 1;
			vis[PC[i].a] = 0;
		}
		if (f[PC[i].b] == PC[i].b && vis[PC[i].b]){
			if (s[PC[i].b] == 2)s2++;
			if (s[PC[i].b] == 3)s3++;
			if (s[PC[i].b] > 3)bad = 1;
			vis[PC[i].b] = 0;
		}
	}
	s1 -= s2 * 2 + s3 * 3;
	int res = 0;
	if (!bad && s1 >= s2){
		res = P(s1, s2);
		s1 -= s2;
		res = (LL)res * dp[s1] % pp;
	}
	for (int i = 0; i < M; i++){
		f[PC[i].a] = PC[i].a;
		s[PC[i].a] = 1;
		vis[PC[i].a] = 1;
		f[PC[i].b] = PC[i].b;
		s[PC[i].b] = 1;
		vis[PC[i].b] = 1;
	}
	return res;
}

int main(){
//	freopen("F.in", "r", stdin);
//	freopen("F.out", "w", stdout);
	scanf("%d%d", &N, &M);
	H[0] = 1;
	for (int i = 1; i <= 3 * N; i++)
		H[i] = (LL)H[i - 1] * i % pp;
	Hrev[3 * N] = quick(H[3 * N], pp - 2);
	for (int i = 3 * N - 1; i >= 0; i--)
		Hrev[i] = (LL)Hrev[i + 1] * (i + 1) % pp;
	dp[0] = 1;
	for (int i = 3; i <= 3 * N; i++)
		dp[i] = (LL)dp[i - 3] * C(i - 1, 2) % pp;
	len = 0;
	for (int i = 0; i < M; i++){
		scanf("%d%d%d", &PC[i].a, &PC[i].b, &PC[i].c);
		len += PC[i].c;
	}
	sort(PC, PC + M, cmpc);
	for (int i = 1; i <= 3 * N; i++){
		f[i] = i;
		s[i] = 1;
		vis[i] = 1;
	}
	for (int i = 0; i < 1 << len; i++){
		int step = 0;
		for (int j = 0; j < len; j++)
			step += (i >> j) & 1;
		if (step & 1)ans = (ans - check(i) + pp) % pp;
		else ans = (ans + check(i)) % pp;
	}
	printf("%d", ans);
}
