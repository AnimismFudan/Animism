#include <bits/stdc++.h>
using namespace std;

const int p2 = 10000019;
int Test, N, pt, l, r;
int q[2000010], pre[2000010];
int ne[2000010], go[2000010], w[2000010], from[2000010];
int hst[p2], hne[2000010];
char s[1000010];

void Init(int &st, int x, int ww, int y){
	ne[++pt] = st;
	st = pt;
	go[pt] = y;
	w[pt] = ww;
	from[pt] = x;
	int H = (x * 26 + ww) % p2;
	hne[pt] = hst[H];
	hst[H] = pt;
}

int find(int x, int ww){
	int H = (x * 26 + ww) % p2;
	for (int i = hst[H]; i; i = hne[i])
		if (w[i] == ww && from[i] == x)
			return i;
	return 0;
}

const int maxc = 26;
class ACAnode {
  public:
	int fail, acc, st, l;
	void clr() {
		st = 0;
		fail = acc = 0;
	}
};

class ACA {
  public:
	int root, size;
	ACAnode a[1000010];
	
	void pre() {
		root = size = 1;
		a[1].clr();
	}
	
	int init (int last, int x) {
		if (!find(last, x)) {
			Init(a[last]. st, last, x, ++size);
			a[size].clr();
			a[size].l = a[last].l + 1;
		}
		return go[find(last, x)];
	}
	
	void build() {
		q[l = r = 1] = root;
		a[root].fail = root;
		for (; l <= r; l++) {
			int x = q[l];
			for (int j = a[x].st; j; j = ne[j]){
				int c = w[j];
				int y = go[j];
				int last = a[x].fail;
				while (last != root && !find(last, c))
					last = a[last].fail;
				int t = find(last, c);
				if (t && go[t] != y)
					a[y].fail = go[t];
				else a[y].fail = root;
				if (a[a[y].fail].acc)
					a[y].acc = max(a[y].acc, a[a[y].fail].acc);
				q[++r] = y;
			}
		}
	}
} aca;

void readin(char *s){
	char ch = getchar();
	int r = 0;
	while (ch != '\n' && ch != '\r'){
		s[r++] = ch;
		ch = getchar();
	}
	s[r] = 0;
}

int main(){
	freopen("1003.in", "r", stdin);
	freopen("1003.out", "w", stdout);
	scanf("%d",&Test);
	while (Test--){
		scanf("%d\n", &N);
		pt = 0;
		memset(hst, 0, sizeof(hst));
		aca.pre();
		int x, len;
		for (int i = 0; i < N; i++){
			readin(s);
			len = strlen(s);
			x = aca.root;
			for (int j = 0; j < len; j++)
				x = aca.init(x, s[j] - 'a');
			aca.a[x].acc = len;
		}
		aca.build();
		readin(s);
		len = strlen(s);
		x = aca.root;
		for (int i = 0; i < len; i++){
			int cc = s[i] - 'a';
			if (s[i] >= 'A' && s[i] <= 'Z')cc = s[i] - 'A';
			else if (s[i] < 'a' || s[i] > 'z'){
				cc = -1;
				x = aca.root;
				continue;
			}
			int t = find(x, cc);
			while (x != aca.root && !t){
				x = aca.a[x].fail;
				t = find(x, s[i] - 'a');
			}
			pre[i] = 0;
			if (t){
				x = go[t];
				if (aca.a[x].acc)
					pre[i] = aca.a[x].acc;
			}
		}
		int t = 0;
		for (int i = len - 1; i >= 0; i--){
			t = max(t, pre[i]);
			if (t) s[i] = '*';
			t--;
		}
		printf("%s\n", s);
	}
}