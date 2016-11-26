#include <bits/stdc++.h>
using namespace std;

#define LL long long

int Test, N;
LL T[4010], P[4010];
LL pT[4010], pP[4010], sT[4010], sP[4010];
LL spT[4010], spP[4010], ssT[4010], ssP[4010];
LL f[4010][2];

LL calcr(int l, int r, int t){
	if (t == 0)
		return spT[r] - spT[l - 1] - pT[l - 1] * (r - l + 1);
	else return spP[r] - spP[l - 1] - pP[l - 1] * (r - l + 1);
}

LL calcl(int l, int r, int t){
	if (t == 0)
		return ssT[l] - ssT[r + 1] - sT[r + 1] * (r - l + 1);
	else return ssP[l] - ssP[r + 1] - sP[r + 1] * (r - l + 1);
}

int main(){
	freopen("K.in", "r", stdin);
	freopen("K.out", "w", stdout);
	scanf("%d", &Test);
	for (int tt = 1; tt <= Test; tt++){
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
			scanf("%lld%lld", &T[i], &P[i]);
		memset(pT, 0, sizeof(pT));
		memset(pP, 0, sizeof(pP));
		memset(sT, 0, sizeof(sT));
		memset(sP, 0, sizeof(sP));
		memset(spT, 0, sizeof(spT));
		memset(spP, 0, sizeof(spP));
		memset(ssT, 0, sizeof(ssT));
		memset(ssP, 0, sizeof(ssP));
		for (int i = 1; i <= N; i++){
			pT[i] = pT[i - 1] + T[i];
			pP[i] = pP[i - 1] + P[i];
			spT[i] = spT[i - 1] + pT[i];
			spP[i] = spP[i - 1] + pP[i];
		}
		for (int i = N; i >= 1; i--){
			sT[i] = sT[i + 1] + T[i];
			sP[i] = sP[i + 1] + P[i];
			ssT[i] = ssT[i + 1] + sT[i];
			ssP[i] = ssP[i + 1] + sP[i];
		}
		for (int i = 1; i < N; i++){
			f[i][0] = calcr(1, i, 1);
			f[i][1] = calcr(1, i, 0);
		}
		f[N][0] = f[N][1] = 2e18;
		for (int i = 2; i < N; i++){
			for (int j = i - 1; j > 0; j--){
				int m = (i + j + 1) / 2;
				LL dl = calcl(j + 1, m, 0);
				LL dr = calcr(m + 1, i, 0);
				f[i][1] = min(f[i][1], f[j][0] + dl + dr);
				dl = calcl(j + 1, m, 1);
				dr = calcr(m + 1, i, 1);
				f[i][0] = min(f[i][0], f[j][1] + dl + dr);
			}
		}
		for (int i = 1; i < N; i++){
			f[N][0] = min(f[N][0], f[i][1] + calcl(i + 1, N, 1));
			f[N][1] = min(f[N][1], f[i][0] + calcl(i + 1, N, 0));
		}
		printf("Case #%d: %lld\n", tt, min(f[N][0], f[N][1]));
	}
}