#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);

int Test;
double H;

double calc_cir(double a, double b){
    return pi * a * b;
}

double calc1(double H){
    double h = 4 - H * 2;
    return calc_cir(sqrt(2 * 2 + h * h) / 2, 1);
}

double check1(double L){
    double Ls = acos(L);
    double res = 0;
    res += 2 * L * (pi - Ls) / (L + 1);
    res += L * sin(2 * Ls) / (L + 1);
    res += 4 * pow(sin(Ls), 3) / 3 / (L + 1);
    return res;
}

double check2(double T){
    T += 1;
    double b = 1;
    double h = 2 / T * 2;
    double a = sqrt(2 * 2 + h * h) / 2;
    double L = a - T * a;
    double Ls = acos(L / a);
    double res = 0;
    res += a * b / 2 * Ls;
    res -= a * b / 4 * sin(2 * Ls);
    return res * 2;
}

double calc2(double H){
    if (H == 0)
        return 0;
    double V = pi * H;
    double l = -1, r = 1;
    for (int i = 0; i < 100; i++){
        double mid = (l + r) / 2;
        if (check1(mid) > V) r = mid;
        else l = mid;
    }
    return check2(l);
}

int main(){
    scanf("%d", &Test);
    while (Test--){
        scanf("%lf", &H);
        if (H >= 1.0)
            printf("%.5lf\n", calc1(H));
        else
            printf("%.5lf\n", calc2(H));
    }
    return 0;
}
