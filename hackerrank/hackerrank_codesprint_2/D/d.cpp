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

typedef pair <i64, i64> fraction;

const int maxn = 1e5+5;

int anc[maxn];
vi edges[maxn];
int n, k;
int ans = 0;
set <int> guess[maxn];

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

void calc(int v, int cur) {
    if (cur >= k)
        ans++;
    for (int u : edges[v]) {
        if (u != anc[v]) {
            int nnew = cur;
            if (guess[u].find(v) != guess[u].end())
                nnew--;
            if (guess[v].find(u) != guess[v].end())
                nnew++;
            calc(u, nnew);
        }
    }
}

int dfs(int v, int prev) {
    anc[v] = prev;
    int result = guess[v].find(prev) != guess[v].end();
    for (int u : edges[v]) {
        if (u != prev) {
            result += dfs(u, v);
        }
    }
    return result;
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
        int g;
        scanf("%d%d", &g, &k);
        fore(j, 1, n)
            guess[j].clear();
        forn(j, g) {
            int u, v;
            scanf("%d%d", &u, &v);
    //        printf("guess parent of %d is %d\n", v, u);
            guess[v].insert(u);
        }
        int start = dfs(1, -1);
      //  printf("start = %d\n", start);
        ans = 0;
        calc(1, start);
        int gc = gcd(ans, n);
        printf("%d/%d\n", ans / gc, n / gc);
    }
}
