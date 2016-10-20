#include bitsstdc++.h
#define eps (1e-8)
using namespace std;

double ans;
double A[1010];
int n,T;
char s[10];

int main() {
	for (scanf(%d,&T); T; T--) {
		scanf(%d %s,&n,s + 1);
		for (int i = 1; i = n; i++) scanf(%lf,&A[i]), A[i] = 100.0;
		double ans = 0;
		for (int i = 1; i = n; i++) {
			if (A[i]  eps) continue;
			if (s[1] == 'n')
				ans -= A[i]  log(A[i]);
			else if (s[1] == 'b')
				ans -= A[i]  log(A[i])  log(2);
			else if (s[1] == 'd')
				ans -= A[i]  log(A[i])  log(10);
		}
		printf(%.12lfn,ans);
	}
	return 0;
}
	