#include <bits/stdc++.h>
using namespace std;

int Max[1010],Min[1010],Max_[1010],Min_[1010];
int t,n,T;

void get_(char &ch) {
	do ch = getchar(); while (ch != '<' && ch != '>' && ch != '=');
}

int main() {
	for (scanf("%d",&T); T; T--) {
		scanf("%d",&n);
		t = 0;
		for (int i = 1; i <= n; i++) {
			t++;
			Max[t] = Min[t] = i;
		}
		while (t > 1) {
			int t_ = 0;
			for (int i = 1; i < t; i += 2) {
				char ch;
				t_++;
				printf("? %d %d\n",Max[i], Max[i + 1]);
				fflush(stdout);
				get_(ch);
				if (ch == '>') Max_[t_] = Max[i];
				else Max_[t_] = Max[i + 1];
				if (Max[i] == Min[i] && Max[i + 1] == Min[i + 1]) {
					if (Max_[t_] == Max[i])
						Min_[t_] = Min[i + 1];
					else
						Min_[t_] = Min[i];
				} else {
					printf("? %d %d\n",Min[i], Min[i + 1]);
					fflush(stdout);
					get_(ch);
					if (ch == '<') Min_[t_] = Min[i];
					else Min_[t_] = Min[i + 1];
				}
			}
			if (t & 1) {
				t_++;
				Max_[t_] = Max[t];
				Min_[t_] = Min[t];
			}
			t = t_;
			for (int i = 1; i <= t; i++)
				Max[i] = Max_[i], Min[i] = Min_[i];
		}
		printf("! %d %d\n",Min[1],Max[1]);
		fflush(stdout);
	}
}
