#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <vector>
#include <cstdio>
#include <set>
#include <map>
#include <queue>
#include <memory.h>
#include <cmath>

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


const int inf = 1e9;
const int maxn = 105 * 105;
const int maxm = 1005 * 105;
const int source = 0;


std::vector<int>  edges[maxn], chosen[maxn];
int current[maxn];
std::vector<int> list;
int flow[maxm];
int cap[maxm];
int target;
int dist[maxn];

int dfs(int ver, int cur_flow)
{
    if (ver == target)
        return cur_flow;
    for (size_t jj = current[ver]; jj < chosen[ver].size(); ++jj)
    {
        int id = chosen[ver][jj];
        int uu = list[id];
        if (cap[id] > flow[id])
        {
            int tmp = std::min(cur_flow, cap[id] - flow[id]);
            int ret = dfs(uu, tmp);
            if (ret)
            {
                flow[id] += ret;
                flow[id ^ 1] -= ret;
                return ret;
            }
        }
        current[ver]++;
    }
    return 0;
}


void bfs()
{
    std::queue <int> order;
    dist[source] = 0;
    for (int j = 1; j <= target; ++j) {
        dist[j] = inf;
    }
    order.push(source);
    while (!order.empty())
    {
        int ver = order.front();
        order.pop();
        for (size_t j = 0; j < edges[ver].size(); ++j)
        {
            int id = edges[ver][j];
            int uu = list[id];
            if (cap[id] > flow[id] && dist[uu] == inf)
            {
                dist[uu] = dist[ver] + 1;
                order.push(uu);
            }
        }
    }
}

inline void add_edge(int fr, int to, int cc) {
    //printf("add edge from %d to %d cap = %d\n", fr, to, cc);
    edges[fr].push_back(list.size());
    cap[list.size()] = cc;
    list.push_back(to);

    edges[to].push_back(list.size());
    cap[list.size()] = 0;
    list.push_back(fr);
}



int maxflow() {
    int answer = 0;
    dist[target] = 0;
    while (dist[target] != inf)
    {
        bfs();
        // printf("dist[target] = %d\n", dist[target]);
        if (dist[target] == inf)
            break;
        memset(current, 0, sizeof(current));
        for (int v = 0; v <= target; ++v) {
            chosen[v].clear();
            for (int id : edges[v]) {
                int to = list[id];
                if (dist[to] == dist[v] + 1)
                    chosen[v].push_back(id);
            }
        }
        int to_add = 1;
        while (to_add)
        {
            to_add = dfs(source, inf);
            answer += to_add;
        }
    }
    return answer;
}


pii primal[maxm];
int n, m, k;

int get(int v, int t) {
    return v + t * n;
}

int f(int middle) {
    target = n * (middle + 1) + 1;
    fore(j, source, target)
        edges[j].clear();
    list.clear();
    add_edge(source, get(1, 0), k);
    fore(t, 0, middle)
        add_edge(get(n, t), target, k);
    forn(j, m)
        fore(t, 0, middle - 1) {
            add_edge(get(primal[j].fi, t), get(primal[j].se, t + 1), 1);
        }
    fore(j, 0, list.size())
        flow[j] = 0;
    int res = maxflow();
    //printf("result %d\n", res);
    return res;
}

int main()
{
#ifdef LOCAL
    freopen("inp", "r", stdin);
#endif
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        scanf("%d%d%d", &n, &m, &k);
        // printf("n = %d m = %d k = %d\n", n, m, k);
        forn(j, m)
            scanf("%d%d", &primal[j].fi, &primal[j].se);
        int start = 0;
        int finish = n - 1;
        while(start < finish) {
            int middle = (start + finish) / 2;
            int cur = f(middle);
            // printf("f[%d] = %d\n", middle, cur);
            if (cur >= k)
                finish = middle;
            else start = middle + 1;
        }
        if (f(start) >= k)
            printf("%d\n", start);
        else printf("-1\n");
    }
    return 0;
}
