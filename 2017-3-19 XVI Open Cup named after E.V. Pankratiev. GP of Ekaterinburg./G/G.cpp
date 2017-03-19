#include <bits/stdc++.h>
using namespace std;

string s;

int main() {
	//freopen("G.in","r",stdin);
	//freopen("G.out","w",stdout);
	getline(cin, s);
	if (s == "I am Groot") cout << "Pfff" << endl;
	else {
		int cnt = 0;
		for (int i = s.length() - 1; i >= 0; i--) if (s[i] == '!') cnt++;
		cout << "W";
		for (int i = 1; i <= cnt; i++) putchar('o');
		cout << "w" << endl;
	}
	return 0;
}
