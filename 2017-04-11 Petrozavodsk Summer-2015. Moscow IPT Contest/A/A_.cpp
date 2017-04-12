#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

#define sz(x) ((int) (x).size())
#define forn(i,n) for (int i = 0; i < int(n); ++i)

typedef long long ll;
typedef long double ld;

const int INF = 1000001000;
const ll INFL = 2000000000000001000;
int solve();


int main()
{
	freopen("A.in", "r", stdin);
	freopen("A_.out", "w", stdout);
    srand(2317);
    cout.precision(10);
    cout.setf(ios::fixed);
    int tn = 1;
    for (int i = 0; i < tn; ++i)
        solve();
}

const int maxc = 500010;
const int base = 1 << 19;

vector<pair<int, int>> pt;

int C;

vector<int> allx[2][2 * base];

#pragma pack(1)
struct InnerTree
{
    unsigned short sum;
    int l, r;
};

const int maxIT = 50000000;
InnerTree IT[maxIT];
int ITs = 1;

int buildIT(int sz)
{
    if (sz == 0)
        return 0;
    int id = ITs++;
    assert(ITs < maxIT);
    if (sz == 1)
        return id;
    IT[id].l = buildIT(sz / 2);
    IT[id].r = buildIT(sz - sz / 2);
    return id;
}

int getIT(int i, int bound, int cnt)
{
    if (cnt <= bound)
        return 0;
    if (bound <= 0)
        return IT[i].sum;
    int lcnt = cnt / 2;
    return getIT(IT[i].l, bound, lcnt) + getIT(IT[i].r, bound - lcnt, cnt - lcnt);
}

int putIT(int i, int pos, int delta, int cnt)
{
    if (cnt == 0)
        return 0;
    int res = ITs++;
    assert(ITs < maxIT);
    IT[res].l = IT[i].l, IT[res].r = IT[i].r;
    IT[res].sum = IT[i].sum + delta;
    if (cnt == 1)
        return res;
    int lcnt = cnt / 2;
    if (lcnt > pos)
        IT[res].l = putIT(IT[res].l, pos, delta, lcnt);
    else
        IT[res].r = putIT(IT[res].r, pos - lcnt, delta, cnt - lcnt);
    return res;
}

struct Tree
{
    int it;
    int l, r;
};

const int maxT = 5000000;
Tree T[maxT];
int Ts = 1;

int build(int id = 1)
{
    int i = Ts++;
    assert(Ts < maxT);
    if (id >= base)
        return i;
    T[i].l = build(id * 2);
    T[i].r = build(id * 2 + 1);
    return i;
}

int put(int i, int y, int oldx, int newx, int id = 1, int cl = 0, int cr = base)
{
    int res = Ts++;
    assert(Ts < maxT);
    T[res].l = T[i].l, T[res].r = T[i].r;
    T[res].it = T[i].it;

    if (oldx >= 0)
    {
        int innerx = lower_bound(allx[C][id].begin(), allx[C][id].end(), oldx) - allx[C][id].begin();
        assert(allx[C][id][innerx] == oldx);
        T[res].it = putIT(T[res].it, innerx, -1, sz(allx[C][id]));
    }
    int innerx = lower_bound(allx[C][id].begin(), allx[C][id].end(), newx) - allx[C][id].begin();
    assert(allx[C][id][innerx] == newx);
    T[res].it = putIT(T[res].it, innerx, 1, sz(allx[C][id]));

    if (id >= base)
        return res;
    int cc = (cl + cr) / 2;
    if (y < cc)
        T[res].l = put(T[res].l, y, oldx, newx, id * 2, cl, cc);
    else
        T[res].r = put(T[res].r, y, oldx, newx, id * 2 + 1, cc, cr);
    return res;
}

int get(int i, int yl, int yr, int xl, int id = 1, int cl = 0, int cr = base)
{
    if (yl <= cl && cr <= yr)
    {
        int innerx = lower_bound(allx[C][id].begin(), allx[C][id].end(), xl) - allx[C][id].begin();
        return getIT(T[i].it, innerx, sz(allx[C][id]));
    }
    if (yr <= cl || cr <= yl)
        return 0;
    int cc = (cl + cr) / 2;
    return get(T[i].l, yl, yr, xl, id * 2, cl, cc) + get(T[i].r, yl, yr, xl, id * 2 + 1, cc, cr);
}

int root[2][maxc];
int last[maxc];

void build_all()
{
    sort(pt.begin(), pt.end());
    for (auto p: pt)
        allx[C][base + p.second].push_back(p.first);
    for (int i = base - 1; i > 0; --i)
    {
        allx[C][i].resize(allx[C][i * 2].size() + allx[C][i * 2 + 1].size());
        allx[C][i].erase(set_union(allx[C][i * 2].begin(), allx[C][i * 2].end(), allx[C][i * 2 + 1].begin(), allx[C][i * 2 + 1].end(), 
                allx[C][i].begin()), allx[C][i].end());
    }
    int rt = build();
    int ptr = 0;
    fill(last, last + maxc, -1);
    for (int xr = 0; xr < maxc; ++xr)
    {
        while (ptr < sz(pt) && pt[ptr].first <= xr)
        {
            assert(pt[ptr].first == xr);
            int y = pt[ptr].second;
            rt = put(rt, y, last[y], xr);
            last[y] = xr;
            ++ptr;
        }
        root[C][xr] = rt;
    }
}

void swap_coords()
{
    for (auto &p: pt)
        swap(p.first, p.second);
}

int solve()
{
    int n;
    cin >> n;
    forn (i, n)
    {
        int x, y;
        cin >> x >> y;
        pt.emplace_back(x, y);
    }
    C = 1;
    build_all();
    swap_coords();
    C = 0;
    build_all();
    int q;
    cin >> q;
    forn (i, q)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        C = 0;
        int cx = get(root[0][y2], x1, x2 + 1, y1);
        C = 1;
        int cy = get(root[1][x2], y1, y2 + 1, x1);
        cout << cx << ' ' << cy << endl;
    }
    return 0;
}
