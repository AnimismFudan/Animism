#include <cstdio>
using namespace std;

int a,b;

int gcd(int a,int b) {
	return b ? gcd(b, a % b) : a;
}

int main() {
	//freopen("G.in","r",stdin);
	//freopen("G.out","w",stdout);
	scanf("%d %d",&a,&b);
	printf("%d\n",gcd(a,b));
	return 0;
}
