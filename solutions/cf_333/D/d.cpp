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

int best = -2e9;
const int P1 = 53;
const int P2 = 43;
const int MOD1 = 1e9+7;
const int MOD2 = 1e8+7;
int best_vertex_cnt;
const int maxn = 3e5+5;

set <pii> * S[maxn];
int c[maxn];
vi edges[maxn];
char letter[maxn];

inline void recalc(pii & p, char c)
{
    p = mp(((i64)p.fi * P1 + c) % MOD1, ((i64)p.se * P2 + c) % MOD2);
}

void dfs(int v, int anc, pii cur)
{
    recalc(cur, letter[v]);
    int biggest = -1;
    for (int u : edges[v]) if (u != anc)
    {
        dfs(u, v, cur);                 
        if (biggest == -1 || S[u]->size() > S[biggest]->size())
            biggest = u;
    }
    if (biggest == -1)
    {
        S[v] = new set <pii>;
        S[v]->insert(cur);
    }
    else
    {
        S[v] = S[biggest];
        S[v]->insert(cur);
        for (int u : edges[v]) if (u != anc && u != biggest)
        {
            for (pii p : *S[u])
                S[v]->insert(p);
        }
    }
    int v_val = S[v]->size() + c[v];
    if (v_val > best)
    {
        best = S[v]->size() + c[v];
        best_vertex_cnt = 1;
    }
    else if (v_val == best)
        best_vertex_cnt++;
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
        scanf("%d", &c[j]);
    scanf("\n");
    fore(j, 1, n)
        scanf("%c", &letter[j]);
    forn(j, n - 1)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        edges[x].pb(y);
        edges[y].pb(x);
    }
    dfs(1, -1, mp(0, 0));
    printf("%d\n%d", best, best_vertex_cnt);
}
