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

const int maxn = 2e5+5;
const int LOG = 18;

int tin[maxn];
int color[maxn];
int fup[maxn];
int comp_cnt, timer, compressed_comp_cnt;
vector <pii> edges[maxn];
vi tree_edges[maxn];
int p[maxn][LOG + 1];
int A[maxn];
int B[maxn];
int C[maxn];
int h[maxn];
int compressed_comp[maxn];

void calc_fup(int v, int prevEdge)
{
    timer++;
    fup[v] = tin[v] = timer;
    for (pii p : edges[v]) if (p.se != prevEdge)
    {
        int u = p.fi;
        //printf("edge from %d to %d\n", v, u);
        if (fup[u] == 0)
        {
            calc_fup(u, p.se);
            fup[v] = min(fup[v], fup[u]);
        }
        else fup[v] = min(fup[v], tin[u]);
    }
//    printf("fup[%d] = %d\n", v, fup[v]);
}

void paint(int v)
{
    color[v] = comp_cnt;   
    for (pii p : edges[v]) if (color[p.fi] == 0)
    {
        if (fup[p.fi] <= tin[v])
            paint(p.fi);
    }
}

void calc_p(int v, int anc, int curh)
{
    compressed_comp[v] = compressed_comp_cnt;
    h[v] = curh;
    p[v][0] = anc;
    fore(level, 1, LOG - 1)
        p[v][level] = p[p[v][level - 1]][level - 1];
    for (int u : tree_edges[v]) if (u != anc)
    {
        calc_p(u, v, curh + 1);       
    }
}

inline int get_lca(int x, int y)
{
    if (h[x] < h[y])
        swap(x, y);
    int diff = -h[y] + h[x];
    forn(level, LOG)
        if (diff & (1 << level))
            x = p[x][level];
    if (x == y)
        return x;
    for (int level = LOG - 1; level >= 0; level--)
    {
        int x1 = p[x][level];
        int y1 = p[y][level];
        if (x1 != y1)
        {
            x = x1;
            y = y1;
        }
    }
    return p[x][0];
}

void dfs(int v, int anc)
{
    for (int u : tree_edges[v]) if (u != anc)
    {
        dfs(u, v);
        A[v] += A[u];
        B[v] += B[u];
        C[v] += C[u];
    }
    bool flag1 = A[v] > C[v];
    bool flag2 = B[v] > C[v];
    if (flag1 && flag2)
    {
        printf("No");
        exit(0);
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
    scanf("%d%d%d", &n, &m, &Q);
    forn(j, m)
    {
        int u, v;
        scanf("%d%d", &v, &u);
        edges[v].pb(pii(u, j));
        edges[u].pb(pii(v, j));
    }
    fore(j, 1, n) if (fup[j] == 0)
        calc_fup(j, -1);
    fore(j, 1, n) if (color[j] == 0)
    {
        comp_cnt++;
        paint(j);
    }
//    fore(j, 1, n)
  //      printf("color[%d] = %d\n", j, color[j]);
//    int tree_edges_cnt = 0;
    fore(j, 1, n)
        for (pii p : edges[j]) if (color[j] != color[p.fi])
        {
            tree_edges[color[j]].pb(color[p.fi]);
  //          tree_edges_cnt++;
        }
    //assert(tree_edges_cnt / 2 == comp_cnt - 1);
    fore(j, 1, comp_cnt) if (compressed_comp[j] == 0)
    {
        compressed_comp_cnt++;
        calc_p(j, -1, 0);
    }
    forn(query, Q)
    {
        int fr, to;
        scanf("%d%d", &fr, &to);
        if (compressed_comp[color[fr]] != compressed_comp[color[to]])
        {
            printf("No");
            exit(0);
        }
        A[color[fr]]++;
        B[color[to]]++;
        int L = get_lca(color[fr], color[to]);
        C[L]++;
    }
    dfs(1, -1);
    printf("Yes");
}
