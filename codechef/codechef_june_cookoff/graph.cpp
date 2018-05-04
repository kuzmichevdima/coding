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

const int maxn = 105;

int n;
vi edges[maxn];
vi centroids;
int sz[maxn];

void dfs(int v, int anc = -1) {
    sz[v] = 1;
    bool ok = true;
    for (int u : edges[v]) {
        if (u != anc) {
            dfs(u, v);
            sz[v] += sz[u];
            if (sz[u] > n / 2)
                ok = false;
        }
    }
    if ((n - sz[v]) > n / 2)
        ok = false;
    if (ok)
        centroids.pb(v);
}

void add_edge(int x, int y) {
    edges[x].pb(y);
    edges[y].pb(x);
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
        int b;
        scanf("%d%d", &n, &b);
        if (b == 0 && n > 2) {
            printf("YES\n");
            fore(j, 2, n)
                printf("1 %d\n", j);
            continue;
        }
        bool found = false;
        forn(k, n / 2 + 1) {
            fore(v, 1, n)
                edges[v].clear();
            fore(v, 1, n - k - 1)
                add_edge(v, v + 1);
            fore(v, n - k + 1, n)
                add_edge(1, v);
            centroids.clear();
            dfs(1);
            int res;
            if (k != 0) {
                vi centers;
                int minn = n + 1;
                fore(j, 1, n - k) {
                    int cur = max(j, n - k - j);
                    if (cur < minn) {
                        minn = cur;
                        centers.clear();
                        centers.pb(j);
                    } else if (cur == minn)
                        centers.pb(j);
                }
                // printf("k = %d minn = %d\n", k, minn);
                for (int c : centroids) {
                    for (int cc : centers)
                        res = max(res, abs(c - cc));
                }
            }
             else {
                 if (n % 2 == 0)
                     res = 1;
                 else res = 0;
             }
            if (res == b) {
                found = true;
                printf("YES\n");
                fore(v, 1, n)
                    for (int u : edges[v])
                        if (u > v)
                            printf("%d %d\n", v, u);
                break;
            }
        }
        if (!found)
            printf("NO\n");
    }
}

