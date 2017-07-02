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

const int maxn = 1e6+5;

vi edges[maxn];
bool mark[maxn];
bool has_edges[maxn];

void dfs(int v) {
    mark[v] = true;
    for (int u : edges[v]) {
        if (!mark[u])
            dfs(u);
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
    int n, m;
    scanf("%d%d", &n, &m);
    i64 loops = 0;
    i64 non_loops = 0;
    forn(j, m) {
        int x, y;
        scanf("%d%d", &x, &y);
        has_edges[x] = true;
        has_edges[y] = true;
        if (x == y)
            loops++;
        else {
            edges[x].pb(y);
            edges[y].pb(x);
            non_loops++;
        }
    }
    fore(v, 1, n)
        if (has_edges[v]) {
            dfs(v);
            fore(j, 1, n)
                if (!mark[j] && has_edges[j]) {
                    printf("0");
                    exit(0);
                }
            break;
        }
    i64 ans = loops * (loops - 1) / 2 + loops * non_loops;
    fore(j, 1, n) {
        i64 x = edges[j].size();
        ans += x * (x - 1) / 2;
    }
    cout << ans;
}
