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

vi edges[maxn];
int game[maxn];

void dfs(int v, int anc) {
    vi list;
    int total = 0;
    for (int u : edges[v]) {
        if (u == anc)
            continue;
        dfs(u, v);
        total = total ^ game[u];
        list.pb(game[u]);
    }
    set <int> values;
    for (int x : list)
        values.insert(x ^ total);
    game[v] = 0;
    while(values.count(game[v]) > 0) {
        game[v]++;
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
    forn(j, n - 1) {
        int x, y;
        scanf("%d%d", &x, &y);
        edges[x].pb(y);
        edges[y].pb(x);
    }
    dfs(1, -1);
    fore(j, 1, n)
        printf("game[%d] = %d\n", j, game[j]);
    printf(game[1] == 0 ? "Bob" : "Alice");
}

