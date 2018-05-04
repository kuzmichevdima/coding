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

int timer, comp_cnt, color_cnt;
vi edges[maxn];
set <int> final_edges[maxn];
bool cutpoint[maxn];
int comp[maxn], color[maxn], up[maxn], tin[maxn];
int depth[maxn];
int jump[maxn][20];

void dfs(int v, int anc = -1) {
    up[v] = tin[v] = timer++;
    comp[v] = comp_cnt;
    int child_cnt = 0;
    for (int u : edges[v]) {
        if (u == anc)
            continue;
        if (comp[u] == 0) {
            dfs(u, v);
            child_cnt++;
            up[v] = min(up[v], up[u]);
        } else {
            up[v] = min(up[v], tin[u]);
        }
    }
    if (anc == -1)
        cutpoint[v] = child_cnt > 1;
    else {
        cutpoint[v] = false;
        for (int u : edges[v]) {
            if (u == anc)
                continue;
            if (up[u] >= tin[v]) {
                cutpoint[v] = true;
                break;
            }
        }
    }
}

void paint(int v) {
    color[v] = color_cnt;
    for (int u : edges[v]) {
        if (color[u] == 0 && cutpoint[u] == cutpoint[v])
            paint(u);
    }
}

void add_edge(int x, int y) {
    final_edges[x].insert(y);
    final_edges[y].insert(x);
}

void final_dfs(int v, int anc = -1) {
    depth[v] = anc == -1 ? 1 : depth[anc] + 1;
    jump[v][0] = anc;
    for (int u : final_edges[v]) {
        if (depth[u] == 0)
            final_dfs(u, v);
    }
}

inline int do_jump(int v, int len) {
    int cur = v;
    forn(j, 18)
        if (len & (1 << j))
            cur = jump[cur][j];
    return cur;
}

inline int get_sub(int fr, int to) {
    //printf("depth[%d] = %d depth[%d] = %d\n", fr, depth[fr], to, depth[to]);
    if (depth[fr] > depth[to]) {
        int tmp = do_jump(fr, depth[fr] - depth[to]);
        if (tmp == to)
            return do_jump(fr, depth[fr] - depth[to] - 1);
        else return -1;
    } else return -1;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    forn(j, m) {
        int x, y;
        scanf("%d%d", &x, &y);
        edges[x].pb(y);
        edges[y].pb(x);
    }
    fore(i, 1, n) {
        if (comp[i] == 0) {
            comp_cnt++;
            dfs(i);
        }
    }
    //fore(i, 1, n)
    //    printf("cutpoint[%d] = %d\n", i, cutpoint[i]);
    fore(i, 1, n)
        if (color[i] == 0) {
            color_cnt++;
            paint(i);
        }
    fore(i, 1, n)
       printf("color[%d] = %d\n", i, color[i]);
    fore(i, 1, n)
        for (int u : edges[i])
            if (color[i] != color[u])
                add_edge(color[i], color[u]);
    fore(i, 1, color_cnt)
        if (depth[i] == 0)
            final_dfs(i);
    fore(level, 1, 17)
        fore(i, 1, color_cnt)
            jump[i][level] = jump[i][level - 1] == -1 ? -1 : jump[jump[i][level - 1]][level - 1];
    forn(query, q) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        //assert(u !=v);
        bool answer = false;
        if (comp[u] == comp[v] && comp[u] == comp[w]) {
            if (u == v) {
                answer = (u == w);
            } else if (u == w || v == w) {
                answer = true;
            } else {
                u = color[u];
                v = color[v];
                w = color[w];
                //assert(u != w && v != w && u != v);
                if (u == w || v == w || (u == v && final_edges[u].find(w) != final_edges[u].end()))
                    answer = true;
                else {
                    int sub_u = get_sub(u, w);
                    int sub_v = get_sub(v, w);
                    //printf("u = %d v = %d w = %d sub_u = %d sub_v = %d\n", u, v, w, sub_u, sub_v);
                    //assert(sub_u == sub_v);
                    answer = (sub_u != sub_v);
                }
            }
        }
        if (answer)
            printf("YES\n");
        else printf("NO\n");
    }
}

