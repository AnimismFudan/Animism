#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);
const double eps = 1e-4;

int N;
double ans[110];

class mat{
    public:
    double a[3][3];
}A[110], R;

inline double dist(const mat &A, const mat &B){
    double res = 0;
    for (int i = 0; i < 3; i++)
        res += (A.a[0][i] - B.a[0][i]) * (A.a[0][i] - B.a[0][i]);
    return sqrt(res);
}

inline mat operator * (const mat &A, const mat &B){
    mat C;
    memset(C.a, 0, sizeof(C.a));
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                C.a[i][j] += A.a[i][k] * B.a[k][j];
    return C;
}

inline mat rev(const mat &A){
    double a[3][6];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++)
            a[i][j] = A.a[i][j];
        for (int j = 3; j < 6; j++)
            a[i][j] = 0;
        a[i][3 + i] = 1;
    }
    for (int i = 0; i < 3; i++){
        int k = i;
        while (k < 3 && fabs(a[k][i]) < eps)
            k++;
        if (i != k)
            for (int j = 0; j < 6; j++)
                a[i][j] -= a[k][j];
        double t = a[i][i];
        for (int j = 0; j < 6; j++)
            a[i][j] /= t;
        for (k = 0; k < 3; k++)
            if (k != i && fabs(a[k][i]) > eps){
                double t1 = a[i][i], t2 = a[k][i];
                for (int j = 0; j < 6; j++)
                    a[k][j] = a[k][j] - a[i][j] * t2 / t1;
            }
    }
    mat T;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            T.a[i][j] = a[i][3 + j];
    return T;
}

inline double check(double s){
    mat p;
    memset(p.a, 0, sizeof(p.a));
    p.a[0][0] = cos(s);
    p.a[0][1] = 0;
    p.a[0][2] = sin(s);
    mat pp = p;
    pp = pp * R;
    double d = dist(p, pp);
    double c = (1 + 1 - d * d) / 2;
    double selta = acos(c);
    return selta;
}

inline double calc(int a, int b){
    R = rev(A[b]);
//    mat RR = A[b] * R;
    R = A[a] * R;
    double delta = pi / 2;
    double x = 0;
    double sx = check(x);
    double y, sy;
    for (int i = 0; i < 20; i++){
        y = x;
        if (rand() & 1) y += delta;
        else y -= delta;
        if (y >= pi) y -= 2 * pi;
        if (y < -pi) y += 2 * pi;
        sy = check(y);
        if (sy > sx) sx = sy, x = y;
        delta = delta * 0.8;
    }
    return sx;
}

int main(){
    srand(time(0));
    while (scanf("%d", &N) != EOF){
        for (int i = 1; i <= N; i++)
            for (int j = 0; j < 3; j++)
                for (int k = 0; k < 3; k++)
                    scanf("%lf", &A[i].a[j][k]);
        for (int i = 1; i <= N; i++)
            ans[i] = 2e9;
        for (int i = 1; i <= N; i++)
            for (int j = i + 1; j <= N; j++){
                double res = calc(i, j);
                ans[i] = min(ans[i], res);
                ans[j] = min(ans[j], res);
            }
        for (int i = 1; i <= N; i++){
            printf("%.2lf", ans[i]);
            if (i < N)printf(" ");
            else printf("\n");
        }
    }
    return 0;
}
