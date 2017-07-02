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

const int maxn = 82;
const int inf = 1e9;

int dp[maxn][maxn][maxn][maxn];
vector <pii> edges[maxn];

inline void upd(int & x, int y) {
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
    int n, k, m;
    scanf("%d%d%d", &n, &k, &m);
    if (k > n) {
        printf("-1");
        exit(0);
    }
    if (k == 1) {
        printf("0");
        exit(0);
    }
    forn(done, k + 1)
        forn(L, n + 1)
            forn(R, n + 1)
                forn(cur, n + 1)
                    dp[done][L][R][cur] = inf;
    forn(i, m) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        //printf("edge %d %d %d\n", u, v, w);
        if (u == v)
            continue;
        edges[u].pb(mp(v, w));
        if (u < v) {
            fore(L, 1, u)
                fore(R, v, n)
                    upd(dp[2][L][R][u], w);
        }
        else {
            fore(L, 1, v)
               fore(R, u, n)
                upd(dp[2][L][R][u], w);
        }
    }
    fore(done, 3, k)
        fore(L, 1, n)
            fore(R, L + 1, n)
                fore(cur, L, R) {
                    int val = inf;
                    for (const pii & edge : edges[cur]) {
                        int mid = edge.fi;
                        if (mid < L || mid > R)
                            continue;
                        int L1, R1;
                        if (mid < cur) {
                            L1 = L;
                            R1 = cur - 1;
                        } else {
                            L1 = cur + 1;
                            R1 = R;
                        }
                        int nnew = dp[done - 1][L1][R1][mid];
                        val = min(val, nnew + edge.se);
                    }
                    dp[done][L][R][cur] = val;
                    //if (val != inf)
                    //    printf("dp[%d][%d][%d][%d] = %d\n", done, L, R, flag, dp[done][L][R][flag]);
                }
    int ans = inf;
    fore(L, 1, n)
        fore(R, L + 1, n)
            fore(cur, L, R)
                ans = min(ans, dp[k][L][R][cur]);
    if (ans == inf)
        ans = -1;
    printf("%d", ans);
}
