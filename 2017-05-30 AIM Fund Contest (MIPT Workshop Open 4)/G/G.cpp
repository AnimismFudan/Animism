#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);
const double ans = 3.14;

int sig;
double l, r, mid, x;
bool flag;

int sign(double x){
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}

int main() {
	x = pi / (1e9 + 1);
	printf("? %.13lf\n", x);
	fflush(stdout);
	scanf("%d", &sig);
//	sig = sign(sin(ans * x));
	if (sig == 0){
		printf("! 0\n");
		fflush(stdout);
		return 0;
	}
	if (sig == -1)
		flag = 1;
	else flag = 0;
	l = 0;
	r = 1e9 + 1;
	for (int i = 1; i <= 190; i++){
		mid = (l + r) / 2;
		x = pi / mid;
		if (flag) x = -x;
		printf("? %.13lf\n", x);
		fflush(stdout);
		scanf("%d", &sig);
//		sig = sign(sin(ans * x));
		if (sig == 0){
			if (flag) mid = -mid;
			printf("! %.8lf\n", mid);
			fflush(stdout);
			return 0;
		}
		if (sig == 1) r = mid;
		else l = mid;
	}
	if (flag) l = -l;
	printf("! %.7lf\n", l);
	fflush(stdout);
	return 0;
}
