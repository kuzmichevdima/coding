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

const int maxn = 2005;

int used[maxn];
int paired[maxn];
pii a[maxn];
pii b[maxn];
vi edges[maxn];
int code = 0;
//int perm[maxn];
bool valid[maxn];

bool dfs(int v) {
    used[v] = code;
    for (int u : edges[v]) {
        if (paired[u] == -1 || (used[paired[u]] != code && dfs(paired[u]))) {
            paired[u] = v;
            return true;
        }
    }
    return false;
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
        forn(i, n) {
            scanf("%d%d", &a[i].fi, &a[i].se);
        }
        forn(i, m) {
            scanf("%d%d", &b[i].fi, &b[i].se);
        }
        forn(i, m)
            paired[i] = -1;
        forn(i, n) {
            valid[i] =true;
            edges[i].clear();
            forn(j, m) {
                int dx = abs(a[i].fi - b[j].fi);
                int dy = abs(a[i].se - b[j].se);
                //if (dx == dy || (dx == 0 && dy % 2 == 0) || (dy == 0 && dx % 2 == 0))
                if (dx == dy || dx == 0 || dy == 0) {
                    edges[i].pb(j);
                    if (paired[j] == -1 && valid[i]) {
                        valid[i] = false;
                        paired[j] = i;
                    }
                }
            }
        }
        vector <pii> order(n);
        forn(i, n)
            order[i] = mp(edges[i].size(), i);
        sort(order.begin(), order.end());
        forn(i, n) {
            int v = order[i].se;
            if (!valid[v])
                continue;
            code++;
            dfs(v);
        }
        int ans = 0;
        forn(i, m)
            if (paired[i] != -1)
                ans++;
        printf("%d\n", ans);
    }
}
