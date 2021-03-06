#include <bits/stdc++.h>
#define LL long long
using namespace std;

int a[10];
char s[110];
int step, win_time;

class match{
	public:
	int x, y, goal_x, goal_y;
	bool ot;
}P[10];

class team{
	public:
	int t[5];
	LL ran;
}Sta[10];

bool cmp_ran(const int &A, const int &B){
	return Sta[A].ran > Sta[B].ran;
}

bool cmps(const int &A, const int &B){
	return Sta[A].t[step] > Sta[B].t[step];
}

int get_N(char *s){
	if (s[0] == 'R')return 0;
	if (s[0] == 'S')return 1;
	if (s[0] == 'F')return 2;
	if (s[0] == 'N')return 3;
	return -1;
}

int get_winner(int x, int y){
	for (int i = 0; i < 6; i++)
		if ((P[i].x == x && P[i].y == y) ||
			(P[i].x == y && P[i].y == x)){
				int winner = -1;
				if (P[i].goal_x > P[i].goal_y)
					winner = P[i].x;
					else winner = P[i].y;
				return winner;
			}
	return -1;
}

void get_sort(){
	for (int i = 0; i < 5; i++){
		step = i;
		for (int j = 0; j < 4; j++)a[j] = j;
		sort(a, a + 4, cmps);
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
				if (Sta[j].t[i] == Sta[a[k]].t[i]){
					Sta[j].ran = (Sta[j].ran * 10 + 4 - k) * 10;
					break;
				}
		sort(a, a + 4, cmp_ran);
		for (int j = 0; j < 4; j++){
			int k = j;
			while (k + 1 < 4 && Sta[a[k + 1]].ran == Sta[a[j]].ran)k++;
			if (k - j == 1){
				int winner = get_winner(a[j], a[k]);
				Sta[winner].ran += 5;
			}
			j = k;
		}
	}
}

int check(){
	//always win return 2
	//always lose return 0
	//otherwise return 1
	for (int i = 0; i < 4; i++){
		Sta[i].t[0] = 0;//score
		Sta[i].t[1] = 0;//wins
		Sta[i].t[2] = 0;//wins_p
		Sta[i].t[3] = 0;//goal_c
		Sta[i].t[4] = 0;//goal
		Sta[i].ran = 0;
	}
	for (int i = 1; i <= 6; i++){
		int winner;
		if (P[i].goal_x > P[i].goal_y)	winner = P[i].x;
		else	winner = P[i].y;
		if (P[i].ot){
			Sta[winner].t[0] += 2;
			Sta[P[i].x + P[i].y - winner].t[0] += 1;
			Sta[winner].t[1]++;
		}
		else{
			Sta[winner].t[0] += 2;
			Sta[winner].t[1]++;
			Sta[winner].t[2]++;
		}
		Sta[P[i].x].t[4] += P[i].goal_x;
		Sta[P[i].y].t[4] += P[i].goal_y;
		Sta[P[i].x].t[3] += P[i].goal_x - P[i].goal_y;
		Sta[P[i].y].t[3] += P[i].goal_y - P[i].goal_x;
	}
	for (int i = 0; i < 4; i++)a[i] = i;
	get_sort();
	
	sort(a, a + 4, cmp_ran);
	int x = -1;
	for (int i = 0; i < 4; i++)
		if (a[i] == 0)
			x = i;
	if (0 <= x && x < 2){
		if (Sta[a[2]].ran == Sta[0].ran)
			return 1;
		return 2;
	}else{
		if (Sta[a[1]].ran == Sta[0].ran)
			return 1;
		return 0;
	}
}

int main() {
	freopen("H.in","r",stdin);
	freopen("H.out","w",stdout);
	scanf("%s", s);
	for (int i = 1; i <= 5; i++){
		P[i].x = get_N(s);
		scanf("%s", s);
		P[i].y = get_N(s);
		scanf("%d%d", &P[i].goal_x, &P[i].goal_y);
		scanf("%s", s);
		if (s[0] == 'O'){
			P[i].ot = 1;
			scanf("%s", s);
		}
		else P[i].ot = 0;
	}
	P[6].x = get_N(s);
	scanf("%s", s);
	P[6].y = get_N(s);
	
	int win_time = 0;
	int ss = 0;
	
	P[6].goal_x = 1e9;
	P[6].goal_y = 0;
	P[6].ot = 0;
	win_time += check();
	ss += 2;
	
	P[6].goal_x = (1e9) + 1;
	P[6].goal_y = 1e9;
	P[6].ot = 1;
	win_time += check();
	ss += 2;
	
	P[6].goal_x = 0;
	P[6].goal_y = 1e9;
	P[6].ot = 0;
	win_time += check();
	ss += 2;
	
	P[6].goal_x = 1e9;
	P[6].goal_y = (1e9) + 1;
	P[6].ot = 1;
	win_time += check();
	ss += 2;
	
	for (int i = 0; i <= 120; i++)
		for (int j = 0; j <= 120; j++){
			if (i == j)
				continue;
			P[6].goal_x = i;
			P[6].goal_y = j;
			P[6].ot = 0;
			win_time += check();
			ss += 2;
			
			if (abs(i - j) > 1)
				continue;
			P[6].goal_x = i;
			P[6].goal_y = j;
			P[6].ot = 1;
			win_time += check();
			ss += 2;
		}
	if (win_time == ss)printf("Already in playoff!\n");
	else if (win_time == 0)printf("No chance\n");
	else printf("Believe in playoff!\n");
	
	return 0;
}
