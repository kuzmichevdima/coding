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

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    double eps = 1.0 / 120;
    forn(test, T)
    {
        double need;
        scanf("%lf", &need);
        forn(hours, 12)
        {
            forn(minutes, 60)
            {
                double A = hours * 30.0 + (minutes / 60.0) * 30.0;
                double B = minutes * 6.0;
                if (abs(abs(A - B) - need) < eps or abs(abs(A - B + 360) - need) < eps or abs(abs(A - B - 360) - need) < eps)
                {
                   printf("%d%d:%d%d\n", hours / 10, hours % 10, minutes / 10, minutes % 10);
                }
            }
        }
    }
}

