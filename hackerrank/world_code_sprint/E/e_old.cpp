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

const int maxn = 5e4+5;
const i64 inf = 2e18;

vi edges[maxn];
int c[maxn];
i64 sum[maxn];
int T;
int in[maxn];
int out[maxn];

void dfs(int v, int anc) {
    in[v] = T++;
    sum[v] = c[v];
    for (int u : edges[v]) {
        if (u == anc)
            continue;
        dfs(u, v);
        sum[v] += sum[u];
    }
    out[v] = T++;
}

inline void check(i64 fr, i64 to, i64 & ans) {
    if (to - fr >= 0)
        ans = min(ans, to - fr);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int q;
    scanf("%d", &q);
    forn(query, q) {
        int n;
        scanf("%d", &n);
        assert(n <= 2000);
        fore(i, 1, n) {
            scanf("%d", &c[i]);
            edges[i].clear();
        }
        forn(i, n - 1) {
            int u, v;
            scanf("%d%d", &v, &u);
            edges[u].pb(v);
            edges[v].pb(u);
        }
        T = 0;
        dfs(1, -1);
        i64 total = sum[1];
        i64 ans = inf;
        fore(v, 1, n)
            fore(u, 1, n) if (in[v] < in[u]) {
                if (out[v] > out[u]) {
                    if (sum[u] * 2 == sum[v])
                        check(total - sum[v], sum[u], ans);
                    if (sum[u] == 2 * sum[v] - total)
                        check(sum[u], total - sum[v], ans);
                    if (sum[u] == total - sum[v])
                        check(sum[v] - sum[u], sum[u], ans);
                } else {
                    if (sum[u] == sum[v])
                        check(total - sum[u] - sum[v], sum[v], ans);
                    if (sum[v] == total - sum[v] - sum[u])
                        check(sum[u], sum[v], ans);
                    if (sum[u] == total - sum[v] - sum[u])
                        check(sum[v], sum[u], ans);
                }
            }
        if (ans == inf)
            ans = -1;
        cout << ans << endl;
    }
}
