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

i64 sum[maxn];
set <pii> * S[maxn];
map <int, int> * M[maxn];
vi edges[maxn];
int vertex_color[maxn];

inline void add(pii p, int v)
{
    //printf("add (%d %d) v = %d\n", p.fi, p.se, v);
    int color = p.fi;
    int prev;
    if (M[v]->find(color) != M[v]->end())
    {
        prev = (*M[v])[color];
        if (prev == S[v]->rbegin()->fi)
            sum[v] -= color;
        S[v]->erase(mp(prev, color));
    }
    else prev = 0;
    int new_val = prev + p.se;
//    printf("color = %d new_val = %d\n", color, new_val);
    if (S[v]->empty() || new_val > S[v]->rbegin()->fi)
    {
        sum[v] = color;
    }
    else if (new_val == S[v]->rbegin()->fi)
        sum[v] += color;
    S[v]->insert(mp(new_val, color));
    (*M[v])[color] = new_val;

}

void dfs(int v, int anc)
{
    int biggest = -1;
    for (int u : edges[v])
    {
        if (u != anc)
        {
            dfs(u, v);
            if (biggest == -1 || M[u]->size() > M[biggest]->size())
                biggest = u;
        }
    }
    if (biggest == -1)
    {
        M[v] = new map<int, int>;
        (*M[v])[vertex_color[v]] = 1;
        S[v] = new set <pii>;
        S[v]->insert(mp(1, vertex_color[v]));
        sum[v] = vertex_color[v];
        return;
    }
    M[v] = M[biggest];
    S[v] = S[biggest];
    sum[v] = sum[biggest];
    for (int u : edges[v]) if (u != anc && u != biggest)
    {
    //    printf("v = %d u = %d\n", v, u);
        for (pii p : *M[u])      
        {
            add(p, v);
        }
    }
    add(mp(vertex_color[v], 1), v);
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
    fore(j, 1, n)
        scanf("%d", &vertex_color[j]);
    forn(j, n - 1)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        edges[x].pb(y);
        edges[y].pb(x);
    }
    dfs(1, -1);
    fore(j, 1, n)
        cout << sum[j] << " ";

}
