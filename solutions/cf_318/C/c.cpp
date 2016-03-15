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

bool deleted[maxn];
vi edges[maxn];
int legs[maxn];

void dfs(int v, int anc)
{
    if (edges[v].size() <= 2)
    {
        deleted[v] = true;
        for (int u : edges[v]) if (u != anc)
            dfs(u, v);
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
    int n;
    scanf("%d", &n);
    forn(j, n - 1)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        edges[u].pb(v);
        edges[v].pb(u);
    }
    fore(j, 1, n)
        if (edges[j].size() == 1)
            dfs(j, -1);
    fore(j, 1, n)
    {
        for (int u : edges[j]) if (deleted[u])
            legs[j]++;       
        legs[j] = min(legs[j], 2);
    }
    fore(j, 1, n) if (!deleted[j])
    {
        int cnt = 0;
        for (int u : edges[j])
            if (!deleted[u] && (int)edges[u].size() > 1 + legs[u])
                cnt++;
        if (cnt > 2)
        {
            printf("No");
            exit(0);
        }
    }
    printf("Yes");
}
