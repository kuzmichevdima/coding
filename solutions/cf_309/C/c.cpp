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

struct Edge
{
    int a, b, c;
};

const int maxn = 1e5+5;
const int MOD = 1e9+7;

Edge e[maxn];
vi edges[2][maxn];
int color[maxn];
int comp[maxn];
int color_cnt, comp_cnt;
vi color_edges[maxn];
int mark_color[maxn];
int st_place[maxn];

void dfs_color(int v)
{
    color[v] = color_cnt;
    for (int u : edges[1][v])
    {
        if (color[u] == 0)
            dfs_color(u);
    }
}

void dfs_check0(int v, int cur)
{
    mark_color[v] = cur;
    for (int u : color_edges[v])
    {
//        printf("v = %d u = %d\n", v, u);
        if (mark_color[u] == 0)
            dfs_check0(u, 3 - cur);
        else if (mark_color[u] == mark_color[v])
        {
            printf("0");
            exit(0);
        }
    }
}

void dfs_comp(int v, int prev_color)
{
    comp[v] = comp_cnt;
  //  printf("dfs_comp %d comp[%d] = %d prev_color = %d\n", v, v, comp[v], prev_color);
    for (int u : edges[1][v])
    {
        if (comp[u] == 0)
            dfs_comp(u, prev_color);
    }
    for (int u : edges[0][v])
    {
//        printf("v = %d u = %d color[%d] = %d color[%d] = %d\n", v, u, v, color[v], u, color[u]);
        if (comp[u] == 0)
            dfs_comp(u, color[v]);
        /*else if (comp[u] == comp[v] && color[u] != prev_color && color[u] != color[v])
        {
            printf("0");
            exit(0);
        }*/
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
    int n, m;
    scanf("%d%d", &n, &m);
    forn(j, m)
    {
        scanf("%d%d%d", &e[j].a, &e[j].b, &e[j].c);
        edges[e[j].c][e[j].a].pb(e[j].b);
        edges[e[j].c][e[j].b].pb(e[j].a);
    }
    color_cnt = 0;
    fore(j, 1, n) if (color[j] == 0)
    {
        color_cnt++;
        dfs_color(j);
    }
//    fore(j, 1, n)
  //      printf("color[%d] = %d\n", j, color[j]);
    forn(j, m) if (e[j].c == 0)
    {
        int ca = color[e[j].a];
        int cb = color[e[j].b];
        if (ca == cb)
        {
            printf("0");
            exit(0);
        }
        if (ca != cb)
        {
            color_edges[ca].pb(cb);
            color_edges[cb].pb(ca);
//            printf("add color edge %d %d\n", ca, cb);
        }
    }
    fore(j, 1, color_cnt) if (mark_color[j] == 0)
        dfs_check0(j, 1);
    comp_cnt = 0;
    fore(j, 1, n) if (comp[j] == 0)
    {
        comp_cnt++;   
        dfs_comp(j, -1);
    }
    int ans = 1;
    forn(j, comp_cnt - 1)
        ans = (ans * 2) % MOD;
    printf("%d", ans);
}
