#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, T, l, r;
LL ans;
LL dp[4010][4010];

class song_rec{
	public:
	LL t, p, f;
}song[4010];

class line{
	public:
	LL k, b;
}b[4010], p;

bool cmpf(const song_rec &A, const song_rec &B){
	return A.f < B.f;
}

LL calc(line &A, LL x){
	return A.k * x + A.b;
}

bool check(line &A, line &B, line &C){
	if (B.k == C.k)
		return C.b >= B.b;
	LL x1 = (C.b - A.b) / (A.k - C.k);
	LL x2 = (B.b - A.b) / (A.k - B.k);
	return  x1 <= x2;
}

int main(){
//	freopen("I.in", "r", stdin);
//	freopen("I.out", "w", stdout);
	
	cin >> N >> T;
	for (int i = 1; i <= N; i++)
		cin >> song[i].t >> song[i].p >> song[i].f;
	sort(song + 1, song + N + 1, cmpf);
	memset(dp, 250, sizeof(dp));
	for (int i = 1; i <= N; i++)
		dp[song[i].t][i] = song[i].p;
	ans = 0;
	for (int t = 1; t <= T; t++){
		l = 1;r = 0;
		for (int i = 1; i <= N; i++){
			ans = max(ans, dp[t][i]);
			while (l < r && calc(b[l], song[i].f) <= calc(b[l + 1], song[i].f))
				l++;
			if (l <= r && t + song[i].t <= T)
				dp[t + song[i].t][i] = max(dp[t + song[i].t][i], calc(b[l], song[i].f) + song[i].p - song[i].f * song[i].f);
			p.k = song[i].f * 2;
			p.b = dp[t][i] - song[i].f * song[i].f;
			while (l < r && check (b[r - 1], b[r], p))
				r--;
			if (!(b[r].k == p.k && b[r].b >= p.b))
				b[++r] = p;
		}
	}
	
	cout << ans << endl;
	
	return 0;
}

