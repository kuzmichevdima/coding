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

const int it_const = 100;
const int it_const_2 = 100;
const ld inf = 1e9;

const ld PI = acos(-1.0);

typedef pair<ld, ld> mypair;

ld vmax;

ld get(mypair need, mypair wind, double t, mypair & res)
{
    ld start = 0;
    ld finish = inf;
    mypair optimal;
    forn(it, it_const)
    {
        ld middle = (start + finish) / 2;
        optimal = mp(need.fi * middle - wind.fi,
                    need.se * middle - wind.se);
        if (optimal.fi * optimal.fi + optimal.se * optimal.se > vmax * vmax)
            finish = middle;
        else start = middle;
    }
//    printf("optimal %.5lf %.5lf\n", (double)optimal.fi, (double)optimal.se);
    ld time_to_reach = 1.0 / start;
    if (time_to_reach < t)
    {
        res = need;
        return time_to_reach;
    }
    else
    {
        res = mp(need.fi - (optimal.fi + wind.fi) * t, need.se - (optimal.se + wind.se) * t);
        return inf;
    }
}

mypair wind1, wind2;
ld t;

mypair change(mypair & p, ld angle)
{
    ld vx = vmax * cos(angle);
    ld vy = vmax * sin(angle);
    mypair res;
    res.first = p.fi - (vx + wind1.fi) * t;
    res.second = p.se - (vy + wind1.se) * t;
    return res;
}

mypair delta;

ld solve(ld s, ld f)
{
    ld start = s;
    ld finish = f;
    ld g1, g2;
    mypair delta1;
    forn(iter, it_const_2)
    {
        ld m1 = start + (finish - start) / 3.0;
        ld m2 = finish - (finish - start) / 3.0;
        mypair c1 = change(delta, m1);
        mypair c2 = change(delta, m2);
        g1 = get(c1, wind2, inf, delta1);
        g2 = get(c2, wind2, inf, delta1);
        if (g1 < g2)
        {
            finish = m2;          
        }
        else start = m1;
    }
    return g1 + t;

}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    ld x1, y1, x2, y2;

    cin >> x1 >> y1 >> x2 >> y2;
    delta = mp(x2 - x1, y2 - y1);
    cin >> vmax >> t;
    cin >> wind1.fi >> wind1.se;
    cin >> wind2.fi >> wind2.se;
    mypair delta1;
    ld g1 = get(delta, wind1, t, delta1);
    if (g1 <= t)
    {
        printf("%.10lf", (double)g1);
        exit(0);
    }
    ld ans1 = solve(-PI, PI);
    ld ans2 = solve(0, 2 * PI);
    ld ans = min(ans1, ans2);
    printf("%.10lf", (double)ans);

}
