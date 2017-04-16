#include <bits/stdc++.h>
using namespace std;

const int MaxN = 407;
const int MaxM = 33000000;

int N, M;
bool lnk[MaxN][MaxN];
vector<int> iv[MaxN];
int proc[MaxM];

void PrintK33(int t, int i)
{
	//cout << proc[t] << endl;
	
	printf("K33\n");
	int a = t / 401, b = 1;
	while (b * (b-1) / 2 < a) b++;
	b--; a-= b * (b-1) / 2;
	printf("%d %d %d\n", a, b, t % 401);
	printf("%d %d %d\n", i, proc[t] / 401, proc[t] % 401);
}

int main()
{
	scanf("%d%d", &N, &M);
	for (int i=1; i<=M; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		lnk[a][b] = lnk[b][a] = true;
		iv[a].push_back(b);
		iv[b].push_back(a);
	}
	for (int i=1; i<=N; i++)
	{
		int l = iv[i].size();
		if (l >= 3)
		{
			for (int j=0; j<l; j++)
				for (int k=j+1; k<l; k++)
					for (int p=k+1; p<l; p++)
					{
						int a = iv[i][j], b = iv[i][k], c = iv[i][p];
						if (a > b) swap(a, b);
						if (a > c) swap(a, c);
						if (b > c) swap(b, c);
						int t = (b * (b-1) / 2 + a) * 401 + c;
						//cout << a << ' ' << b << ' ' << c << ' ' << t << endl;
						if (proc[t] > 401)
						{
							PrintK33(t, i);
							return 0;
						}
						else
						{
							//cout << t << ' ' << i << endl;
							proc[t] = proc[t] * 401 + i;
						}
					}
		}
	}
	for (int i=1; i<=N; i++)
		for (int j=i+1; j<=N; j++)
			for (int k=j+1; k<=N; k++)
				if (lnk[i][j] && lnk[j][k] && lnk[i][k])
				{
					int t = (j * (j-1) / 2 + i) * 401 + k;
					if (proc[t] <= 401) continue;
					int a = proc[t] / 401;
					int b = proc[t] % 401;
					if (lnk[a][b])
					{
						printf("K5\n");
						printf("%d %d %d %d %d\n", a, b, i, j, k);
						return 0;
					}
				}
	printf("NO\n");
	return 0;
}

