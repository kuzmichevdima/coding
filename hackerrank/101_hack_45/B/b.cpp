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

const int maxn = 105;
const int inf = 1e9;

int dp[maxn][maxn][maxn];

void upd(int & x, int y) {
    x = min(x, y);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#endif
    int n, k;
    scanf("%d%d", &n, &k);
    if (k > n) {
        printf("-1");
        exit(0);
    }
    forn(i, k + 1)
        forn(j, n + 1)
            forn(h, n + 1)
                dp[i][j][h] = inf;
    dp[1][1][1] = 0;
    fore(layer, 1, k - 1)
        fore(total, layer, n)
            fore(last, 1, total) if (dp[layer][total][last] != inf) {
                int limit = n - total;
                if (layer == k - 1)
                    limit = min(limit, 1);
                fore(next, 1, limit) {
                    upd(dp[layer + 1][total + next][next], dp[layer][total][last] + last * next);
                }
            }
    int ans = inf;
    fore(last, 1, n)
        ans = min(ans, dp[k][n][last]);
    printf("%d", ans == inf ? -1 : ans);
}
