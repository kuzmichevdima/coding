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

typedef pair <i64, i64> frac;

const int maxn = 1e5+5;

int anc[maxn];
vi edges[maxn];
int sz[maxn];
int n;
frac dp[maxn][maxn];

i64 gcd(i64 a, i64 b) {
    return b == 0 ? a : gcd(b % a, a);
}

inline frac norm(frac f) {
    i64 g = gcd(f.fi, f.se);
    return mp(f.fi / g, f.se / g);
}

inline frac add(frac & a, frac & b) {
    return norm(mp(a.fi * b.se + a.se * b.fi, a.se * b.se));
}

void dfs(int v, int prev) {
    anc[v] = prev;
    sz[v] = 1;
    for (int u : edges[v]) {
        if (u != prev) {
            dfs(u, v);
            sz[v] += sz[u];
        }
    }
}

inline frac get_prob(int u, int v) {
    if (anc[v] == u)
        return norm(make_pair(n - sz[v], n));
    return norm(make_pair(sz[v], n));
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
        fore(i, 1, n)
            edges[i].clear();
        forn(j, n - 1) {
            int u, v;
            scanf("%d%d", &u, &v);
            edges[u].pb(v);
            edges[v].pb(u);
        }
        dfs(1, -1);
        int guess, k;
        scanf("%d%d", &guess, &k);
        if (k > guess) {
            printf("0/1\n");
            continue;
        }
        forn(i, guess) { 
            int u, v;
            scanf("%d%d", &u, &v);
            frac prob = get_prob(u, v);
            /*fore(correct, 0, i + 1) {
                dp[i][correct] = i == 0 ? prob : add(dp[i - 1][correct], prob);
            }*/
        }
        cout << dp[guess - 1][k].first << "/" << dp[guess - 1][k].second << endl;
    }
}
