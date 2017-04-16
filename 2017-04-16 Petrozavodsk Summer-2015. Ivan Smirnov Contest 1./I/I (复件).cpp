#include <bits/stdc++.h>
#define eps (1e-7)
using namespace std;

double Rand() {
	return (double)(abs(rand() * rand() + rand()) % 1000000000) / 1000000000.0;
}

int done[101000];
int ans[101000];
double x[101000], y[101000];
int n, N, cnt, top;
double now, pas, T;

double dis[5010][5010];

int main() {
	freopen("I.in","r",stdin);
	freopen("I.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++)
		scanf("%lf %lf",&x[i],&y[i]);
	scanf("%lf",&T);

	for (int i=1; i<=n; i++)
	{
		for (int j=0; j<=i; j++)
			dis[i][j] = dis[j][i] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
	}
	
	int N = (n + 1) / 2;

	double d = 1e30; int loc = 0;
	for (int i=1; i<=n; i++)
		if (x[i] * x[i] + y[i] * y[i] < d) d = x[i] * x[i] + y[i] * y[i], loc = i;

	ans[++top] = loc;
	
	done[loc] = true;
	for (int i=1; i <= (n-1) / 2; i++)
	{
		int nj, j; d = 1e30; nj = 0;
		for (j=1; j<=n; j++)
			if (!done[j] && dis[loc][j] < d) d = dis[loc][j], nj = j;
		loc = nj;
		ans[++top] = loc;
		done[loc] = true;
	}  
	
	double t = 1;
	srand(173);
	for (int i = 1; i <= N; i++) now += dis[ans[i]][ans[i - 1]];	
	while (t > eps && (++cnt < 10000000) && now > T - eps) {
		int u;
		do u = abs(rand() * rand() + rand()) % n + 1;
		while (done[u]);
		int v = abs(rand() * rand() + rand()) % N + 1;
		pas = now;
		now += dis[u][ans[v - 1]] - dis[ans[v]][ans[v - 1]];
		if (v != N) now += dis[u][ans[v + 1]] - dis[ans[v]][ans[v + 1]];
		if (pas > now || Rand() < t) {
			done[ans[v]] = 0;
			ans[v] = u;			
			done[u] = 1;
		} else {
			now = pas;
		}
		t *= 0.999995;
	}
	//printf("%d\n%.10lf\n",cnt,t);
	printf("%.12lf\n",now);
	for (int i = 1; i <= N; i++)
		printf("%d ",ans[i]);
	return 0;
}
