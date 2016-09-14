#include <bits/stdc++.h>
using namespace std;

#define LL long long

bool cmpxs(const line &A, const line &B){
	if (A.x == B.x)
		return A.x < B.x;
	return A.selta < B.selta;
}

int main(){
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
	
	scanf("%d%d", &N, &Q);
	for (int i = 1; i <= N; i++)
		scanf("%d%d", &P[i].x, &P[i].y);
	for (int i = 1; i <= M; i++){
		scanf("%d%d", &L[i].x, &L[i].y);
		L[M + i] = L[i];
		swap(L[i].x, L[i].y);
		L[i].n = i;
	}
	M <<= 1;
	for (int i = 0; i < M; i++)L[i] = L[i + 1];
	for (int i = 0; i < M; i++)
		L[i].selta = atan2(P[L[i].y].y - P[L[i].x].y, P[L[i].y].x - P[L[i].x].x);
	sort(L, L + M, cmpxs);
	for (int i = 0; i < M; i++){
		Add(L[i].x, L[i].y);
		L[i].pos = pt;
		num[pt] = L[i].n;
	}
	for (int i = 0; i < M; i++)L[i].rev = L[i ^ 1].pos;
	for (int i = 0; i < M; i++)
		if (!vis[i]){
			++ tot;
			int x = i;
			LL area = 0;
			for (; !vis[x]; ){
				vis[x] = tot;
				area += xet(P[L[x].x], P[L[x].y]);
				if (ne[L[x].rev])
					x = ne[L[x].rev];
				else	x = st[L[x].y];
			}
			if (area < 0)
				bound[tot] = 1;
		}
	len = 0;
	for (int i = 0; i < M; i++)
		if (bound[vis[i]]){
			++len;
			q[len].t = 0;
			q[len].x = 
		}
		
	return 0;
}

