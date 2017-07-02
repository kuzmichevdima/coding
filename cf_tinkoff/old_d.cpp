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

const int maxn = 85;
const int inf = 1e9;

int dp[maxn][maxn][maxn][2];
vector <pii> edges[maxn];

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
                forn(flag, 2)
                    dp[done][L][R][flag] = inf;
    forn(i, m) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        //printf("edge %d %d %d\n", u, v, w);
        if (u == v)
            continue;
        edges[u].pb(mp(v, w));
        if (u < v)
            dp[2][u][v][0] = w;
        else dp[2][v][u][1] = w; 
    }
    fore(done, 3, k)
        fore(L, 1, n)
            fore(R, L + 1, n)
                forn(flag, 2) {
                    int val = inf;
                    int cur = flag ? R : L;
                    for (pii edge : edges[cur]) {
                        int mid = edge.fi;
                        if (mid <= L || mid >= R)
                            continue;
                        int nnew = min(dp[done - 1][L][mid][1], dp[done - 1][mid][R][0]);
                        if (nnew != inf)
                            val = min(val, nnew + edge.se);
                    }
                    dp[done][L][R][flag] = val;
                    if (val != inf)
                        printf("dp[%d][%d][%d][%d] = %d\n", done, L, R, flag, dp[done][L][R][flag]);
                }
    int ans = inf;
    fore(L, 1, n)
        fore(R, L + 1, n)
            forn(flag, 2)
                ans = min(ans, dp[k][L][R][flag]);
    if (ans == inf)
        ans = -1;
    printf("%d", ans);
}
