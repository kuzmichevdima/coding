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

const int maxn = 5005;
const i64 inf = 1e18;

i64 dp[maxn][maxn];
int x[maxn];
int w[maxn];
i64 prec[maxn][maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, k;
    scanf("%d%d", &n, &k);
    forn(j, n)
        scanf("%d%d", &x[j], &w[j]);
    fore(i, 0, n + 1)
        fore(j, 0, k)
            dp[i][j] = inf;
    fore(i, 0, n - 1)
        fore(j, i, n - 1) {
            prec[i][j] = prec[i][j - 1] + w[j];
        }
    dp[0][0] = 0;
    forn(used, k) {
        int optimal = 0;
        forn(covered, n) {
            i64 cur = 0;
            fore(last, covered, n - 1) {
                cur += (i64)(x[last] - x[optimal]) * w[last];
                while(optimal < last) {
                    i64 delta = (prec[covered][optimal] - prec[optimal + 1][last]) * (x[optimal + 1] - x[optimal]);
                    if (delta < 0) {
                        cur += delta;
                        optimal++;
                    } else break;
                }
                fore(used, 0, k - 1) if (dp[covered][used] != inf) {
    //                printf("upd %d %d with  %lld\n", last + 1, used + 1, cur + dp[covered][used]);
                    dp[last + 1][used + 1] = min(dp[last + 1][used + 1], cur + dp[covered][used]);
                }

            }
        }
    }
    cout << dp[n][k];
}
