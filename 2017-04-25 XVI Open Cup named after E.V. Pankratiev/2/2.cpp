#include <bits/stdc++.h>
using namespace std;

map <string,int> st;
int n;
string ts[1010];

int main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d\n",&n);
	for (int i = 1; i <= n; i++) {
		string s = "";
		cin >> s;
		string t = "";
		for (int i = (int) s.length() - 1; s[i] != '.'; i--)
			t = s[i] + t;
		if (!st[t]) ts[i] = t;
		st[t]++;		
	}

	for (int i = 1; i <= n; i++)
		if (ts[i] != "")
			cout << ts[i] << ": " << st[ts[i]] << endl;
	return 0;
}
