#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-7;
const double pi = acos(-1.0);

int Test;
bool flag;

class poi;

class poi3{
	public:
	double x, y, z;
	poi topoi();
	void rotatex(double selta);
	void rotatey(double selta);
	void rotatez(double selta);
};

class poi{
	public:
	double latitude, longitude;
	void read(){
		scanf("%lf%lf", &latitude, &longitude);
		latitude = latitude / 180 * pi;
		longitude = longitude / 180 * pi;
	}
	poi3 topoi3();
	void rotatex(double selta);
	void rotatey(double selta);
	void rotatez(double selta);
}AS, AF, BS, BF;

poi3 poi :: topoi3(){
	poi3 C;
	C.x = cos(latitude) * cos(longitude);
	C.y = cos(latitude) * sin(longitude);
	C.z = sin(latitude);
	return C;
}

poi poi3 :: topoi(){
	poi C;
	double l = sqrt(x * x + y * y);
	C.latitude = atan2(z, l);
	C.longitude = atan2(y, x);
	return C;
}

void poi3 :: rotatex(double selta){
	poi3 C;
	C.x = x;
	C.y = y * cos(selta) - z * sin(selta);
	C.z = y * sin(selta) + z * cos(selta);
	*this = C;
}

void poi3 :: rotatey(double selta){
	poi3 C;
	C.y = y;
	C.z = z * cos(selta) - x * sin(selta);
	C.x = z * sin(selta) + x * cos(selta);
	*this = C;
}

void poi3 :: rotatez(double selta){
	poi3 C;
	C.z = z;
	C.x = x * cos(selta) - y * sin(selta);
	C.y = x * sin(selta) + y * cos(selta);
	*this = C;
}

void poi :: rotatex(double selta){
	poi3 C = topoi3();
	C.rotatex(selta);
	*this = C.topoi();
}

void poi :: rotatey(double selta){
	poi3 C = topoi3();
	C.rotatey(selta);
	*this = C.topoi();
}

void poi :: rotatez(double selta){
	poi3 C = topoi3();
	C.rotatez(selta);
	*this = C.topoi();
}

double signal(double x){
	if (x > eps) return 1;
	if (x < -eps) return -1;
	return 0;
}

void TT(double &l, double &r){
	double t1 = r - l;
	if (t1 < 0) t1 += 2 * pi;
	double t2 = l - r;
	if (t2 < 0) t2 += 2 * pi;
	if (t1 > t2)
		swap(l, r);
	if (l > r) r += 2 * pi;
}

bool in(double l, double r, double x){
	TT(l, r);
	if (l <= x && x <= r) return 1;
	x += 2 * pi;
	if (l <= x && x <= r) return 1;
	return 0;
}

bool in(double l, double r, double ll, double rr){
	TT(l, r);
	TT(ll, rr);
	if (l <= ll && rr <= r) return 1;
	if (l <= ll + 2 * pi && rr + 2 * pi <= r) return 1;
	if (l + 2 * pi <= ll && rr <= r + 2 * pi) return 1;
	return 0;
}

bool check(){
	double selta, x, y;
	selta = AS.longitude;
	AS.rotatez(-selta);
	AF.rotatez(-selta);
	BS.rotatez(-selta);
	BF.rotatez(-selta);
	selta = AS.latitude;
	AS.rotatey(selta);
	AF.rotatey(selta);
	BS.rotatey(selta);
	BF.rotatey(selta);
	x = sin(AF.longitude) * cos(AF.latitude);
	y = sin(AF.latitude);
	selta = atan2(y, x);
	AS.rotatex(-selta);
	AF.rotatex(-selta);
	BS.rotatex(-selta);
	BF.rotatex(-selta);
	if (fabs(BS.latitude) < eps && in(AS.longitude, AF.longitude, BS.longitude))
		return 1;
	if (fabs(BF.latitude) < eps && in(AS.longitude, AF.longitude, BF.longitude))
		return 1;
	if (fabs(BS.latitude) < eps && fabs(BF.latitude) < eps && in(BS.longitude, BF.longitude, AS.longitude, AF.longitude))
		return 1;
	return signal(BS.latitude) * signal(BF.latitude) < 0;
}

int main(){
	freopen("flight.in", "r", stdin);
	freopen("flight.out", "w", stdout);
	scanf("%d", &Test);
	while (Test--){
		AS.read();
		AF.read();
		BS.read();
		BF.read();
		flag = 1;
		flag &= check();
		swap(AS, BS);
		swap(AF, BF);
		flag &= check();
		flag?printf("DANGER\n"):printf("SAFELY\n");
	}
}
