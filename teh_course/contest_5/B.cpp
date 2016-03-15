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

#define UNDEF ((int)1e9)

const int maxh = 18;
const int maxn = 2e5+5;
const int inf = 1e9;

struct SegInfo
{
    int best, suff, pref, sum; 
    SegInfo() {}
    SegInfo(int x) : best(x), suff(x), pref(x), sum(x) {}
    SegInfo (int _best, int _suff, int _pref, int _sum) : best(_best), suff(_suff), pref(_pref), sum(_sum) {}
    void print()
    {
        printf("SegInfo %d %d %d %d\n", best, suff, pref, sum);
    }
};

int prec[maxh + 5][maxn];
bool heavy[maxn];
int anc[maxn];
int sz[maxn];
vi list[maxn];
vector <SegInfo> tree[maxn];
int num_on_path[maxn];
int path_num[maxn];
int path_cnt, n;
vi edges[maxn];
int h[maxn];
int start_w[maxn];
vi to_push[maxn];

inline SegInfo merge(SegInfo a, SegInfo b)
{
    int t1 = max(a.best, b.best);
    int t2 = a.suff + max((int)0, b.pref);
    int t3 = b.pref + max((int)0, a.suff);
    int new_best = max(t1, max(t2, t3));
    int new_suff = max(b.suff, b.sum + max((int)0, a.suff));
    int new_pref = max(a.pref, a.sum + max((int)0, b.pref));
    return SegInfo(new_best, new_suff, new_pref, a.sum + b.sum);
}

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
    if (h[x] < h[y])
        swap(x, y);
    int deltah = h[x] - h[y];
    int j = 0;
    while((1 << j) <= deltah)
    {
        if ((1 << j) & deltah)
            x = prec[j][x];
        j++;
    }
    //assert(h[x] == h[y]);
    if (x == y)
        return x;
    for (int j = maxh; j >= 0; j--) if (h[x] >= (1 << j))
    {
        int x1 = prec[j][x];
        int y1 = prec[j][y];
        if (x1 != y1)
        {
            x = x1;
            y = y1;
        }
    }
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
        tree[number][i] = SegInfo(start_w[v]);
        return;
    }
    int M = (L + R) / 2;
    build(number, i * 2, L, M);
    build(number, i * 2 + 1, M, R);
    tree[number][i] = merge(tree[number][i * 2], tree[number][i * 2 + 1]);
}

inline void push(int number, int i, int len)
{
    if (to_push[number][i] == UNDEF)
        return;
    int val = to_push[number][i];
    int best = val > 0 ? val * len : val;
    tree[number][i] = SegInfo(best, best, best, val * len);
    if (len != 1)
    {
        to_push[number][i * 2] = val;
        to_push[number][i * 2 + 1] = val;
    }
    to_push[number][i] = UNDEF;
}

inline SegInfo get(int number, int i, int L, int R, int A, int B)
{
    push(number, i, R - L);
    if (A == L && B == R)
        return tree[number][i];
    int M = (L + R) / 2;
    if (B <= M)
        return get(number, i * 2, L, M, A, B);
    else if (A >= M)
        return get(number, i * 2 + 1, M, R, A, B);
    else return merge(get(number, i * 2, L, M, A, M),
                get(number, i * 2 + 1, M, R, M, B));
}

inline SegInfo get(int number, int A, int B)
{
 //   printf("get %d %d %d\n", number, A, B);
    return get(number, 1, 0, list[number].size(), A, B);
}




inline void upd(int number, int i, int L, int R, int A, int B, int new_val)
{
    push(number, i, R - L);
    if (A >= R || L >= B)
        return;
    if (L == A && R == B)
    {
        to_push[number][i] = new_val; 
        push(number, i, R - L);
        return;
    }
    int M = (L + R) / 2;
    upd(number, i * 2, L, M, A, min(M, B), new_val);
    upd(number, i * 2 + 1, M, R, max(A, M), B, new_val);
    tree[number][i] = merge(tree[number][i * 2], tree[number][i * 2 + 1]);
}

inline void upd(int number, int A, int B, int new_val)
{
    upd(number, 1, 0, list[number].size(), A, B, new_val);
}

inline SegInfo get_on_path(int lower, int upper)
{
    printf("get_on_path %d %d\n", lower, upper);
    int cur = lower;
    SegInfo result;
    bool first_iteration = true;
    while(cur != -1)
    {
        printf("get_on_path cur = %d b = %d\n", cur, upper);
        int p = path_num[cur];
        SegInfo nnew;
        if (path_num[upper] == p)
            nnew = get(p, num_on_path[cur], num_on_path[upper] + 1);
        else nnew = get(p, num_on_path[cur], list[p].size());
        nnew.print();
        result = (first_iteration ? nnew : merge(result, nnew));
        if (path_num[upper] == p)
            break;
        cur = anc[list[p].back()];
        printf("cur = %d\n", cur);
        first_iteration = false;
    }
    return result;
}

inline void upd_on_path(int lower, int upper, int new_val)
{
    printf("upd_on_path %d %d %d\n", lower, upper, new_val);
    int cur = lower;
    while(cur != -1)
    {
        int p = path_num[cur];
        SegInfo nnew;
        if (path_num[upper] == p)
            upd(p, num_on_path[cur], num_on_path[upper] + 1, new_val);
        else upd(p, num_on_path[cur], list[p].size(), new_val);
        if (path_num[upper] == p)
            break;
        cur = anc[list[p].back()];
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
    int Q;
    scanf("%d%d", &n, &Q);
    fore(j, 1, n)
        scanf("%d", &start_w[j]);
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
    forn(j, path_cnt)
    {
       printf("path %d: ", j);
        for (int x : list[j])
            printf("%d ", x);
        printf("\n");
        tree[j].resize(list[j].size() * 4);
        to_push[j].resize(list[j].size() * 4, UNDEF);
        build(j, 1, 0, list[j].size());
    }
    //fore(j, 1, n)
      //  printf("path_num[%d] = %d num_on_path[%d] = %d\n", j, path_num[j], j, num_on_path[j]);
    precalc_lca();
    //printf("preparations complete\n");
    //fflush(stdout);
    forn(j, Q)
    {
        int typ, u, v, new_val;
        scanf("%d%d%d%d", &typ, &u, &v, &new_val);
    //    printf("query typ = %d u = %d v = %d new_val = %d\n", typ, u, v, new_val);
        int l = lca(u, v);
      //  printf("lca of %d and %d is %d\n", u, v, l);
        vi ans;
        if (typ == 2)
        {
            SegInfo g;
            if (l == u)
                g = get_on_path(v, u);
            else if (l == v)
                g = get_on_path(u, v);
            else
            {
                int dh = h[v] - h[l] - 1;
               // printf("dh = %d\n", dh);
                int t = v;
                fore(j, 0, maxh) if (dh & (1 << j))
                    t = prec[j][t];
                SegInfo g1 = get_on_path(u, l);
                SegInfo g2 = get_on_path(v, t);
                swap(g2.suff, g2.pref);
                g = merge(g1, g2);
            }
            printf("%d\n", g.best); 
        }
        else
        {
            upd_on_path(u, l, new_val);
            upd_on_path(v, l, new_val);
        }
    }
}
