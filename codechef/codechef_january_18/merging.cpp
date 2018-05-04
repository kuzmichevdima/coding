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
const int inf = 1e9;

int dp[maxn][maxn][2];

inline void upd(int& x, int y) {
    x = min(x, y);
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
        int n, m;
        scanf("%d%d", &n, &m);
        string s, t;
        cin >> s >> t;
        fore(i, 0, n + 1)
            fore(j, 0, m + 1)
                dp[i][j][0] = dp[i][j][1] = inf;
        dp[1][0][0] = 1;
        dp[0][1][1] = 1;
        fore(i, 0, n)
            fore(j, 0, m)
                forn(last, 2) if (dp[i][j][last] != inf) {
                    //printf("dp[%d][%d][%d] = %d\n", i, j, last, dp[i][j][last]);
                    char symb = last == 0 ? s[i - 1] : t[j - 1];
                    if (i != n) {
                        upd(dp[i + 1][j][0], dp[i][j][last] + (symb != s[i]));
                    }
                    if (j != m) {
                        upd(dp[i][j + 1][1], dp[i][j][last] + (symb != t[j]));
                    }
                }
        printf("%d\n", min(dp[n][m][0], dp[n][m][1]));
    }
}

