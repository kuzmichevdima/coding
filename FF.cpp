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
#include <limits.h>

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
    int fr, to, next, f, c;
};

vector <Edge> edges;
vector <int> head;
vector <int> visited;
int n, m;

void add_edge(int v, int u, int c)
{
    edges.pb(Edge{v, u, head[v], 0, c});
    head[v] = (int)edges.size() - 1;
}

void read()
{
    scanf("%d%d", &n, &m);
    head.resize(n + 1, -1);
    forn(j, m)
    {
        int v, u, c;
        scanf("%d%d%d", &v, &u, &c);
        add_edge(v, u, c);
        add_edge(u, v, 0);
    }
}

int marker;

int dfs(int v, int flow)
{
    if (v == n)
        return flow;
    visited[v] = marker;
    for (int i = head[v]; i != -1; i = edges[i].next)
    {
        Edge & e = edges[i];
        if (e.c > e.f && visited[e.to] != marker)
        {
            int res = dfs(e.to, min(flow, e.c - e.f));
            if (res > 0)
            {
                e.f += res;
                edges[i ^ 1].f -= res;
                return res;
            }
        }
    }
    return 0;
}

void maxFlow()
{
    visited.resize(n + 1);
    marker = 0;
    i64 F = 0;
    while(true)
    {
        marker++;
        int add = dfs(1, INT_MAX);   
        if (add == 0)
            break;
        F += add;
    }
    cout << F << endl;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    read();
    maxFlow();
}

