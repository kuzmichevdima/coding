#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
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

const double inf = 2e9;

i64 Y_zero;

inline double get(i64 x0)
{
    if (x0 == 0)
        return Y_zero;
    i64 start = 0;
    i64 finish = 1e9;
    while(start < finish)
    {
        i64 middle = (start + finish) / 2 + 1;
        i64 tmp = 2 * middle * Y_zero;
        if (tmp <= x0)
            start = middle;
        else finish = middle - 1;
    }
    return (start == 0 ? inf : (double)x0 / (2 * start));
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    i64 a, b;
    cin >> a >> b;
    Y_zero = b;
    if (a - b < 0)
    {
        printf("-1");
        exit(0);
    }
    double first_var = get(a - b);
    double second_var = get(a + b);
    //printf("first_var = %.10lf\n", first_var);

    double ans = min(first_var, second_var);
    if (abs(ans - inf) < 1.0e-7)
        printf("-1");
    else printf("%.10lf\n", ans);
}
