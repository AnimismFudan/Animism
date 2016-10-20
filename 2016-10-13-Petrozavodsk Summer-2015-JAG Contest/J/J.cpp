#include <bits/stdc++.h>
using namespace std;

int N, C, len;
int b[100010];
class poi{
	public:
	int x, y;
}P[100010];

bool cmpx(const poi &A, const poi &B){
	if (A.x != B.x)return A.x < B.x;
	return A.y < B.y;
}

int main(){
	scanf("%d%d", &N, &C);
	for (int i = 1; i <= N; i++)
		scanf("%d%d", &P[i].x, &P[i].y);
	sort(P + 1, P + N + 1, cmpx);
	for (int i = 1; i < N; i++)
		if (abs(P[i].x - P[i + 1].x) > C){
			N = i;
			break;
		}
	b[len = 1] = 1;
	for (int i = 2; i <= N; i++)
		if (P[i].y < P[b[len]].y)
			b[++len] = i;
	printf("%d\n", len);
}
