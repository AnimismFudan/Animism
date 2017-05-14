#include <bits/stdc++.h>

using namespace std;

int N, L, Q, res;
int lis[30], f[210];
char ss[210], s[210][210];

int findset(int x){
	if (f[x] == x) return f[x];
	return f[x] = findset(f[x]);
}

int ctoi(char ch){
	return ch - 'A';
}

int main(){
	freopen("git-hashes.in", "r", stdin);
	freopen("git-hashes.out", "w", stdout);
	scanf("%d%d", &N, &L);
	for (int i = 0; i < N; i++)
		scanf("%s", s[i]);
	scanf("%d", &Q);
	while (Q--){
		scanf("%s", ss);
		for (int i = 0; i < L; i++)
			f[i] = i;
		for (int i = 0; i < N; i++)
			if (ss[i] == '1'){
				memset(lis, 255, sizeof(lis));
				for (int j = 0; j < L; j++)
					if (lis[ctoi(s[i][j])] == -1)
						lis[ctoi(s[i][j])] = j;
					else
						f[findset(j)] = findset(lis[ctoi(s[i][j])]);
			}
		res = 0;
		for (int i = 0; i < L; i++)
			if (f[i] == i)
				res += 4;
		printf("1*2^%d\n", res);
	}
}
