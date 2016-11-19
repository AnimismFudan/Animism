#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
using namespace std;
typedef long long ll;
const int maxn = 10011;
struct{
	int to, nxt;
}E[maxn << 1];
int zh[maxn], tot;
void addedge(int u, int v){
	E[++tot].to = v;
	E[tot].nxt = zh[u];
	zh[u] = tot;
}

int n, m, k;
ll mk[1011][30];//%50
int col[1011];
int pre[1011][1011] = {};
ll MAXE = (1ll << 50) - 1;

ll GET(ll p){
	ll ret = -1;
	while (p){
		ret++;
		p /= 2;
	}
	return ret;
}
bool Getcol(int u){
	int kk = k / 50;
	if (k % 50 == 0) kk--;
	ll p = 0, pp = 0;
	rep(i, 0, kk){
		if (mk[u][i] != 0){
			p = (mk[u][i] & (-mk[u][i]));
			//cout<<u<<" "<<mk[u][i]<<" "<<i<<" "<<p<<endl;
			pp = i;
			break;
		}
	}
	if (p == 0) return 0;
	p = GET(p);
	col[u] = (int)(pp * 50 + p);
	for (int i = zh[u]; i; i = E[i].nxt){
		int v = E[i].to;
		//cout<<mk[v][pp]<<" ";
		mk[v][pp] |= (1ll << p);
		mk[v][pp] ^= (1ll << p);
		pre[v][pp * 50 + p] = u;
		//cout<<u<<" "<<v<<" "<<p<<" "<<pp<<" "<<mk[v][pp]<<endl;
	}
	return 1;
}
int main(){
	//freopen("H.in", "r", stdin);
	//freopen("H.out", "w", stdout);
	int Tcase;
	cin>>Tcase;
	while (Tcase--){
		scanf("%d%d", &n, &m);
		scanf("%d", &k);

		rep(i, 1, n){
			zh[i] = 0;
			col[i] = -1;
			rep(j, 0, k / 50)
				mk[i][j] = MAXE;
			mk[i][k / 50] = (1ll << (k % 50)) - 1;
		}
		tot = 0;

		rep(i, 1, m){
			int a, b;
			scanf("%d%d", &a, &b);
			addedge(a, b);
			addedge(b, a);
		}

		bool colorisok = 1;
		rep(i, 1, n){
			if (!Getcol(i)){
				colorisok = 0;
				int p = i;
				printf("path ");
				printf("%d", p);
				for (int i = k - 1; i >= 0; i--){
					p = pre[p][i];
					printf(" %d", p);
				}
				printf("\n");
				break;
			}
		}
		if (colorisok){
			printf("coloring");
			rep(i, 1, n)
				printf(" %d", col[i] + 1);
			printf("\n");
		}
	}
	return 0;
}
