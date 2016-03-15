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

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)

const int maxn = 2e5+5;
const int it_count = 150;

int a[maxn];
int n;

inline double f(double x)
{
    double cur = 0, minn = 0, maxx = 0;
    double ret = 0.0;
    forn(pos, n)
    {
        cur += a[pos] - x;
        minn = min(minn, cur);
        maxx = max(maxx, cur);
        ret = max(ret, max(abs(cur - minn), abs(cur - maxx)));
    }
    return ret;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d", &n);
    forn(j, n)
        scanf("%d", &a[j]);
    double start = -2e4;
    double finish = 2e4;
    forn(iter, it_count)
    {
        double m1 = start + (finish - start) / 3;
        double m2 = finish - (finish - start) / 3;
        double f1 = f(m1);
        double f2 = f(m2);
        if (f1 < f2)
            finish = m2;
        else start = m1;
    }
    double ans = f(start);
/*    for (double diff = 0.1; diff <= 10; diff += 0.1)
    {
        assert(f(start - diff) > ans);
        assert(f(start + diff) > ans);
    }*/
    printf("%.10lf\n", ans);
}
