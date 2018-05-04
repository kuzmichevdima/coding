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

const int maxn = 1e5+5;
const i64 inf = 1e18;

int h[maxn];
int one, two, three;
vi edges[maxn];
int in[maxn];
int out[maxn];
int timer = 0;
i64 ans;
int v[3];
int n;

void dfs(int v, int anc) {
    in[v] = timer++;
    h[v] = anc == -1 ? 0 : h[anc] + 1;
    for (int u : edges[v]) {
        if (u == anc)
            continue;
        dfs(u, v);
    }
    out[v] = timer++;
}


bool is_anc(int v, int u) {
    return in[v] <= in[u] && out[v] >= out[u];
}

int get_lca(int x, int y) {
    int result = -1;
    fore(v, 1, n)
        if (is_anc(v, x) && is_anc(v, y) && (result == -1 || h[v] > h[result]))
            result = v;
    return result;
}


inline void upd(int x, int y, int z) {
    i64 nnew = (i64)one * x + (i64)two * y + (i64)three * z;
    ans = min(ans, nnew);
}

void case2(int first, int second, int third) {
    first = v[first];
    second = v[second];
    third = v[third];
    int lca = get_lca(first, second);
    upd(h[third] + (h[first] - h[lca]) + (h[second] - h[lca]), h[lca], 0);
    upd(h[third] + h[lca] + (h[first] - h[lca]) + (h[second] - h[lca]), 0, h[lca]);
}




void case3(int first, int second, int third) {
    first = v[first];
    second = v[second];
    third = v[third];
    int lca12 = get_lca(first, second);
    int tmp = h[first] - h[lca12] + h[second] - h[lca12];
    int lca123 = get_lca(lca12, third);
    //printf("case3 %d %d %d lca12 = %d lca123 = %d\n", first, second, third, lca12, lca123);
    upd(h[third] - h[lca123] + tmp, h[lca12] - h[lca123], h[lca123]);
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
        scanf("%d", &n);
        scanf("%d%d%d", &one, &two, &three);
        two = min(two, 2 * one);
        three = min(three, 3 * one);
        three = min(three, one + two);
        forn(j, 3)
            scanf("%d", &v[j]);
        fore(j, 1, n)
            edges[j].clear();
        forn(j, n - 1) {
            int u, v;
            scanf("%d%d", &u, &v);
            edges[u].pb(v);
            edges[v].pb(u);
        }
        dfs(1, -1);
        //fore(j, 1, n)
          //  printf("h[%d] = %d\n", j, h[j]);
        ans = inf;
        upd(h[v[0]] + h[v[1]] + h[v[2]], 0, 0);
        //forn(j, 3)
          //  printf("v[%d] = %d h = %d\n", j, v[j], h[v[j]]);
        case2(0, 1, 2);
        case2(0, 2, 1);
        case2(1, 2, 0);

        case3(0, 1, 2);
        case3(0, 2, 1);
        case3(1, 2, 0);
        cout << ans << endl;
    }
}

