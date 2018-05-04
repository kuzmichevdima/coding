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

const int maxn = 1e5+5;

int a[maxn];

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
        int n, k;
        scanf("%d%d", &n, &k);
        forn(j, n)
            scanf("%d", &a[j]);
        i64 ans = -1e18;
        i64 cur_pref = 0;
        i64 min_pref = 0;
        i64 best_pref = 0;
        forn(i, n) {
            cur_pref += a[i];
            ans = max(ans, cur_pref - min_pref);
            min_pref = min(min_pref, cur_pref);
            best_pref = max(best_pref, cur_pref);
        }
        i64 cur_suff = 0;
        i64 best_suff = 0;
        for (int j = n - 1; j >= 0; --j) {
            cur_suff += a[j];
            best_suff = max(best_suff, cur_suff);
        }
        if (ans >= 0 && k >= 2)
            ans = max(ans, best_suff + best_pref + (cur_suff > 0 ? cur_suff * (k - 2) : 0));
        cout << ans << endl;
    }
}

