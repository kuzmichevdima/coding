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

const int maxh = 17;
const int maxn = 1e5+5;
const int inf = 1e9;

int prec[maxh + 5][maxn];
bool heavy[maxn];
int anc[maxn];
int sz[maxn];
vi list[maxn];
vi tree[maxn];
int wher[maxn];
int num_on_path[maxn];
int path_num[maxn];
set <int> in_vertex[maxn];
int path_cnt, n;
vi edges[maxn];
int h[maxn];

inline void precalc_lca()
{
    fore(j, 1, n)
        prec[0][j] = anc[j];
    fore(j, 1, maxh)
    {
        fore(i, 1, n)
            prec[j][i] = prec[j - 1][prec[j - 1][i]];
    }
}

inline int lca(int x, int y)
{
  //  printf("lca %d %d\n", x, y);
    if (h[x] < h[y])
        swap(x, y);
    int deltah = h[x] - h[y];
//    printf("deltah = %d\n", deltah);
    int j = 0;
    while((1 << j) <= deltah)
    {
        if ((1 << j) & deltah)
            x = prec[j][x];
        j++;
    }
//    printf("x = %d y = %d\n", x, y);
    assert(h[x] == h[y]);
    if (x == y)
        return x;
    for (int j = maxh; j >= 0; j--) if (h[x] >= (1 << j))
    {
        int x1 = prec[j][x];
        int y1 = prec[j][y];
    //    printf("j = %d x1 = %d y1 = %d\n", j, x1, y1);
        if (x1 != y1)
        {
            x = x1;
            y = y1;
        }
    }
//    printf("x = %d y = %d\n", x, y);
    assert(anc[x] == anc[y]);
    return anc[x];
}

void dfs(int v, int anc1, int curh)
{
    h[v] = curh;
    anc[v] = anc1;
    sz[v] = 1;
    for (int u : edges[v])
    {
        if (u == anc[v])
            continue;
        dfs(u, v, curh + 1);
        sz[v] += sz[u];
    }
    for (int u : edges[v])
    {
        if (u == anc[v])
            continue;
        heavy[u] = sz[u] * 2 >= sz[v];
    }

}

void get_paths()
{
    path_cnt = 0;
    fore(j, 1, n)
        path_num[j] = -1;
    vector <pii> order;
    fore(j, 1, n)
        order.pb(mp(h[j], j));
    sort(order.begin(), order.end());
    for (int i = n - 1; i >= 0; i--)
    {
        int j = order[i].se;
        if (path_num[j] != -1)
            continue;
        int cur = j;
        list[path_cnt].pb(j);
        while(cur != 1 && heavy[cur])
        {
            cur = anc[cur];   
            list[path_cnt].pb(cur);
        }
        int h = 0;
        for (int v : list[path_cnt])
        {
            path_num[v] = path_cnt;
            num_on_path[v] = h;
            h++;
        }
        path_cnt++;
    }

}

void build(int number, int i, int L, int R)
{
    if (L + 1 == R)
    {
        int v = list[number][L];
        tree[number][i] = (in_vertex[v].empty() ? inf : *in_vertex[v].begin());
        return;
    }
    int M = (L + R) / 2;
    build(number, i * 2, L, M);
    build(number, i * 2 + 1, M, R);
    tree[number][i] = min(tree[number][i * 2], tree[number][i * 2 + 1]);
}

inline int get(int number, int i, int L, int R, int A, int B)
{
    if (A >= R || L >= B)
        return inf;
    if (A == L && B == R)
        return tree[number][i];
    int M = (L + R) / 2;
    return min(get(number, i * 2, L, M, A, min(M, B)),
                get(number, i * 2 + 1, M, R, max(M, A), B));
}

inline int get_min_on_path(int lower, int upper)
{
    int cur = lower;
    int result = inf;
    while(cur != -1)
    {
        int p = path_num[cur], nnew;
        if (path_num[upper] == p)
            nnew = get(p, 1, 0, list[p].size(), num_on_path[cur], num_on_path[upper] + 1);
        else nnew = get(p, 1, 0, list[p].size(), num_on_path[cur], list[p].size());
        result = min(result, nnew);
        if (path_num[upper] == p)
            break;
        cur = anc[list[p].back()];
    }
    return result;
}

inline void upd(int number, int i, int L, int R, int pos)
{
    if (L + 1 == R)
    {
        int v = list[number][L];
        tree[number][i] = (in_vertex[v].empty() ? inf : *in_vertex[v].begin());
        return;
    }
    int M = (L + R) / 2;
    if (pos < M)
        upd(number, i * 2, L, M, pos);
    else upd(number, i * 2 + 1, M, R, pos);
    tree[number][i] = min(tree[number][i * 2], tree[number][i * 2 + 1]);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
/*    freopen("inp", "w", stdout);
    n = 1e5;
    printf("%d %d %d\n", n, n, n);
    fore(j, 2, n)
        printf("%d %d\n", j, rand() % (j - 1) + 1);
    fore(j, 1, n)
        printf("%d ", rand() % n + 1);
    printf("\n");
    fore(j, 1, n)
        printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, rand() % 10 + 1);
    exit(0);*/
    int Q, m;
    scanf("%d%d%d", &n, &m, &Q);
    forn(j, n - 1)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        edges[x].pb(y);
        edges[y].pb(x);
    }
    dfs(1, -1, 0);
    //printf("here\n");
    /*fore(i, 1, n)
        printf("h[%d] = %d anc[%d] = %d\n", i, h[i], i, anc[i]);*/
    get_paths();
    fore(j, 1, m)
    {
        int c;
        scanf("%d", &c);
        wher[j] = c;
        in_vertex[c].insert(j);
        if (in_vertex[c].size() > 10)
            in_vertex[c].erase(*in_vertex[c].rbegin());
    }
    forn(j, path_cnt)
    {
    /*   printf("path %d\n", j);
        for (int x : list[j])
            printf("%d ", x);
        printf("\n");*/
        tree[j].resize(list[j].size() * 4);
        build(j, 1, 0, list[j].size());
    }
    //fore(j, 1, n)
      //  printf("path_num[%d] = %d num_on_path[%d] = %d\n", j, path_num[j], j, num_on_path[j]);
    precalc_lca();
    //printf("preparations complete\n");
    //fflush(stdout);
    forn(j, Q)
    {
        int u, v, A;
        scanf("%d%d%d", &u, &v, &A);
        int l = lca(u, v);
     //   printf("lca of %d and %d is %d\n", u, v, l);
        vi ans;
        forn(iter, A)
        {
            int g1 = get_min_on_path(u, l);
            int g2 = get_min_on_path(v, l);
            int g = min(g1, g2);
            if (g == inf)
                break;
            ans.pb(g);
            int v = wher[g];
            int p = path_num[v];
            in_vertex[v].erase(g);
            upd(p, 1, 0, list[p].size(), num_on_path[v]);
        }
        for (int x : ans)
        {
            int v = wher[x];
            int p = path_num[v];
            in_vertex[v].insert(x);
            upd(p, 1, 0, list[p].size(), num_on_path[v]);
        }
        printf("%d ", (int)ans.size());
        for (int x : ans)
            printf("%d ", x);
        printf("\n");
    }
}
