#include <bits/stdc++.h>
using namespace std;

int N, ansn;

class bir{
	public:
	int d, m, y;
	bool operator < (const bir &X) const{
		if (y < X.y)return 1;
		if (y > X.y)return 0;
		if (m < X.m)return 1;
		if (m > X.m)return 0;
		if (d < X.d)return 1;
		if (d > X.d)return 0;
		return 0;
	}
}P, Q, ans;

bool check(bir A, bir B){
	A.y -= 18;
	return !(A < B);
}

int main(){
	freopen("king.in", "r", stdin);
	freopen("king.out", "w", stdout);
	scanf("%d%d%d", &P.d, &P.m, &P.y);
	scanf("%d", &N);
	ans.d = 1;
	ans.m = 1;
	ans.y = -1000;
	ansn = -1;
	for (int i = 1; i <= N; i++){
		scanf("%d%d%d", &Q.d, &Q.m, &Q.y);
		if (check(P, Q) && ans < Q){
			ans = Q;
			ansn = i;
		}
	}
	if (ansn != -1)printf("%d\n", ansn);
	else printf("-1\n");
	
	return 0;
}

