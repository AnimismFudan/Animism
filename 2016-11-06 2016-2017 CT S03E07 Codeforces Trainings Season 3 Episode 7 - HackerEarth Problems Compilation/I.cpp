#include <bits/stdc++.h>
using namespace std;

#define LL long long

LL p1, p2;

const LL pri[10] = {2,3,5,7,11,13,17,19,23,29};

LL product_mod(LL x, LL y, LL n){
	LL s = 0, t = x;
	for (; y; y >>= 1){
		if (y & 1)	s = (s + t) % n;
		t = t * 2 % n;
	}
	return s;
}


LL power_mod(LL x, LL y, LL n){
	x %= n;
	LL s = 1, t = x;
	for (; y; y >>= 1){
		if (y & 1)	s = product_mod(s, t, n);
		t = product_mod(t, t, n);
	}
	return s;
}

bool isprime(LL N){
	if (N < 2)return 0;
	if (N == 2)return 1;
	if (! ( N & 1))return 0;
	LL m, k = 0, a;
	m = N - 1;
	while (! (m & 1)) k++, m = m / 2;
	for (LL i = 2; i < 10; i++){
		if (pri[i] >= N)break;
		a = power_mod(pri[i], m, N);
		if (a == 1)
			continue;
		LL j;
		for (j = 0; j < k; j++){
			if (a == N - 1)break;
			a = product_mod(a, a, N);
		}
		if (j == k)return 0;
	}
	return 1;
}

int main()
{
	bool mov1, mov2, mov3, mov4;
	mov1 = mov2 = mov3 = mov4 = false;
	cin >> p1 >> p2;
	mov1 = isprime(p1-2);
	mov2 = isprime(p1+2);
	mov3 = isprime(p2-2);
	mov4 = isprime(p2+2);
	
	if ( p1 + 2 == p2 )
	{
		cout << p1 << "->" << p2 << endl;
		return 0;
	}
	if ( p1 + 4 == p2 && mov2 )
	{
		cout << p1 << "->" << p1+2 << "->" << p2 << endl;
		return 0;
	}
	if ( p1 == 2 )
	{
		if (mov3) cout << p1 << "->" << p2 << endl;
		else if (mov4) cout << p1 << "->" << p2+2 << "->" << p2 << endl;
		else cout << "Unlucky Benny\n";
		return 0;
	}
	if (!mov1 && !mov2)
	{
		cout << "Unlucky Benny\n";
		return 0;
	}
	if (!mov3 && !mov4)
	{
		cout << "Unlucky Benny\n";
		return 0;
	}
	if (mov1 && mov3) cout << p1 << "->" << 2 << "->" << p2 << endl;
	else if (mov1 && !mov3) cout << p1 << "->" << 2 << "->" << p2+2 << "->" << p2 << endl;
	else if (!mov1 && mov3) cout << p1 << "->" << p1+2 << "->" << 2 << "->" << p2 << endl;
	else cout << p1 << "->" << p1+2 << "->" << 2 << "->" << p2+2 << "->" << p2 << endl;
	return 0;
