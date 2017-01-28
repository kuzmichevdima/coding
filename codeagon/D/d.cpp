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

const int MOD = 1e9+7;
const int maxn = 2005;

int dp[maxn][maxn];
int pref[maxn][maxn];
int sum[maxn];
int limit[maxn];

inline void add(int & x, int y) {
    x = (x + y) % MOD;
}

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
        int n, colors;
        scanf("%d%d", &n, &colors);
        forn(j, colors) {
            scanf("%d", &limit[j]);
        }
        if (colors == 1) {
            if (limit[0] < n)
                printf("0\n");
            else printf("1\n");
            continue;
        }
        memset(dp, 0, sizeof(dp));
        memset(pref, 0, sizeof(pref));
        memset(sum, 0, sizeof(sum));
        fore(pos, 0, n - 1) {
            forn(color, colors) {
                if (limit[color] > pos)
                    dp[pos][color] = 1;
                int to_add = pref[pos - 1][color];
                if (pos - limit[color] - 1 >= 0)
                    to_add = (to_add - pref[pos - limit[color] - 1][color] + MOD) % MOD;
                add(dp[pos][color], to_add);
            }
            sum[pos] = 0;
            forn(j, colors) {
                add(sum[pos], dp[pos][j]);
//                printf("dp[%d][%d] = %d\n", pos, j, dp[pos][j]);
            }
            forn(color, colors) {
                pref[pos][color] = pos == 0 ? 0 : pref[pos - 1][color];
                add(pref[pos][color], (sum[pos] - dp[pos][color] + MOD) % MOD);
            }
        }
        int ans = 0;
        forn(j, colors)
            add(ans, dp[n - 1][j]);
        printf("%d\n", ans);
    }
}
