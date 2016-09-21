#include <bits/stdc++.h>
using namespace std;

int N, S;
int f1[50010], f2[50010], f3[50010];
class rec{
	public:
	int c, w;
}P[1010];

bool cmpc(const rec &A, const rec &B){
	return A.c < B.c;
}

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	
	scanf("%d%d",&N, &S);
	for (int i = 1; i <= N; i++)
		scanf("%d%d", &P[i].c, &P[i].w);
	sort(P + 1, P + N + 1, cmpc);
	memset(f1, 255, sizeof(f1));
	f1[0] = 0;
	
	for (int i = 1; i <= N; i++){
		for (int j = 0; j <= S; j++)
			f3[j] = f2[j] = f1[j];
		int k = i;
		for (; P[k].c == P[i].c; k++){
			for (int j = 0; j + P[k].w <= S; j++){
				if (f1[j] != -1)
					f3[j + P[k].w] = max(f3[j + P[k].w], f1[j] + 1);
				if (f2[j] != -1)
					f3[j + P[k].w] = max(f3[j + P[k].w], f2[j]);
			}
			for (int j = 0; j <= S; j++)
				f2[j] = f3[j];
		}
		for (int j = 0; j <= S; j++)
			f1[j] = f2[j];
		i = k - 1;
	}
	if (f1[S] == -1)printf("Impossible\n");
	else printf("%d\n", f1[S]);
	
	return 0;
}

