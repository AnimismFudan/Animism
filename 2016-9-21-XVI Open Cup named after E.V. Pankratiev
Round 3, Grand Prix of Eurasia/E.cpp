#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define UI unsigned int

int N, M, K, pt, len;
int a[30], pre[2010];
int res[2000010];
bool vis[2010];
int q[20000010];
double dist[30][2010];
class poi{
	public:
	double x, y;
}P[2010];
int st[2010], ne[200010], go[200010];
double Vr, Vf;

class rec{
	public:
	double d;
	int x;
	bool operator > (const rec &X)const{
		return d > X.d;
	}
}p, pp;
priority_queue <rec, vector<rec>, greater<rec> > heap;

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

inline double dis(const poi &A, const poi &B){
	return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	
	scanf("%d%d%d%lf%lf",&N,&M,&K,&Vr,&Vf);
	
	for (int i = 1; i <= N; i++)
		scanf("%lf%lf", &P[i].x, &P[i].y);
	for (int i = 1; i <= M; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		Add(x, y);
		Add(y, x);
	}
	for (int i = 1; i <= K; i++)scanf("%d", &a[i]);
	a[0] = 1;
	a[K + 1] = N;
	for (int i = 0; i <= K + 1; i++)
		for (int j = 1; j <= N; j++)
			dist[i][j] = 1e9;
	dist[0][1] = 0;
	res[len = 1] = 1;
	for (int i = 1; i <= K + 1; i++){
		dist[i][a[i - 1]] = dist[i - 1][a[i - 1]];
		memset(vis, 0, sizeof(vis));
		for (;!vis[a[i]];){
			int x = 0;
			for (int j = 1; j <= N; j++)
				if (!vis[j] && (!x || dist[i][j] < dist[i][x]))
					x = j;
			vis[x] = 1;
			for (int j = st[x]; j; j = ne[j])
				if (dist[i][go[j]] > dist[i][x] + dis(P[x], P[go[j]]) / Vr){
					dist[i][go[j]] = dist[i][x] + dis(P[x], P[go[j]]) / Vr;
					pre[go[j]] = x;
				}
			for (int j = 1; j <= N; j++)
				if (dist[i][j] > dist[i][x] + dis(P[x], P[j]) / Vf){
					dist[i][j] = dist[i][x] + dis(P[x], P[j]) / Vf;
					pre[j] = x;
				}
		}
		int x = a[i];
		int ll = len + 1;
		while (x != a[i - 1]){
			res[++len] = x;
			x = pre[x];
		}
		for (int l = ll, r = len; l < r; l++, r--)
			swap(res[l], res[r]);
	}
	printf("%.10lf\n", dist[K + 1][N]);
	for (int i = 1; i <= len; i++){
		printf("%d", res[i]);
		if (i < len)printf(" ");
		else printf("\n");
	}
	return 0;
}

