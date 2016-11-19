#include <bits/stdc++.h>
using namespace std;

#define LL long long

LL ans;
int N;
int SUM[2];
int Pre[200010], Pres[200010];

class poi{
	public:
	int x, y;
}P[200010], L;

int xet2(poi A, poi B){
	int res = A.x * B.y - B.x * A.y;
	res = (res + 2) & 1;
	return res;
}

int main(){
	freopen("integral.in", "r", stdin);
	freopen("integral.out", "w", stdout);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++){
		scanf("%d%d", &P[i].x, &P[i].y);
		P[i].x &= 1;
		P[i].y &= 1;
	}
	ans = 0;
	Pre[1] = 0;
	for (int j = 2; j <= N; j++)
		Pre[j] = Pre[j - 1] ^ xet2(P[j - 1], P[j]);
	bool flag = Pre[N] ^ xet2(P[1], P[N]);
	if (flag){
		printf("0\n");
		return 0;
	}
	for (int i = 0; i < 4; i++){
		L.x = i >> 1;
		L.y = i & 1;
		for (int j = 1; j <= N; j++)
			Pres[j] = Pre[j] ^ xet2(L, P[j]);
		SUM[0] = SUM[1] = 0;
		for (int j = N; j > 0; j--){
			if (P[j].x == L.x && P[j].y == L.y)
				ans += SUM[Pre[j]];
			SUM[Pres[j]]++;
		}
	}
	ans -= N;
	cout << ans << endl;
	return 0;
}

