#include <bits/stdc++.h>
using namespace std;

#define LL long long

int A, B, C, N;
LL ans;
class poi{
	public:
	int x, y, z;
}P[1010], p;

void work(){
	bool flag = 1;
	if (p.x < 0 || p.x >= A || p.y < 0 || p.y >= B || p.z < 0 || p.z >= C)flag = 0;
	else
		for (int j = 1; j <= N; j++)
			if (p.x == P[j].x && p.y == P[j].y && p.z == P[j].z)
				flag = 0;
	if (flag) ans ++;
}

int main(){
	scanf("%d%d%d%d", &A, &B, &C, &N);
	for (int i = 1; i <= N; i++)
		scanf("%d%d%d", &P[i].x, &P[i].y, &P[i].z);
	ans = 0;
	ans += (LL)A * B * 2 + (LL)A * C * 2 + (LL)B * C * 2;
	for (int i = 1; i <= N; i++){
		if (P[i].x == 0)ans--;
		if (P[i].x == A - 1)ans--;
		if (P[i].y == 0)ans--;
		if (P[i].y == B - 1)ans--;
		if (P[i].z == 0)ans--;
		if (P[i].z == C - 1)ans--;
	}
	
	for (int i = 1; i <= N; i++){
		p = P[i];
		p.x--;
		work();
		
		p = P[i];
		p.x++;
		work();
		
		p = P[i];
		p.y--;
		work();
		
		p = P[i];
		p.y++;
		work();
		
		p = P[i];
		p.z--;
		work();
		
		p = P[i];
		p.z++;
		work();
	}
	
	cout << ans << endl;
	
	return 0;
}

