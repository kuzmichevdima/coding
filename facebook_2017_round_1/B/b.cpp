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

const int maxk = 5005;
const int maxn = 105;

bool mark[maxk][2][2][maxn];
set <pii> dp[maxk][2][2];
vector <pii> edges[maxn];
int source[maxk];
int dest[maxk];

inline void upd(int cur, int flag1, int flag2, int v, int new_val) {
    if (mark[cur][flag1][flag2][v])
        return;
    //printf("upd cur = %d flag1 = %d flag2 = %d v = %d new_val = %d\n", cur, flag1, flag2, v, new_val);
    dp[cur][flag1][flag2].insert(mp(new_val, v));
}

int main() {
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        fprintf(stderr, "test %d\n", test);
        int n, m, k;
        scanf("%d%d%d", &n, &m, &k);
        fore(j, 1, n)
            edges[j].clear();
        forn(j, m) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            edges[u].pb(mp(v, w));
            edges[v].pb(mp(u, w));
        }
        forn(j, k) {
            scanf("%d%d", &source[j], &dest[j]);
            // printf("source[%d] = %d dest[%d] = %d\n", j, source[j], j, dest[j]);
        }
        forn(j, k + 1)
            forn(flag1, 2)
                forn(flag2, 2)
                    dp[j][flag1][flag2].clear();
        memset(mark, false, sizeof(mark));
        dp[0][0][0].insert(mp(0, 1));
        forn(cur, k)
            forn(flag1, 2)
                forn(flag2, 2) {
                    if (flag2 == 1 && flag1 == 0)
                        continue;
                    while(!dp[cur][flag1][flag2].empty()) {
                        pii p = *dp[cur][flag1][flag2].begin();
                        dp[cur][flag1][flag2].erase(dp[cur][flag1][flag2].begin());
                        int v = p.se;
                        if (mark[cur][flag1][flag2][v])
                            continue;
                        mark[cur][flag1][flag2][v] = true;
                        if (flag1 == 1 && v == dest[cur])
                            upd(cur + 1, flag2, 0, v, p.fi);
                        if (v == source[cur] && flag1 == 0)
                            upd(cur, 1, 0, v, p.fi);
                        if (cur + 1 < k && v == source[cur + 1] && flag1 == 1 && flag2 == 0)
                            upd(cur, 1, 1, v, p.fi);
                        for (pii e : edges[v]) {
                            upd(cur, flag1, flag2, e.fi, p.fi + e.se);
                        }
                    }
                }
        int ans = dp[k][0][0].empty() ? -1 : dp[k][0][0].begin()->first;
        printf("Case #%d: %d\n", test + 1, ans);
    }
}
