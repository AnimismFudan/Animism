#include <bits/stdc++.h>
using namespace std;
#define LL long long

char s[5][5];

bool check(){
	bool flag = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (s[i][j] != 'x')
				flag = 1;
	return flag;
}

void Writeln(){
	for (int i = 0; i < 3; i++)
		cout << s[i] << endl;
	fflush(stdout);
}

void Readln(){
	for (int i = 0; i < 3; i++)
		scanf("%s", s[i]);
}

bool ok(){
	bool flag;
	for (int i = 0; i < 3; i++){
		flag = 1;
		for (int j = 0; j < 3; j++){
			if (s[i][j] != 'x')
				flag = 0;
		}
		if (flag)return 1;
	}
	for (int j = 0; j < 3; j++){
		flag = 1;
		for (int i = 0; i < 3; i++){
			if (s[i][j] != 'x')
				flag = 0;
		}
		if (flag)return 1;
	}
	flag = 1;
	for (int i = 0; i < 3; i++){
		if (s[i][i] != 'x')
			flag = 0;
	}
	if (flag)return 1;
	flag = 1;
	for (int i = 0; i < 3; i++){
		if (s[2 - i][i] != 'x')
			flag = 0;
	}
	if (flag)return 1;
//	return sum >= 2;
	return 0;
}

bool Win(){
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (s[i][j] == '.'){
				s[i][j] = 'x';
				if (ok())
					return 1;
				s[i][j] = '.';
			}
	return 0;
}

int main(){
	Readln();
	while (check()){
		bool flag = 1;
		if (Win()){
			Writeln();
			flag = 0;
		}
		if (flag && s[0][0] == '.'){
			s[0][0] = 'x';
			Writeln();
			flag = 0;
		}
		if (flag && s[1][0] == '.' && s[2][0] != 'o'){
			if (s[2][0] == 'x')s[1][0] = 'x';
			else	s[2][0] = 'x';
			Writeln();
			flag = 0;
		}
		if (flag && s[0][1] == '.' && s[0][2] != 'o'){
			if (s[0][2] == 'x')s[0][1] = 'x';
			else s[0][2] = 'x';
			Writeln();
			flag = 0;
		}
		if (flag && s[2][2] == '.'){
			s[2][2] = 'x';
			Writeln();
			flag = 0;
		}
		if (flag && s[1][1] == '.'){
			s[1][1] = 'x';
			Writeln();
			flag = 0;
		}
		if (flag && s[1][2] == '.'){
			s[1][2] = 'x';
			Writeln();
			flag = 0;
		}
		if (flag && s[2][1] == '.'){
			s[2][1] = 'x';
			Writeln();
			flag = 0;
		}
		if (flag)
			printf("OrzOrzOrz\n");
		Readln();
	}
	return 0;
}

