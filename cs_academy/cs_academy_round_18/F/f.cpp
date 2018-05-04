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

int c[maxn];
int h[maxn];
int ans[maxn];
vi edges[maxn];
int parent[maxn];

bool cmp_less(int u, int w, int v) {
    return (i64)(c[v] - c[u]) * (h[u] - h[w]) > (i64)(c[w] - c[u]) * (h[u] - h[v]);
}

void dfs(int u, int anc) {
//    printf("u = %d anc = %d\n", u, anc);
    h[u] = h[anc] + 1;
    if (u != 1) {
        ans[u] = ans[anc];
        int cur = anc;
        forn(it, 1000) {
            if (cmp_less(u, cur, ans[u]))
                ans[u] = cur;
            if (cur == 1)
                break;
            if (cmp_less(u, ans[cur], ans[u]))
                ans[u] = ans[cur];
            cur = parent[cur];
        }
        cur = anc;
        forn(it, 1000) {
            if (cmp_less(u, cur, ans[u]))
                ans[u] = cur;
            if (cur == 1)
                break;
            cur = ans[cur];
        }

    }
    for (int z : edges[u]) {
        dfs(z, u);
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
    int n;
    scanf("%d", &n);
    fore(i, 1, n) {
        scanf("%d", &c[i]);
    }
    fore(i, 2, n) {
        scanf("%d", &parent[i]);
        edges[parent[i]].pb(i);
    }
    ans[1] = 1;
    dfs(1, 0);
    fore(i, 2, n)
        printf("%d\n", ans[i]);
}
