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

const int maxn = 1e5 + 5;
const int inf = 1e9;

vi edges[maxn];
int dp[maxn][2][3];

void dfs(int v, int anc = -1) {
    int cnt = 0;
    for (int u : edges[v]) {
        if (u == anc)
            continue;
        cnt++;
        dfs(u, v);
    }
    fore(here, 0, 1)
        fore(kids, 1 - here, min(cnt, 2)) {
            int sum = 0;
            int minn1 = inf;
            int minn2 = inf;
            for (int u : edges[v]) {
                if (u == anc)
                    continue;
                int optimal = inf;
                int required;
                fore(x, 0, 1) {
                    int need = 2 - here - x;
                    optimal = min(optimal, dp[u][x][need]);
                    if (x == 1) {
                        required = dp[u][x][need];
                    }
                }
                if (optimal == inf)
                    continue;
                sum += optimal;
                if (required == inf)
                    continue;
                int delta = -optimal + required;
                if (delta < minn1) {
                    minn2 = minn1;
                    minn1 = delta;
                } else if (delta < minn2) {
                    minn2 = delta;
                }
            }
            printf("v = %d here = %d kids = %d minn1 = %d minn2 = %d\n", v, here, kids, minn1, minn2);
            if (kids > 0) {
                if (minn1 == inf)
                    continue;
                sum += minn1;
                if (kids > 1) {
                    if (minn2 == inf)
                        continue;
                    sum += minn2;
                }
            }
            sum += here;
            dp[v][here][kids] = sum;
        }
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
        int n;
        scanf("%d", &n);
        fore(j, 1, n) {
            edges[j].clear();
            fore(q, 0, 1)
                fore(w, 0, 2)
                    dp[j][q][w] = inf;
        }
        forn(j, n - 1) {
            int x, y;
            scanf("%d%d", &x, &y);
            edges[x].pb(y);
            edges[y].pb(x);
        }
        dfs(1);
        printf("dp[3][0][2] = %d\n", dp[3][0][2]);
        int ans = inf;
        fore(in_root, 0, 1)
            fore(kids, 2 - in_root, 2)
                ans = min(ans, dp[1][in_root][kids]);
        if (ans == inf)
            ans = -1;
        printf("%d\n", ans);
    }
}

