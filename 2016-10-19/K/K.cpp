#include <bits/stdc++.h>
using namespace std;
#define LL long long
int Test;
char s[3010], ss[3010];
int len, res, ans, sum;
int main(){
	freopen("K.in", "r", stdin);
	freopen("K.out", "w", stdout);
	scanf("%d", &Test);
	while (Test--){
		scanf("%s", s);
		len = strlen(s);
		bool flag = 1;
		sum = 0;
		res = 0;
		ans = 0;
		for (int i = 0; i < len; i++)
			if (s[i] == '*'){
				flag = 0;
				sum--;
			}else sum++;
		if (flag){
			printf("0\n");
			continue;
		}
		if (sum <= 0){
			for (int i = 0; i < -sum + 1; i++)
				ss[i] = '1';
			for (int i = 0; i < len; i++)
				ss[-sum + 1 + i] = s[i];
			len = len - sum + 1;
			for (int i = 0; i < len; i++)
				s[i] = ss[i];
			ss[len] = 0;
			ans += -sum + 1;
		}
		if (s[len - 1] != '*'){
			for (int i = 0; i < len; i++)
				if (s[i] == '*'){
					swap(s[i], s[len - 1]);
					ans++;
					break;
				}
		}
		int j = len - 1;
		for (int i = 0; i < len; i++){
			if (s[i] == '*')res--;
			else res++;
			if (res <= 0){
				while (j > i && s[j] == '*')
					j--;
				swap(s[i], s[j]);
				j--;
				res+=2;
				ans++;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
