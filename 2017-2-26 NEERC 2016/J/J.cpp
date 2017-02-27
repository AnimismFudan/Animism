#include <bits/stdc++.h>
using namespace std;

const int MaxN = (int)1e4 + 7;
const int MaxH = 5007;
const double eps = 1e-7;

struct nodetype
{
	double x, y, w;
	void Print()
	{
		printf("(%lf, %lf) - %lf\n", x, y, w);
	}
};

int N, W, H, Q;
int l[MaxH], r[MaxH];
bool flg[MaxH][MaxN];
nodetype f[MaxH], sf[MaxH];

nodetype operator+ (const nodetype A, const nodetype B)
{
	nodetype C;
	C.w = A.w + B.w;
	C.x = A.x * A.w + B.x * B.w; C.x /= C.w;
	C.y = A.y * A.w + B.y * B.w; C.y /= C.w;
	return C;
}

nodetype operator- (const nodetype A, const nodetype B)
{
	nodetype C;
	C.w = A.w - B.w;
	C.x = A.x * A.w - B.x * B.w; C.x /= C.w;
	C.y = A.y * A.w - B.y * B.w; C.y /= C.w;
	return C;
}

void Del(int h, int x)
{
	flg[h][x] = false; l[h] = r[h] = 0;
	for (int i=1; i<=N; i++)
	{
		if (l[h] == 0 && flg[h][i]) l[h] = i;
		if (flg[h][i]) r[h] = i;
	}
	nodetype tmp;
	tmp.w = 1; tmp.x = tmp.y = .5 * N;
	if (h&1) tmp.x = x - .5;
	else tmp.y = x - .5;
	f[h] = f[h] - tmp;
}

bool Check(int h)
{
	double x, y;
	if (h >= H) return true;
	x = sf[h+1].x; y = sf[h+1].y;
	if (h&1)
	{
		if (x < l[h] - 1 + eps || r[h] < x + eps) return false;
	}
	else
	{
		if (y < l[h] - 1 + eps || r[h] < y + eps) return false;
	}
	return true;
}

int main()
{
	freopen("jenga.in", "r", stdin);
	freopen("jenga.out", "w", stdout);
	
	scanf("%d%d", &N, &W);
	scanf("%d%d", &H, &Q);
	
	for (int i=1; i<=H; i++)
		for (int j=1; j<=N; j++)
			flg[i][j] = true;
	for (int i=H; i>=1; i--)
	{
		f[i].x = f[i].y = .5 * N;
		f[i].w = N;
		sf[i] = sf[i+1] + f[i];
		l[i] = 1; r[i] = N;
	}
	
	for (int i=1; i<=Q; i++)
	{
		int h, x;
		scanf("%d%d", &h, &x);
		Del(h, x);
		
		if (l[h] == 0 && r[h] == 0)
		{
			if (h == H) H--;
			else
			{
				printf("yes\n%d\n", i);
			}
		}
		
		for (int j=h; j>=1; j--)
		{
			if (!Check(j))
			{
				printf("yes\n%d\n", i);
				return 0;
			}
			sf[j] = f[j] + sf[j+1];
		}
	}
	printf("no\n");
	
	return 0;
}

