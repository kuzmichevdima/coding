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

const double eps = 1.0e-8;
const int maxn = 1e5+5;

int cnt_good[maxn];
vi edges[maxn];

inline double get_ratio(int v)
{
    return (double)cnt_good[v] / edges[v].size();
}

struct cmp_struct
{
    bool operator () (int x, int y)
    {
        double rx = get_ratio(x);
        double ry = get_ratio(y);
        if (abs(rx - ry) > eps)
            return rx < ry;
        else return x < y;
    }
};

set <int, cmp_struct> order;
bool bad[maxn];
bool taken[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    forn(j, k)
    {
        int v;
        scanf("%d", &v);
        bad[v] = true;
    }
    forn(j, m)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        edges[x].pb(y);
        edges[y].pb(x);
    }
    fore(j, 1, n) if (!bad[j])
    {
        for (int u : edges[j])
            if (!bad[u])
                cnt_good[j]++;
//        ratio[j] = (double)cnt_good / edges[j].size();
        order.insert(j);
        taken[j] = true;
    }
    vi list;
    double best = -1;
    int best_step = 0;
    while(!order.empty())
    {
        int v = *order.begin();
        if (get_ratio(v) > best)
        {
            best = get_ratio(v);
            best_step = list.size();
        }
        list.pb(v);
        order.erase(order.begin());
        taken[v] = false;
//        if (abs(p.se - ratio[v]) > eps)
  //          continue;

        for (int u : edges[v]) if (taken[u] && !bad[u])
        {
            order.erase(u);
            cnt_good[u]--;
            order.insert(u);
        }
    }
/*    for (int x : list)
        printf("%d ", x);
    printf("\n");*/
    printf("%d\n", (int)list.size() - best_step);
    fore(j, best_step, list.size() - 1)
        printf("%d ", list[j]);
}
