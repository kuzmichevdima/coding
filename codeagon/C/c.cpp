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

const int maxn = 2e4+5;

vi edges[maxn];
vi rev_edges[maxn];
bool mark[maxn];

void dfs(int v) {
    mark[v] = true;
    for (int u : rev_edges[v])
        if (!mark[u])
            dfs(u);
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
        fore(i, 1, n) {
            edges[i].clear();
            rev_edges[i].clear();
            mark[i] = false;
        }
        fore(i, 1, n) {
            int num;
            scanf("%d", &num);
            forn(j, num) {
                int u;
                scanf("%d", &u);
                rev_edges[i].pb(u);
                edges[u].pb(i);
            }
        }
        forn(j, m) {
            int x;
            scanf("%d", &x);
            dfs(x);
        }
        //fore(i, 1, n)
        //    printf("mark[%d] = %d\n", i, mark[i]);
        vi deg(n + 1);
        fore(i, 1, n)
            deg[i] = rev_edges[i].size();
        set <int> order;
        fore(i, 1, n) if (mark[i] && deg[i] == 0) {
            order.insert(i);
        }
        vi ans;
        while(!order.empty()) {
            int cur = *order.begin();
            ans.pb(cur);
            order.erase(order.begin());
            for (int u : edges[cur]) {
                deg[u]--;
                if (deg[u] == 0 && mark[u]) {
                    order.insert(u);
                }
            }
        }
        printf("%d\n", (int)ans.size());
        for (int x : ans)
            printf("%d ", x);
        printf("\n");
    }

}
