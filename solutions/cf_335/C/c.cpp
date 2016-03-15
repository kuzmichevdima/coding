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

struct Point
{
    int x, y;   
    Point(){}
    Point(int x, int y) : x(x), y(y) {}
};

i64 sqr(i64 x)
{
    return x * x;
}

const ld inf = 1e18;
const ld eps = 1.0e-6;

struct Vector
{
    int x, y;
    Vector(Point p1, Point p2)
    {
        x = p2.x - p1.x;
        y = p2.y - p1.y;
    }
    i64 operator * (Vector an)
    {
        return (i64)x * an.y - (i64)y * an.x;
    }
    i64 sqrlen()
    {
        return sqr(x) + sqr(y);
    }
};

struct Line
{
    i64 a, b, c;
    Line(Point p1, Point p2)
    {
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = -p1.x * a - p1.y * b;
    }
    pair <ld, ld> intersect(Line an)
    {
        ld y = (ld)(an.c * a - c * an.a) / (b * an.a - an.b * a);
        ld x = (ld)(an.c * b - c * an.b) / (a * an.b - an.a * b);
        return mp(x, y);
    }
};

const int maxn = 1e5+5;

Point a[maxn];

int n, P, Q;

ld ans = inf;

inline void check(Point p)
{
    ld first = (ld)P / p.x;
    ld second = (ld)Q / p.y;
    ans = min(ans, max(first, second));
}

bool operator < (Point first, Point second)
{
    Vector v1(a[0], first);
    Vector v2(a[0], second);
    i64 cp = v1 * v2;
    return cp > 0 || (cp == 0 && v1.sqrlen() < v2.sqrlen());
}

ld sqrld(ld x)
{
    return x * x;
}

ld dist(pair< ld, ld> p1, Point p2)
{
    return sqrt(sqrld(p1.fi - p2.x) + sqrld(p1.se - p2.y));
}



int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d%d%d", &n, &P, &Q);
    set <pii> diff;
    forn(j, n)
    {
        Point p;
        scanf("%d%d", &p.x, &p.y);   
        if (diff.find(mp(p.x, p.y)) == diff.end())
        {
            a[diff.size()] = p;
            diff.insert(mp(p.x, p.y));
        }
    }
    n = diff.size();
    int chosen = 0;
    fore(j, 1, n - 1)
        if (a[j].y < a[chosen].y || (a[j].y == a[chosen].y && a[j].x < a[chosen].x))
            chosen = j;
    swap(a[chosen], a[0]);
    sort(a + 1, a + n);
    vector <Point> conhull;
    conhull.pb(a[0]);
    conhull.pb(a[1]);
    fore(j, 2, n - 1)
    {
        while(conhull.size() >= 2)
        {
            Vector v1(conhull[conhull.size() - 2], conhull.back());
            Vector v2(conhull.back(), a[j]);
//            if (v1 * v2 > 0 || v1 * v2 == 0 && v1.sqrlen() > v2.sqrlen())
            if (v1 * v2 > 0)
                break;
            conhull.pop_back();
        }
        conhull.pb(a[j]);
    }
   /* printf("conhull\n");
    for (auto x : conhull)
        printf("%d %d\n", x.x, x.y);*/
    conhull.pb(conhull[0]);
    Line l2(Point(0, 0), Point(P, Q));
    forn(j, conhull.size() - 1)
    {
        Line l1(conhull[j], conhull[j + 1]);
        if (l1.a * l2.b != l1.b * l2.a)
        {
            auto I = l1.intersect(l2);

            //printf("%.5lf %.5lf\n", (double)I.fi, (double)I.se);
            ld tmp = abs(dist(I, conhull[j]) + dist(I, conhull[j + 1]) - dist(mp(conhull[j].x, conhull[j].y), conhull[j + 1])); 
//            printf("tmp = %.5lf\n", (double)tmp);
            if (tmp< eps)
            {
                ld nnew = (ld)sqrt(sqr(P) + sqr(Q)) / sqrt(I.fi * I.fi + I.se * I.se);
 //               printf("nnew = %.5lf\n", (double)nnew);
                ans = min(ans, nnew);
            }
        }
        check(conhull[j]);
        check(conhull[j + 1]);
    }
    printf("%.10lf", (double)ans);
}
