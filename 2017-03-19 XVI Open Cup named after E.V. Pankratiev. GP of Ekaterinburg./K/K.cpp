#include <bits/stdc++.h>
using namespace std;

char Cons[7] = "Value:";
int len, N, M, tot;
char s[1000100];
int SL[1000100];
bool ans_have[1000100];
string ans[1000100], out[1000100], sl;

class rec{
	public:
	int x;
	string s;
}p;

bool operator < (const rec &A, const rec &B){
	if (A.x != B.x) return A.x < B.x;
	return A.s < B.s;
}

map <rec, int > go;
map <rec, int > :: iterator cp;

inline char readchar(){
	char ch = getchar();
	while (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t')
		ch = getchar();
	return ch;
}

void ReadS(){
	int len = 0;
	char ch = getchar();
	while (ch != '"'){
		s[len++] = ch;
		ch = getchar();
	}
	s[len] = 0;
}

bool Readline(char* s){
	char ch = -1;
	ch = readchar();
	int len = 0;
	while (ch != -1 && ch != '\n' && ch != '\r'){
		s[len++] = ch;
		ch = -1;
		ch = getchar();
	}
	if (!len && ch == -1) return 0;
	return 1;
}

void work(int x){
	char ch;
	ch = readchar();
	if (ch == '"'){
		ReadS();
		ans_have[x] = 1;
		ans[x] = s;
	}
	else{
		ch = readchar();
		while (ch != '}'){
			while (ch == ',') ch = readchar();
			ReadS();
			ch = readchar();
			int y = ++tot;
			p.x = x;
			p.s = s;
			go[p] = y;
			work(y);
			ch = readchar();
		}
	}
}

bool check(int num, int l, int r){
	p.x = 1;
//	while (s[l] == ' ') l++;
	while (l <= r){
		int rr = l;
		while (rr <= r && s[rr] != '.') rr++;
		p.s = "";
		for (int k = l; k < rr; k++) p.s = p.s + s[k];
		cp = go.find(p);
		if (cp == go.end())
			return 0;
		p.x = (cp -> second);
		l = rr + 1;
//		while (s[l] == ' ') l++;
	}
	if (ans_have[p.x]){
		out[num] = ans[p.x];
		return 1;
	}
	else return 0;
}

void Deal(int num, int l, int r){
	int ll = l;
	while (s[ll] == ' ' && ll <= r)
		ll++;
	if (r - ll + 1 >= 6){
		bool flag = 1;
		for (int k = 0; k < 6; k++)
			if (s[ll + k] != Cons[k])
				flag = 0;
		int rr = r;
		while (s[rr] == ' ') rr--;
		if (flag && check(num, ll + 6, rr)) return;
	}
	out[num] = "";
	for (int k = l; k <= r; k++)
		out[num] = out[num] + s[k];
}

int main() {
	//freopen("K.in","r",stdin);
	//freopen("K.out","w",stdout);
	work(++tot);
	Readline(s);
	len = strlen(s);
	N = 0;
	for (int i = 0; i < len; i++)
		if (s[i] == '+')
			M++;
	M--;
	while (Readline(s)){
		++N;
		int l, r;
		l = 0;
		for (int i = 1; i <= M; i++){
			r = l + 1;
			while (s[r] != '|') r++;
			Deal((N - 1) * M + i, l + 1, r - 1);
			l = r;
		}
		Readline(s);
	}
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++){
			int ll = out[(i - 1) * M + j].length();
			SL[j] = max(SL[j], ll);
		}
	sl = "+";
	for (int j = 1; j <= M; j++){
		for (int i = 1; i <= SL[j]; i++)
			sl = sl + '-';
		sl = sl + '+';
	}
	cout << sl << endl;
	for (int i = 1; i <= N; i++){
		printf("|");
		for (int j = 1; j <= M; j++){
			int t = (i - 1) * M + j;
			cout << out[t];
			for (int k = out[t].length(); k < SL[j]; k++)
				printf(" ");
			printf("|");
		}
		printf("\n");
		cout << sl << endl;
	}
	return 0;
}
