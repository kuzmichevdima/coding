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

//const int limit = 100;
const int max_val = 1305;
const int maxn = 55;

int dp[maxn][max_val + 5][max_val + 5];
int cont[max_val + 5][max_val + 5];
int a[maxn];
const int mod = 1e9+7;

inline void upd(int& x, int y) {
    x += y;
    if (x >= mod)
        x -= mod;
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
    fore(sum, 0, max_val)
        fore(first, 0, min(sum, max_val)) {
            int second = sum - first;
            cont[first][second] = 1;
            fore(minus, 1, min(first, second))
                upd(cont[first][second], cont[second - minus][minus]);
        }
    forn(test, tests) {
        int n;
        scanf("%d", &n);
        forn(i, n)
            scanf("%d", &a[i]);
        if (n == 1) {
            printf("1\n");
            continue;
        }
        memset(dp, 0, sizeof(dp));
        dp[0][a[0]][a[1]] = 1;
        fore(i, 0, n - 3)
            fore(first, 0, max_val)
                fore(second, 0, max_val) if (dp[i][first][second]) {
                    //printf("dp[%d][%d][%d] = %d\n", i, first, second, dp[i][first][second]);
                    fore(j, 0, min(first, second)) {
                        //int next = (i + 2 < n ? a[i + 2] : 0) + j;
                        int next = a[i + 2] + j;
                        //if (next == 0 && i + 2 >= n)
                        //    upd(ans, dp[i][first][second]);
                        //else
                        upd(dp[i + 1][second - j][next], dp[i][first][second]);
                    }
                }
        int ans = 0;
        fore(first, 0, max_val)
            fore(second, 0, max_val) if (dp[n - 2][first][second]) {
                //printf("first = %d second = %d dp = %d cont = %d\n", first, second, dp[n - 2][first][second], cont[first][second]);
                int to_add = (i64)dp[n - 2][first][second] * cont[first][second] % mod;
                upd(ans, to_add);
            }
        printf("%d\n", ans); 
    }
}

