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

const int maxn = 2e5+5;
const int inf = 1e9;
const int MOD = 1e9+7;

int d[maxn];
pii best;
vi edges[maxn];

void calc_d(int v, int anc) {
    d[v] = 0;
    for (int u : edges[v]) {
        if (u != anc) {
            calc_d(u, v);
            d[v] = max(d[v], d[u] + 1);
        }
    }
}

void dfs(int v, int anc, int upper) {
    int cur = max(upper, d[v]);
//    printf("v = %d anc = %d upper = %d\n", v, anc, upper);
    if (edges[v].size() <= 2) {
        best = min(best, mp(cur, v));
    }
    for (int u : edges[v]) {
        if (u == anc)
            continue;
        int max_apart = -100;
        for (int w : edges[v])
            if (w != anc && w != u)
                max_apart = max(max_apart, d[w]);
        int new_upper = max(upper + 1, max_apart + 2);
        dfs(u, v, new_upper);
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
        fore(i, 1, n)
            edges[i].clear();
        forn(j, n - 1) {
            int u, v;
            scanf("%d%d", &u, &v);
            edges[u].pb(v);
            edges[v].pb(u);
        }
        bool fail = false;
        fore(i, 1, n)
            if (edges[i].size() > 3) {
                fail = true;
                break;
            }
        if (fail) {
            printf("-1\n");
            continue;
        }
        calc_d(1, -1);
        //fore(i, 1, n)
        //    printf("d[%d] = %d\n", i, d[i]);
        best = mp(inf, -1);
        dfs(1, -1, 0);
//        printf("best = %d %d\n", best.fi, best.se);
        if (best.se == -1)
            printf("-1\n");
        else {
            int total = 1;
            forn(j, best.fi + 1)
                total = 2 * total % MOD;
            total = (total - 1 - n + MOD) % MOD;
            printf("%d %d\n", best.se, total);
        }
        /*int v = find_far(1);
        int tmp = find_far(v);
        int total = 1;
        int depth = (d[tmp] + 1) / 2;
        forn(j, depth)
            total = (2 * total) % MOD;
        total = (total - n + MOD) % MOD;
        fore(chosen, 1, n) if (d[chosen] == d[tmp] / 2) {
            printf("%d %d\n", chosen, total);
            break;
        }*/
    }
}
