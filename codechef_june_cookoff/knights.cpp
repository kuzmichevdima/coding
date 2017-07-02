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

const int maxm = 55;
const int inf = 1e9;

int dp[maxm][8][8][8][8];

inline void upd(int & x, int y) {
    x = min(x, y);
}
int n;

void norm(int & x) {
    if ((n == 2) && (x & 4))
        x ^= 4;
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
        int m;
        scanf("%d%d", &n, &m);
        if (n > m)
            swap(n, m);
        if (n == 1) {
            printf("%d\n", m);
            continue;
        }
        forn(col, m + 1)
            forn(i, (1 << n))
                forn(j, (1 << n))
                    forn(k, (1 << n))
                        forn(h, (1 << n))
                            dp[col][i][j][k][h] = inf;
        dp[0][0][0][0][0] = 0;
        for (int col = 0; col < m; ++col)
            for (int prev = 0; prev < (1 << n); ++prev)
                for (int last = 0; last < (1 << n); ++last)
                    for (int cur = 0; cur < (1 << n); ++cur)
                        for (int next = 0; next < (1 << n); ++next) {
                            if (dp[col][prev][last][cur][next] == inf)
                                continue;
                            //printf("col = %d prev = %d last = %d cur = %d next =%d value = %d\n", col, prev, last, cur, next, dp[col][prev][last][cur][next]);
                            forn(prof, (1 << n)) {
                                int prev1 = prev;
                                int last1 = last;
                                int cur1 = cur | prof;
                                int next1 = next;
                                int new1 = 0;
                                int addit = 0;
                                if (prof & 1) {
                                    addit++;
                                    prev1 |= 2;
                                    last1 |= 4;
                                    next1 |= 4;
                                    new1 |= 2;
                                }
                                if (prof & 2) {
                                    addit++;
                                    prev1 |= 5;
                                    new1 |= 5;
                                }
                                if (prof & 4) {
                                    addit++;
                                    prev1 |= 2;
                                    last1 |= 1;
                                    next1 |= 1;
                                    new1 |= 2;
                                }
                                //if (prev == 0 && last == 0 && cur == 0 && next == 0)
                                //    printf("prof = %d prev1 = %d last1 = %d cur1 = %d next1 = %d new1 = %d\n", prof, prev1, last1, cur1, next1, new1);
                                norm(prev1);
                                norm(last1);
                                norm(cur1);
                                norm(next1);
                                norm(new1);
                                //assert(prev1 < (1 << n) && last1 < (1 << n) && cur1 < (1 << n) && next1 < (1 << n) && new1 < (1 << n));
                                if (col >= 2 && prev1 != (1 << n) - 1)
                                    continue;
                                upd(dp[col + 1][last1][cur1][next1][new1],
                                        dp[col][prev][last][cur][next] + addit);
                            }
                }
        int ans = inf;
        forn(i, (1 << n))
            forn(j, (1 << n))
                upd(ans, dp[m][(1 << n) - 1][(1 << n) - 1][i][j]);
        printf("%d\n", ans);
    }
}

