#include <bits/stdc++.h>
using namespace std;

int N, K, M;
int W[10010], Score[10010], Head[1030];

vector <int > V[1030];

class rec{
	public:
	int Have, DHave, x, t, Score, n, ans;
} Q[100010];

bool cmpd(const int &A, const int &B){
	return A > B;
}

bool cmp(const rec &A, const rec &B){
	return A.Score > B.Score;
}

bool cmpn(const rec &A, const rec &B){
	return A.n < B.n;
}

int main(){
//	freopen("A.in", "r", stdin);
//	freopen("A.out", "w", stdout);
	scanf("%d%d\n", &N, &K);
	for (int i = 1; i <= N; i++){
		int x, t;
		scanf("%d%d", &Score[i], &t);
		x = 0;
		for (int j = 0; j < t; j++){
			int y;
			scanf("%d", &y);
			x |= 1 << (y - 1);
		}
		W[i] = x;
		V[x].push_back(Score[i]);
	}
	for (int i = 0; i < 1 << K; i++){
		sort(V[i].begin(), V[i].end(), cmpd);
		Head[i] = 0;
	}
	scanf("%d", &M);
	for (int i = 1; i <= M; i++){
		Q[i].Have = Q[i].DHave = 0;
		scanf("%d%d", &Q[i].x, &Q[i].t);
		for (int j = 0; j < Q[i].t; j++){
			int y;
			scanf("%d", &y);
			if ((W[Q[i].x] >> (y - 1)) & 1)
				Q[i].Have |= 1 << (y - 1);
			else Q[i].DHave |= 1 << (y - 1);
		}
		Q[i].Score = Score[Q[i].x];
		Q[i].n = i;
	}
	sort(Q + 1, Q + M + 1, cmp);
	for (int i = 1; i <= M; i++){
		Q[i].ans = 1;
		for (int j = 0; j < 1 << K; j++)
			if (((j & Q[i].Have) == Q[i].Have) && ((j & Q[i].DHave) == 0)){
				while (Head[j] < V[j].size() && V[j][Head[j]] > Q[i].Score)
					Head[j]++;
				Q[i].ans += Head[j];
			}
	}
	sort(Q + 1, Q + M + 1, cmpn);
	for (int i = 1; i <= M; i++)
		printf("%d\n", Q[i].ans);
	return 0;
}
