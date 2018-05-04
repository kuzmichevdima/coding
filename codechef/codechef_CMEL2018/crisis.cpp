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
        int n, minn;
        scanf("%d%d", &n, &minn);
        vector<pii> order;
        fore(i, 1, n) {
            int x;
            scanf("%d", &x);
            order.pb({-x, i});
        }
        sort(order.begin(), order.end());
        i64 numerator = 0;
        i64 denominator = 0;
        long double ans = 0;
        forn(i, n) {
            numerator -= order[i].fi * order[i].se;
            denominator += order[i].se;
            if (i + 1 >= minn) {
                long double nnew = (long double)numerator / denominator;
                ans = max(ans, nnew);
            }
        }
        printf("%.10lf\n", (double)ans);
    }
}

