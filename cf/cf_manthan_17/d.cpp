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
const int maxlog = 18;

int timer = 1;
int t_in[3][maxn];
int t_out[3][maxn];
int jump[maxn][maxlog];
vi edges[3][maxn];
int h[maxn];
int parent[maxn];
int typ[maxn];

bool is_anc(int t, int u, int v) {
    return t_in[t][u] < t_in[t][v] && t_out[t][u] > t_out[t][v];
}

void dfs(int t, int v, int anc) {
    //printf("dfs %d %d %d\n", t, v, anc);
    h[v] = anc == -1 ? 0 : h[anc] + 1;
    t_in[t][v] = timer++;
    if (t == 2) {
       jump[v][0] = anc;
       fore(j, 1, maxlog - 1) {
           jump[v][j] = jump[v][j - 1] == -1 ? -1 : jump[jump[v][j - 1]][j - 1];
           //printf("jump[%d][%d] = %d\n", v, j, jump[v][j]);
       }
    }

    for (int u : edges[t][v]) {
        dfs(t, u, v);
    }
    t_out[t][v] = timer++;
}

int up(int x, int delta) {
    //printf("up x = %d delta = %d %d\n", x, delta, jump[x][1]);
    for (int j = maxlog - 1; j >= 0; j--)
        if (delta & (1 << j))
            x = jump[x][j];
    return x;
}

int lca(int x, int y) {
    //printf("lca x = %d y = %d\n", x, y);
    if (h[x] > h[y])
        swap(x, y);
    y = up(y, h[y] - h[x]);
    if (x == y)
        return x;
    //printf("y now = %d\n", y);
    for (int j = maxlog - 1; j >= 0; j--) {
        int x1 = jump[x][j];
        int y1 = jump[y][j];
        if (x1 != y1) {
            x = x1;
            y = y1;
        }
    }
    return jump[x][0];
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
    fore(i, 1, n) {
        scanf("%d%d", &parent[i], &typ[i]);
        if (typ[i] != -1) {
            edges[typ[i]][parent[i]].pb(i);
            edges[2][parent[i]].pb(i);
        }
    }
    forn(t, 3)
        fore(i, 1, n)
            if (t_in[t][i] == 0)
                dfs(t, i, -1);
    //printf("jump[5][1] = %d\n", jump[5][1]);
    //fore(i, 1, n)
      //  printf("h[%d] = %d\n", i, h[i]);
    int queries;
    scanf("%d", &queries);
    forn(q, queries) {
        int q_typ, u, v;
        scanf("%d%d%d", &q_typ, &u, &v);
        bool res;
        if (q_typ == 1) {
            res = is_anc(0, u, v);
        } else {
            //printf("typ[%d] = %d\n", u, typ[u]);
            if (typ[v] <= 0)
                res = false;
            else if (typ[u] != 0)
                res = is_anc(1, u, v);
            else {
                //printf("here");
                int l = lca(u, v);
                //cerr << l << endl;
               // printf("lca %d", l);
                res = l != -1 && (l == u || is_anc(0, l, u)) && is_anc(1, l, v);
            }
        }
        printf(res ? "YES\n" : "NO\n");
    }
}

