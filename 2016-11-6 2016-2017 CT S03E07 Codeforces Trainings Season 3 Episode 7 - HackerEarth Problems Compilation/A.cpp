#include <bits/stdc++.h>
using namespace std;

#define LL long long

char ss[400010];
int B, N, Q, last, tot;
int tooLong[400010], pos[400010], tooLongLen[400010];
int len[400010];

LL quick(LL x, LL y, LL p){
	LL s = 1, t = x;
	for (; y; y >>= 1){
		if (y & 1) s = s * t % p;
		t = t * t % p;
	}
	return s;
}

const int maxc = 26;
class trienode {
  public:
	int go[maxc];
	int acc, w, fa;
	void clr() {
		memset (go, 0, sizeof (go) );
		w = acc = fa = 0;
	}
};

class trie {
  public:
	int root, size;
	trienode a[400010];
	void pre() {
		root = size = 1;
		a[1].clr();
	}
	int init (int last, int x) {
		if (!a[last].go[x]) {
			a[last].go[x] = ++size;
			a[size].clr();
			a[size].w = x;
			a[size].fa = last;
		}
		return a[last].go[x];
	}
} Trie;

const int c_step = 2;

const LL p1[c_step] = {100, 127};
const LL p2[c_step] = {100000007, 299999977};

class Hhash{
	public:
	LL a[2];
	LL high[2];
	void add(int w){
		for (int t = 0; t < c_step; t++)
			a[t] = (a[t] * p1[t] + w) % p2[t];
	}
	void erasePre(int ll){
		for (int t = 0; t < c_step; t++)
			high[t] = quick(p1[t], ll, p2[t]);
	}
	void clear(){
		for (int t = 0; t < c_step; t++)
			a[t] = 0;
	}
	void erase(int w){
		for (int t = 0; t < c_step; t++){
			a[t] = (a[t] - high[t] * w % p2[t]) % p2[t];
			a[t] = (a[t] + p2[t]) % p2[t];
		}
	}
	bool operator == (const Hhash &X)const{
		for (int t = 0; t < c_step; t++)
			if (a[t] != X.a[t])
				return 0;
		return 1;
	}
}HH, Hash[400010];

bool check(){
	int r = strlen(ss);
	for (int i = 0; i < r; i++)
		ss[i] = (ss[i] - 'a' + last) % 26 + 'a';
	for (int i = 0; i < r; i++){
		int x = Trie.root;
		for (int j = 0; j < B && i + j < r; j++){
			x = Trie.a[x].go[ss[i + j] - 'a'];
			if (Trie.a[x].acc){
				printf("YES\n");
				return 1;
			}
		}
	}
	for (int i = 0; i < tot; i++){
		HH.clear();
		HH.erasePre(tooLongLen[i]);
		for (int j = 0; j < r; j++){
			HH.add(ss[j] - 'a');
			if (j >= tooLongLen[i])
				HH.erase(ss[j - tooLongLen[i]] - 'a');
			if (j + 1 >= tooLongLen[i] && HH == Hash[i]){
				printf("YES\n");
				return 1;
			}	
		}
	}
	printf("NO\n");
	return 0;
}

void setTooLong(int x){
	tooLong[x] = tot;
	for (int j = 0; j < len[x]; j++){
		Hash[tot].add(ss[j] - 'a');
		tooLongLen[tot] = len[x];
	}
	++tot;
}

void beTooLong(int x){
	int y = pos[x];
	int r = 0;
	for (; y != 1; y = Trie.a[y].fa)
		ss[r++] = Trie.a[y].w + 'a';
	for (int ll = 0, rr = r - 1; ll < rr; ll++, rr--)
		swap(ss[ll], ss[rr]);
	setTooLong(x);
}

int main(){
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
	B = sqrt(400000);
//	B = 1;
	scanf("%d%d", &N, &Q);
	Trie.pre();
	for (int i = 0; i < N; i++){
		scanf("%s", ss);
		len[i] = strlen(ss);
		if (len[i] > B)setTooLong(i);
		else{
			tooLong[i] = -1;
			int x = Trie.root;
			for (int j = 0; j < len[i]; j++)
				x = Trie.init(x, ss[j] - 'a');
			Trie.a[x].acc ++;
			pos[i] = x;
		}
	}
	last = 0;
	int num = 0;
	for (int i = 0; i < Q; i++){
		int t;
		scanf("%d", &t);
		if (t == 1){
			++num;
			scanf("%s", ss);
			if (check())
				last = i;
		}else{
			int x, c;
			scanf("%d%d", &x, &c);
			x = (x + last) % N;
			c = (c + last) % 26;
			if (tooLong[x] != -1){
				len[x]++;
				int y = tooLong[x];
				Hash[y].add(c);
				tooLongLen[y]++;
			}else{
				len[x]++;
				int y = pos[x];
				Trie.a[y].acc--;
				y = Trie.init(y, c);
				Trie.a[y].acc++;
				pos[x] = y;
				if (len[x] >= B){
					Trie.a[y].acc--;
					beTooLong(x);
				}
			}
		}
	}
}