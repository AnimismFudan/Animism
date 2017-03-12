#include <bits/stdc++.h>
using namespace std;

string A[11];

string Ans[10];
char s[10][200];
int a, b, ans;
int n, mark;

void prepare() {
	A[0] = "xxxxxx...xx...xx...xx...xx...xxxxxx";
	A[1] = "....x....x....x....x....x....x....x";
	A[2] = "xxxxx....x....xxxxxxx....x....xxxxx";
	A[3] = "xxxxx....x....xxxxxx....x....xxxxxx";
	A[4] = "x...xx...xx...xxxxxx....x....x....x";
	A[5] = "xxxxxx....x....xxxxx....x....xxxxxx";
	A[6] = "xxxxxx....x....xxxxxx...xx...xxxxxx";
	A[7] = "xxxxx....x....x....x....x....x....x";
	A[8] = "xxxxxx...xx...xxxxxxx...xx...xxxxxx";
	A[9] = "xxxxxx...xx...xxxxxx....x....xxxxxx";
	A[10] =".......x....x..xxxxx..x....x......."; 
}

int judge(int t) {
	string js = "";
	for (int i = 1; i <= 7; i++)
		for (int j = 0; j < 5; j++)
			js += s[i][j + t];
	for (int i = 0; i <= 10; i++)
		if (js == A[i]) return i;
	return -1;
}

void print(int ans) {
	if (ans > 9) {
		print(ans / 10);
		for (int i = 1; i <= 7; i++)
			Ans[i] += '.';
	}
	int v = ans % 10;
	for (int i = 1; i <= 7; i++)
		for (int j = 0; j < 5; j++)
			Ans[i] += A[v][(i - 1) * 5 + j];
	return;
}

int main() {
	//freopen("A.in","r",stdin);
	//freopen("A.out","w",stdout);
	for (int i = 1; i <= 7; i++)
		scanf("%s",s[i] + 1);
	n = strlen(s[1] + 1);
	prepare();
	for (int t = 1; t <= n; t += 6) {
		int v;
		if ((v = judge(t)) == 10) { mark = 1; continue; }
		else if (!mark) a = a * 10 + v;
		else b = b * 10 + v;
	}
	ans = a + b;
	print(ans);
	for (int i = 1; i <= 7; i++) cout << Ans[i] << endl;
	return 0;
}
