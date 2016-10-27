#include <bits/stdc++.h>
using namespace std;

int N, ans;

class rec{
	public:
	int x, d, t;
	rec operator + (int X)const{
		rec c;
		c.x = x + X;
		c.d = d;
		c.t = t;
		return c;
	}
}P[110];

int sign(int x){
	if (x > 0)return 1;
	if (x < 0)return -1;
	return 0;
}

bool big(rec A, rec B){
	if (A.x != B.x)
		return A.x > B.x;
	return A.t < B.t;
}

bool cmpdx(const rec &A, const rec &B){
	if (sign(A.d) != sign(B.d))
		return sign(A.d) < sign(B.d);
	if (sign(A.d) < 0)
		return big(A, B);
	else return !big(A, B);
}

int main(){
	scanf("%d", &N);
	for (int i = 1; i <= N; i ++){
		scanf("%d %d", &P[i].x, &P[i].d);
		P[i].t = i;
	}
	sort(P + 1, P + N + 1, cmpdx);
	ans = 0;
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++)
			if (i != j)
				if ((big(P[j], P[i]) && !big(P[j], P[i] + P[i].d)) || 
					(!big(P[j], P[i]) && big(P[j], P[i] + P[i].d)))
						ans++;
		P[i].x += P[i].d;
	}	
	printf("%d\n", ans);
	return 0;
}

