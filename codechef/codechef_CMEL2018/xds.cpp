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
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        int x;
        scanf("%d", &x);
        pair<pii, pii> best = {{1e9, 0}, {0, 0}};
        fore(d_count, 1, sqrt(x)) {
            int x_count = x / d_count;
            int rem = x - x_count * d_count;
            int cur = x_count + d_count + (rem > 0);
            if (cur < best.fi.fi) {
                best = {{cur, rem}, {x_count, d_count}};
            }
        }
        forn(i, best.se.fi)
            printf("X");
        forn(i, best.se.se - best.fi.se)
            printf("D");
        if (best.fi.se) {
            printf("X");
            forn(j, best.fi.se)
                printf("D");
        }
        printf("\n");
    }
}

