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

const int maxn = 3005;

set <pii> far_in[maxn];
set <pii> far_out[maxn];
vi edges[maxn];
int d[maxn][maxn];
int n;

void precalc() {
    fore(i, 1, n)
        fore(j, 1, n)
            d[i][j] = -1;
    fore(i, 1, n) {
        queue <int> Q;
        Q.push(i);
        d[i][i] = 0;
        while(!Q.empty()) {
            int v = Q.front();
            Q.pop();
            for (int u : edges[v]) {
                if (d[i][u] == -1) {
                    d[i][u] = d[i][v] + 1;
                    Q.push(u);
                }
            }
        }
    }
    fore(i, 1, n) 
        fore(j, 1, n) if (i != j && d[i][j] != -1) {
            far_out[i].insert(mp(d[i][j], j));
            if (far_out[i].size() == 4) {
                far_out[i].erase(far_out[i].begin());
            }

            far_in[j].insert(mp(d[i][j], i));
            if (far_in[j].size() == 4) {
                far_in[j].erase(far_in[j].begin());
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
    int m;
    scanf("%d%d", &n, &m);
    forn(j, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        edges[u].pb(v);
    }
    precalc();
    pair <pii, pii> ans;
    int best = 0;
    fore(i, 1, n)
        fore(j, 1, n) if (i != j && d[i][j] != -1) {
            for (pii v1 : far_out[j]) {
                int v = v1.se;
                if (v == i)
                    continue;
                for (pii u1 : far_in[i]) {
                    int u = u1.se;
                    if (u == j || u == v)
                        continue;
                    int nnew = d[i][j] + v1.fi + u1.fi;
                    //if (nnew == 13)
                    //    printf("i = %d j = %d v1 = %d %d u1 = %d %d nnew = %d\n", i, j, v1.fi, v1.se, u1.fi, u1.se, nnew);
                    if (nnew > best) {
                        best = nnew;
                        ans = mp(mp(u, i), mp(j, v));
                    }
                }
            }
        }
//    printf("%d\n", best);
    printf("%d %d %d %d\n", ans.fi.fi, ans.fi.se, ans.se.fi, ans.se.se);
}
