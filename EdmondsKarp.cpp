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

int bfs()
{
    vector <int> fr(n + 1, -1);
    queue <int> Q;
    Q.push(1);
    while(!Q.empty())
    {
        int v = Q.front();
        Q.pop();
        for (int i = head[v]; i != -1; i = edges[i].next)
        {
            Edge & e = edges[i];
            if (e.f < e.c && fr[e.to] == -1)
            {
                fr[e.to] = i;
                Q.push(e.to);
            }
        }
    }
    if (fr[n] == -1)
        return 0;
    int cur = n;
    int flow = INT_MAX;
    while(cur != 1)
    {
        flow = min(flow, edges[fr[cur]].c - edges[fr[cur]].f);
        cur = edges[fr[cur]].fr;
    }
    
    cur = n;
    while(cur != 1)
    {
        edges[fr[cur]].f += flow;
        edges[fr[cur] ^ 1].f -= flow;
        cur = edges[fr[cur]].fr;
    }
    return flow;
}

void maxFlow()
{
    i64 F = 0;
    while(true)
    {
        int add = bfs();
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

