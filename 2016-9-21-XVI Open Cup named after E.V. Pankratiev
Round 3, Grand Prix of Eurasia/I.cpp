#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define UI unsigned int

int Q, len;
UI ans, Hash;
int a[40], b[40];

void Plus_Rev(int k){
	memset(b, 0, sizeof(b));
	for (int i = 1; i <= k; i++)
		b[i] = a[i];
	for (int i = k + 1; i <= 32; i++){
		b[i] = a[i] - b[i - k];
		if (b[i] < 0){
			b[i] += 2;
			a[i + 1] --;
			int j = i + 1;
			while (j <= 32 && a[j] < 0){
				a[j] += 2;
				a[j + 1]--;
				j++;
			}
		}
	}
	for (int i = 1; i <= 32; i++)
		a[i] = b[i];
}

void Xor_Rev(int k){
	memset(b, 0, sizeof(b));
	for (int i = 32; i > 32 - k; i--)
		b[i] = a[i];
	for (int i = 32 - k; i; i--)
		b[i] = a[i] ^ b[i + k];
	for (int i = 1; i <= 32; i++)
		a[i] = b[i];
}

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	
	cin >> Q;
	for (int tt = 1; tt <= Q; tt++){
		memset(a, 0, sizeof(a));
		cin >> Hash;
		len = 0;
		while (Hash){
			a[++len] = Hash & 1;
			Hash >>= 1;
		}
		Plus_Rev(16);
		Xor_Rev(11);
		Plus_Rev(3);
		Xor_Rev(6);
		Plus_Rev(10);
		ans = 0;
		for (int i = 32; i; i--)
			ans = (ans << 1) + a[i];
		cout << ans << endl;
	}
	
	return 0;
}

