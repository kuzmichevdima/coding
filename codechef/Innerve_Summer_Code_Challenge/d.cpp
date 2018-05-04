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

const int maxn = 15;
const int dx[4] = {-1, 0, 0, 1};
const int dy[4] = {0, 1, -1, 0};
const int inf = 1e9;

int a[maxn][maxn];
int b[maxn][maxn];
pii d[maxn][maxn];

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
        forn(i, n)
            forn(j, m)
                scanf("%d", &a[i][j]);
        forn(i, n)
            forn(j, m)
                scanf("%d", &b[i][j]);
        forn(i, n)
            forn(j, m)
                d[i][j] = mp(inf, inf);
        set<pair<pii, pii>> Q;
        d[0][0] = mp(a[0][0], b[0][0]);
        Q.insert(mp(d[0][0], mp(0, 0)));
        while(!Q.empty()) {
            auto fr = *Q.begin();
            Q.erase(Q.begin());
            pii p = fr.se;
            forn(move, 4) {
                int x = p.fi + dx[move];
                int y = p.se + dy[move];
                if (x >= 0 && y >= 0 && x < n && y < m) {
                    pii newd = d[p.fi][p.se];
                    newd.fi += a[x][y];
                    newd.se += b[x][y];
                    if (newd < d[x][y]) {
                        d[x][y] = newd;
                        Q.insert(mp(newd, mp(x, y)));
                    }
                }
            }
        }
        printf("%d %d\n", d[n - 1][m - 1].fi, d[n - 1][m - 1].se);
    }
}

