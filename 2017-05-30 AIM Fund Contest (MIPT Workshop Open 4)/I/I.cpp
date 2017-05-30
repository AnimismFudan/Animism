#include <bits/stdc++.h>
using namespace std;

#define pir pair<int, long long>

const int MaxN = (int) 1e5 + 7;
const int mod1 = 9999973;
const long long mod2 = (long long)1e13 + 9;

char tmp[MaxN];
map<int, pir>  mp;

pir GetHash()
{
	int i, l = strlen(tmp);
	int h1 = 0; long long h2 = 0;
	for (i=0; i<l; i++)
	{
		h1 = (h1 * 26 + tmp[i] - 'a') % mod1;
		h2 = (h2 * 26 + tmp[i] - 'a') % mod2;
	}
	return make_pair(h1, h2);
}

int main()
{
	while (scanf("%s", tmp) != EOF)
	{
		int len = strlen(tmp);
		//printf("%s ", tmp);
		if (len < 4) printf("%s ", tmp);
		else
		{
			int a = tmp[0] - 'a', b = tmp[len-1] - 'a';
			int h = (len-2) * 26 * 26 + a * 26 + b;
			if (mp.find(h) == mp.end())
			{
				printf("%s ", tmp);
				mp[h] = GetHash();
			}
			else if (mp[h].first == -1)
			{
				printf("%s ", tmp);
			}
			else
			{
				pir p = GetHash();
				if (mp[h].first == p.first && mp[h].second == p.second)
				{
					printf("%c%d%c ", a+'a', len-2, b+'a');
				}
				else
				{
					printf("%s ", tmp);
					mp[h].first = -1;
				}
			}
		}
	}
	printf("\n");
	return 0;
}

