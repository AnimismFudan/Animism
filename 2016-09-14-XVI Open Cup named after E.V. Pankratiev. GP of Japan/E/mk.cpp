#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, M, Q;
class poi{
	public:
	int x, y;
	bool operator < (const poi &X)const{
		if (x != X.x)return x < X.x;
		return y < X.y;
	}
	bool operator == (const poi &X)const{
		return (x == X.x) && (y == X.y);
	}
}P[1010], L[1010], q[1010];

int main(){
	srand(time(0));
	freopen("E.in", "w", stdout);
	N = rand() % 5 + 2;
	for (int i = 1; i <= N; i++){
		P[i].x = rand() % 10;
		P[i].y = rand() % 10;
	}
	int l = N;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++){
			++l;
			P[l].x = P[i].x;
			P[l].y = P[j].y;
			++l;
			P[l].x = P[j].x;
			P[l].y = P[i].y;
		}
	N = l;
	sort(P + 1, P + N + 1);
	N = unique(P + 1, P + N + 1) - P - 1;
	for (int i = 1; i <= N; i++){
		int t;
		t = 0;
		for (int j = 1; j <= N; j++)
			if (P[j].x == P[i].x && P[j].y < P[i].y)
				if (!t || P[t].y < P[j].y)
					t = j;
		if (t > i){
			++M;L[M].x = i;L[M].y = t;
		}
		
		t = 0;
		for (int j = 1; j <= N; j++)
			if (P[j].x == P[i].x && P[j].y > P[i].y)
				if (!t || P[t].y > P[j].y)
					t = j;
		if (t > i){
			++M;L[M].x = i;L[M].y = t;
		}
		
		t = 0;
		for (int j = 1; j <= N; j++)
			if (P[j].y == P[i].y && P[j].x < P[i].x)
				if (!t || P[t].x < P[j].x)
					t = j;
		if (t > i){
			++M;L[M].x = i;L[M].y = t;
		}
		
		t = 0;
		for (int j = 1; j <= N; j++)
			if (P[j].y == P[i].y && P[j].x > P[i].x)
				if (!t || P[t].x > P[j].x)
					t = j;
		if (t > i){
			++M;L[M].x = i;L[M].y = t;
		}
	}
	for (int i = 1; i <= M; i++)
		if (rand()%10 == 0){
			swap(L[i], L[M]);
			M--;
		}
	Q = rand() % 5 + 1;
	for (int i = 1; i <= Q; i++){
		bool flag = 1;
		do{
			flag = 0;
			q[i].x = rand()%10;
			q[i].y = rand()%10;
			for (int j = 1; j <= M; j++)
				if (min(P[L[j].x].x, P[L[j].y].x) <= q[i].x)
					if (q[i].x <= max(P[L[j].x].x, P[L[j].y].x))
						if (min(P[L[j].x].y, P[L[j].y].y) <= q[i].y)
							if (q[i].y <= max(P[L[j].x].y, P[L[j].y].y))
								flag = 1;
		}while (flag);
	}
	printf("%d %d %d\n", N, M, Q);
	for (int i = 1; i <= N; i++)
		printf("%d %d\n", P[i].x, P[i].y);
	for (int i = 1; i <= M; i++)
		printf("%d %d\n", L[i].x, L[i].y);
	for (int i = 1; i <= Q; i++)
		printf("%d %d\n", q[i].x, q[i].y);
	return 0;
}

