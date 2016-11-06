#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MaxN = (int)1e5 + 7;
const double eps = 1e-3;

int n,h,A[MaxN];
ll S,F[MaxN],ans;
double a,b,c;

void Init()
{
	int i;
	scanf("%d%d", &n, &h);
	for (i=0; i<n; i++)
	{
		scanf("%d", A+i);
		F[i] = F[i-1] + A[i] + i + 1;
	}
	S = F[n-1];
}

inline ll Calc()
{
	double le, ri, mi, d;
	le = 1; ri = 1e18;
	while (fabs(le-ri) > eps)
	{
		mi = .5 * (le+ri);
		d = a*mi*mi + b*mi + c;
		if (d < -eps) le = mi;
		else ri = mi;
	}
	//cout << mi << ' ' << d << endl;
	ll res = (ll) mi;
	while (a*res*res + b*res + c > eps) res--;
	while (a*res*res + b*res + c < -eps) res++;
	return res;
}	

void Solve()
{
	int j; ll i;
	ans = -1;
	for (j=0; j<n; j++)
	{
		a = .5 * n * n;
		b = 1.0 * S - .5 * n * n + 1.0 * n * (j+1);
		c = 1.0 * F[j] - h;
		//cout << "Calc: " << j << endl;
		//cout << a << ' ' << b << ' ' << c << endl;
		if (F[j] >= h) i = 0LL;
		else i = Calc();
		if (ans == -1 || n*i + j + 1 < ans)
			ans = n*i + j + 1;
		//cout << i << ' ' << j << endl;
	}
	printf("%I64d\n", ans);
	return;
}

int main()
{
	
	Init();
	Solve();
	return 0;
}
