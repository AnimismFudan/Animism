#include <bits/stdc++.h>
using namespace std;
#define LL long long

const int MaxN = 30;

const int con = 100000000;

class gj{
	public:
	int a[110];
	void getdata(const int &x){
		memset(a, 0, sizeof(a));
		a[0] = 1;
		a[1] = x;
	}
	void priln(){
		printf("%d", a[a[0]]);
		for (int i = a[0] - 1; i > 0; i--)
			printf("%08d", a[i]);
		printf("\n");
	}
	bool operator == (const int &X){
		if (a[0] > 1)return 0;
		if (a[0] == 0 && X)return 0;
		if (a[1] != X)return 0;
		return 1;
	}
	bool operator != (const int &X){
		return !((*this) == X);
	}
	bool operator >= (const gj &X){
		if (a[0] < X.a[0])return 0;
		if (a[0] > X.a[0])return 1;
		for (int i = a[0]; i; i--){
			if (a[i] < X.a[i])return 0;
			if (a[i] > X.a[i])return 1;
		}
		return 1;
	}
	bool operator <= (const gj &X){
		if (a[0] < X.a[0])return 1;
		if (a[0] > X.a[0])return 0;
		for (int i = a[0]; i; i--){
			if (a[i] < X.a[i])return 1;
			if (a[i] > X.a[i])return 0;
		}
		return 1;
	}
	gj operator + (const gj &X){
		gj c;
		memset(c.a, 0, sizeof(c.a));
		for (int i = 1; i <= a[0] || i <= X.a[0]; i++){
			c.a[i] += a[i] + X.a[i];
			c.a[i + 1] = c.a[i] / con;
			c.a[i] = c.a[i] - c.a[i + 1] * con;
		}
		if (a[0] < X.a[0])c.a[0] = X.a[0];
		else c.a[0] = a[0];
		while (c.a[c.a[0] + 1])++c.a[0];
		while (c.a[0] && !c.a[c.a[0]])c.a[0]--;
		return c;
	}
	gj operator -(const gj &X){
		gj c;
		memcpy(c.a, a, sizeof(c.a));
		for (int i = 1; i <= a[0]; i++){
			c.a[i] = c.a[i] - X.a[i];
			if (c.a[i] < 0){
				c.a[i + 1]--;
				c.a[i] += con;
			}
		}
		while (c.a[0] && !c.a[c.a[0]])
			c.a[0]--;
		return c;
	}
	gj operator * (const int &X){
		gj c;
		memset(c.a, 0, sizeof(c.a));
		int t;
		LL x;
		for (int i = 1; i <= a[0]; i++){
			x = (LL)a[i] * X + c.a[i];
			t = x/ con;
			c.a[i + 1] += t;
			c.a[i] = x - t * con;
		}
		c.a[0] = a[0];
		if (c.a[c.a[0] + 1] > 0)c.a[0]++;
		while (c.a[0] && !c.a[c.a[0]])c.a[0]--;
		return c;
	}
	
	
	gj operator * (const gj &X){
		gj c;
		memset(c.a, 0, sizeof(c.a));
		int t;
		LL x;
		for (int i = 1; i <= a[0]; i++)
			for (int j = 1; j <= X.a[0]; j++){
				x = (LL)a[i] * X.a[j] + c.a[i + j - 1];
				t = x / con;
				c.a[i + j] += t;
				c.a[i + j - 1]= x - t * con;
			}
		c.a[0] = max(a[0] + X.a[0] - 1, 0);
		while (c.a[c.a[0] + 1])c.a[0]++;
		while (c.a[0] && !c.a[c.a[0]])c.a[0]--;
		return c;
	}
	gj operator /(gj X){
		gj c;c.getdata(0);
		gj d;d.getdata(0);
		c.a[0] = a[0] - X.a[0] + 1;
		d.a[0] = X.a[0] - 1;
		for (int i = 1; i < X.a[0]; i++)
			d.a[i] = a[a[0] - X.a[0] + i + 1];
		for (int i = a[0] - X.a[0] + 1; i > 0; i--){
			for (int j = d.a[0]; j; j--)
				d.a[j + 1] = d.a[j];
			d.a[1] = a[i];
			d.a[0]++;
			while (d.a[0] && !d.a[d.a[0]])d.a[0]--;
			int ll = 0, rr = con - 1;
			while (ll < rr){
				int mid = (ll + rr + 1) >> 1;
				if (d >= (X * mid))ll = mid;
				else rr = mid - 1;
			}
			c.a[i] = ll;
			d = d - X * ll;
		}
		return c;
	}
	gj operator %(gj X){
		gj c;c.getdata(0);
		gj d;d.getdata(0);
		c.a[0] = a[0] - X.a[0] + 1;
		d.a[0] = X.a[0] - 1;
		for (int i = 1; i < X.a[0]; i++)
			d.a[i] = a[a[0] - X.a[0] + i + 1];
		for (int i = a[0] - X.a[0] + 1; i > 0; i--){
			for (int j = d.a[0]; j; j--)
				d.a[j + 1] = d.a[j];
			d.a[1] = a[i];
			d.a[0]++;
			while (d.a[0] && !d.a[d.a[0]])d.a[0]--;
			int ll = 0, rr = con - 1;
			while (ll < rr){
				int mid = (ll + rr + 1) >> 1;
				if (d >= (X * mid))ll = mid;
				else rr = mid - 1;
			}
			c.a[i] = ll;
			d = d - X * ll;
		}
		return d;
	}
};

struct fenshu
{
	gj a,b; // a/b
	void Set(int d)
	{
		a.getdata(d); b.getdata(1);
	}
	void Add(gj d, fenshu B)
	{
		gj t = b;
		b = t * B.b;
		a = a*B.b + t*d*B.a;
	}
	void Sub(fenshu B)
	{
		gj t = b;
		b = t*B.b;
		a = a*B.b - t*B.a;
	}
};

int T,n;
gj c[MaxN],f[MaxN];
gj A[MaxN][MaxN],B[MaxN];
fenshu X[MaxN];

void Init()
{
	int i,j; gj s;
	scanf("%d",&n); n++;
	for(i=0; i<n; i++){
		int x;
		scanf("%d",x);
		c[i].getdata(x);
	}
	for(i=0; i<=n; i++)
	{
		f[i] = 0; s = 1;
		for(j=0; j<n; j++)
			f[i] = f[i] + s*c[j],
			s *= i;
	}
	B[0] = f[0];
	for(i=1; i<=n; i++) B[i] = B[i-1] + f[i];
	for(i=0; i<=n; i++)
	{
		A[i][0] = 1;
		for(j=1; j<=n; j++)
			A[i][j] = A[i][j-1] * i;
	}

/*	for(int i=0; i<=n; i++)
	{
		for(int j=0; j<=n; j++)
			printf("%d ",A[i][j]);
		printf(" |  %d\n",B[i]);
	}*/

}

gj Gcd(gj a, gj b)
{
	gj t;
	while(b != 0)
	{
		t = a;
		a = b;
		b = t % b;
	}
	return a;
}

void Solve()
{
	int i,j,k; gj p,q,d,s = 0; fenshu tmp;
	for(i=0; i<=n; i++)
	{
		for(j=i; j<=n; j++)
			if(A[j][i]!=0) break;
		if(i!=j)
		{
			swap(B[i], B[j]);
			for(k=i; k<=n; k++)
				swap(A[i][k], A[j][k]);
		}
		for(j=i+1; j<=n; j++)
		{
			p = A[i][i]; q = A[j][i];
			for(k=i; k<=n; k++)
				A[j][k] = A[j][k]*p - A[i][k]*q;
			B[j] = B[j]*p - B[i]*q;
		}

		for(int i=0; i<=n; i++)
		{
			for(int j=0; j<=n; j++)
				printf("%d ",A[i][j]);
			printf(" |  %d\n",B[i]);
		}
		printf("\n");

	}
	
	for(i=n; i>=0; i--)
	{
		if(A[i][i]==0)
		{
			X[i].Set(0);
			continue;
		}
		tmp.Set(0);
		for(j=i+1; j<=n; j++)
		{
			tmp.Add(A[i][j], X[j]);
		}
		X[i].a = B[i];
		X[i].b = 1;
		X[i].Sub(tmp);
		X[i].b = X[i].b * A[i][i];
		
		d = Gcd(X[i].a, X[i].b);
		X[i].a = X[i].a / d;
		X[i].b = X[i].b / d;
		
		printf("%d / %d\n",X[i].a,X[i].b);
	}
	
	for(i=0; i<=n; i++)
	{
		d = Gcd(X[i].a, X[i].b);
		X[i].a = X[i].a / d;
		X[i].b = X[i].b / d;
		s = s + abs(X[i].a);
	}
	s.priln();
}

int main()
{
	freopen("H.in","r",stdin);
	//freopen("H.out","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		Init();
		Solve();
	}
	return 0;
}

