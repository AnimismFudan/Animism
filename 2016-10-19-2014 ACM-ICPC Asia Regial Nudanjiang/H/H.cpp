#include <bits/stdc++.h>
using namespace std;
#define LL long long

const int p1 = 127;
const int p2 = (1e7) + 19;

int Test, Q, len, root, tot, pt;
int mark[11000010];
char s[11000010], ss[11000010];
int sta[100010];
int tl[100010], tr[100010];
int st[p2], vis[p2], ne[100010], go[100010], wx[100010], wl[100010], wr[100010];

void Add(int x, int y, int xx, int xl, int xr){
	if (vis[x] != Test){
		st[x] = 0;
		vis[x] = Test;
	}
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
	wx[pt] = xx;
	wl[pt] = xl;
	wr[pt] = xr;
}

int gethash(char *s, int x, int l, int r){
	LL h = 0;
	for (int i = l; i <= r; i++){
		h = (h * p1 + s[i]);
		if (h > 1e15) h %= p2;
	}
	h = (h % p2 * 10007 + x) % p2;
	return h;
}

void pre(){
	for (int i = 0; i < len; i++)
		mark[i] = -1;
	int r = 0;
	for (int i = 0; i < len; i++)
		if (s[i] == '{')sta[++r] = i;
		else if (s[i] == '}'){
			mark[i] = sta[r];
			mark[sta[r]] = i;
			sta[r--] = 0;
		}else if (s[i] == '"'){
			int j = i + 1;
			for (; s[j] != '"'; j++);
			mark[i] = j;
			mark[j] = i;
			i = j;
		}
}

int build(int l, int r){
	int x = ++tot;
	tl[x] = l;
	tr[x] = r;
	if (s[l] == '"')
		return x;
	for (int i = l + 1; i <= r; i++){
		int h1 = gethash(s, x, i + 1, mark[i] - 1);
		int j = mark[i] + 2;
		int y = build(j, mark[j]);
		Add(h1, y, x, i + 1, mark[i] - 1);
		i = mark[j] + 1;
	}
	return x;
}

int main(){
	freopen("H.in", "r", stdin);
	freopen("H.out", "w", stdout);
	scanf("%d", &Test);
	for (int i = 0; i < p2; i++)
		vis[i] = Test;
	while (Test--){
		scanf("%s", s);
		len = strlen(s);
		tot = 0;
		pt = 0;
		pre();
		root = build(0, len - 1);
		scanf("%d", &Q);
		for (;Q--;){
			scanf("%s", ss);
			len = strlen(ss);
			int x = root;
			bool flag = 0;
			for (int i = 0; i < len; i++){
				int j = i + 1;
				for (; ss[j] != '"'; j++);
				int h1 = gethash(ss, x, i + 1, j - 1);
				flag = 1;
				for (int k = st[h1]; k; k = ne[k])
					if (wx[k] == x){
						flag = 0;
						x = go[k];
						break;
					}
				if (flag)break;
				i = j + 1;
			}
			if (flag)printf("Error!\n");
			else{
				for (int i = tl[x]; i <= tr[x]; i++)
					putchar(s[i]);
				printf("\n");
			}
		}
	}
	return 0;
}
