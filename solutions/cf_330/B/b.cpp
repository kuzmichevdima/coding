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

const int it_const = 100;

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, R, v;
    scanf("%d%d%d", &n, &R, &v);
    forn(j, n)
    {
        int s, f;
        scanf("%d%d", &s, &f);
        double len = f - s;
        double l = (len - 2 * R) / v;
        double r = len / v;
        double angle = (double)v / 2 / R;
        forn(it, it_const)
        {
            double m = (l + r) / 2;
            if (v * m + 2 * R * abs(sin(angle * m)) >= len)
                r = m;
            else l = m;
        }
        printf("%.10lf\n", l);
    }
}
