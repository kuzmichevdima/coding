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

#define LOWER 0
#define SELECTED 1
#define UPPER 2

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)

const int max_avail = 12;
const int maxn = 1e5+5;
const int MOD = 1e9+7;

typedef int myarr[3][max_avail];
int var_for_typ[3];
myarr dp[maxn];
myarr nnew, current;
vi edges[maxn];
int avail;
vi lst[3];

inline void add(int& x, int y) {
    //printf("add %d\n", y);
    x += y;
    if (x >= MOD)
        x -= MOD;
}

void dfs(int v, int anc) {
    for (int u : edges[v]) {
        if (u != anc)
            dfs(u, v);
    }
    memset(current, 0, sizeof(current));
    forn(typ, 3)
        current[typ][typ == SELECTED] = var_for_typ[typ];
    for (int u : edges[v]) {
        if (u == anc)
            continue;
        //printf("before v = %d u = %d\n", v, u);
       /* forn(typ, 3)
            fore(used, 0, avail)
                printf("current[%d][%d] = %d\n", typ, used, current[typ][used]);*/
        memset(nnew, 0, sizeof(nnew));
        forn(typ, 3) {
            fore(used, 0, avail)
                for (int u_typ : lst[typ])
                    if (dp[u][u_typ][used]) {
                        //printf("v = %d (typ = %d) u = %d u_typ = %d used = %d\n", v, typ, u, u_typ, used);
                        fore(prev, 0, avail - used) {
                          //  printf("current[%d][%d] = %d\n", typ, prev, current[typ][prev]);
                            add(nnew[typ][used + prev], (i64)current[typ][prev] * dp[u][u_typ][used] % MOD);
                        }
                    }
        }
        memcpy(current, nnew, sizeof(nnew));
    }
    memcpy(dp[v], current, sizeof(current));
    /*forn(typ, 3)
        fore(used, 0, avail)
            printf("dp[%d][%d][%d] = %d\n", v, typ, used, dp[v][typ][used]);*/
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, m;
    scanf("%d%d", &n, &m);
    forn(i, n - 1) {
        int x, y;
        scanf("%d%d", &x, &y);
        edges[x].pb(y);
        edges[y].pb(x);
    }
    int sel_color;
    scanf("%d%d", &sel_color, &avail);
    var_for_typ[LOWER] = sel_color - 1;
    var_for_typ[SELECTED] = 1;
    var_for_typ[UPPER] = m - sel_color;
    lst[LOWER] = {LOWER, SELECTED, UPPER};
    lst[SELECTED] = {LOWER};
    lst[UPPER] = {LOWER, UPPER};
    dfs(1, -1);
    int ans = 0;
    forn(typ, 3)
        fore(used, 0, avail)
            add(ans, dp[1][typ][used]);
    printf("%d", ans);
}

