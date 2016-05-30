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

int p[maxn];
int rg[maxn];
int cur;
bool mark[maxn];
pii e[maxn];
int ans[maxn];
int q[maxn];

int find_set(int x) {
    return p[x] == x ? x : p[x] = find_set(p[x]);
}

void add_edge(int num) {
    int v = find_set(e[num].fi);
    int u = find_set(e[num].se);
    if (v != u) {
        cur--;
        if (rg[v] > rg[u]) {
            p[u] = v;
            rg[v] += rg[u];
        } else {
            p[v] = u;
            rg[u] += rg[v];
        }
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
    int n, m, Q;
    scanf("%d%d", &n, &m);
    fore(j, 1, m) {
        scanf("%d%d", &e[j].fi, &e[j].se);
    }
    scanf("%d", &Q);
    forn(j, Q) {
        scanf("%d", &q[j]);
        mark[q[j]] = true;
    }
    fore(j, 1, n) {
        p[j] = j;
        rg[j] = 1;
    }
    cur = n;
    fore(j, 1, m)
        if (!mark[j]) {
            add_edge(j);
        }
    for (int j = Q - 1; j >= 0; j--) {
        ans[j] = cur;
        add_edge(q[j]);
    }
    forn(j, Q)
        printf("%d ", ans[j]);
}
