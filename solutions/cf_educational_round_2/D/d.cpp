#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <cstdlib>

using namespace std;


#define INF 1e+9
#define mp make_pair
#define pb push_back
#define fi first
#define fs first
#define se second
#define i64 long long
#define li long long
#define lint long long
#define pii pair<int, int>
#define vi vector<int>
#define ld long double

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)

const ld PI = acos(-1.0);

inline ld sqr(ld x)
{
    return x * x;
}

struct Point
{
    ld x, y;
    ld distTo(Point an)
    {
        return sqrt(sqr(x - an.x) + sqr(y - an.y));
    }
};

struct Circle
{
    Point center;
    ld r;
    Circle()
    {
        cin >> center.x >> center.y >> r;
    }
};

ld get(ld r1, ld r2, ld d)
{
    ld alpha = acos((sqr(r2) + sqr(d) - sqr(r1)) / (2 * r2 * d));
    return alpha * sqr(r2) - sqr(r2) * sin(alpha) * cos(alpha);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    Circle C1, C2;
    if (C1.r > C2.r)
        swap(C1, C2);
    ld r1 = C1.r;
    ld r2 = C2.r;

    ld d = C1.center.distTo(C2.center);
   // printf("d = %.12lf\n", (double)d);
    if (d + r1 <= r2)
    {
        printf("%.12lf\n", (double)(PI * sqr(r1)));
        exit(0);
    }
    if (d > r1 + r2)
    {
        printf("0.0");
        exit(0);
    }
    ld ans1 = get(r1, r2, d);
    ld ans2 = get(r2, r1, d);
    ld ans = ans1 + ans2;
    printf("%.12lf\n", (double)ans);
}
