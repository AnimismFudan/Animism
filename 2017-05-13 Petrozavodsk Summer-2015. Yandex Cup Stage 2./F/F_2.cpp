#include <bits/stdc++.h>
#define eps (1e-8)
using namespace std;

struct point {
	double x, y, z;
	point (double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
};

point operator + (point a, point b) { return point(a.x + b.x, a.y + b.y, a.z + b.z); }

