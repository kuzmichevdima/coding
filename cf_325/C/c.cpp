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

i64 gcdll(i64 x, i64 y)
{
    if (x == 0 || y == 0)
        return x + y;
    if (x > y)
        return gcdll(x % y, y);
    return gcdll(y % x, x);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    i64 x, y;
    cin >> x >> y;
    if (gcdll(x, y) != 1)
    {
        printf("Impossible");
        exit(0);
    }
    while(x != 0 && y != 0)
    {
//        printf("x = %d y = %d\n", x, y);
        if (x > y)
        {
            i64 t = x / y;
            cout << (x == t * y ? t - 1: t) << "A";
            x -= t * y;
        }
        else
        {
            i64 t = y / x;
            cout << (y == t * x ? t - 1 : t) << "B";
            y -= t * x;
        }
    }
}
