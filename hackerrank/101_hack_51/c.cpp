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
const i64 inf = 1e18;

int h[maxn];
i64 one, two, three;
vi edges[maxn];
int in[maxn];
int out[maxn];
int timer = 0;
int v[3];
int n;

void dfs(int v, int anc) {
    in[v] = timer++;
    h[v] = anc == -1 ? 0 : h[anc] + 1;
    for (int u : edges[v]) {
        if (u == anc)
            continue;
        dfs(u, v);
    }
    out[v] = timer++;
}


bool is_anc(int v, int u) {
    return in[v] <= in[u] && out[v] >= out[u];
}

int get_lca(int x, int y) {
    int result = -1;
    fore(v, 1, n)
        if (is_anc(v, x) && is_anc(v, y) && (result == -1 || h[v] > h[result]))
            result = v;
    return result;
}


/*inline void upd(int x, int y, int z) {
    i64 nnew = (i64)one * x + (i64)two * y + (i64)three * z;
    ans = min(ans, nnew);
}*/

const int maxm = 10;

i64 dist[maxm][maxm][maxm];
int prec[maxm][maxm];
bool marked[maxm][maxm][maxm];

inline void upd(int x, int y, int z, i64 val) {
    dist[x][y][z] = min(dist[x][y][z], val);
}


vi vertex;

struct Elem {
    int first, second, third;
};

int get(int x) {
    return find(vertex.begin(), vertex.end(), x) - vertex.begin();
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        scanf("%d", &n);
        cin >> one >> two >> three;
        two = min(two, 2 * one);
        three = min(three, 3 * one);
        three = min(three, one + two);
        forn(j, 3)
            scanf("%d", &v[j]);
        fore(j, 1, n)
            edges[j].clear();
        forn(j, n - 1) {
            int u, v;
            scanf("%d%d", &u, &v);
            edges[u].pb(v);
            edges[v].pb(u);
        }
        dfs(1, -1);
        vertex.clear();
        forn(j, 3)
            vertex.pb(v[j]);
        forn(first, 3)
            fore(second, first + 1, 2)
                vertex.pb(get_lca(v[first], v[second]));
        vertex.pb(1);
        sort(vertex.begin(), vertex.end());
        vertex.resize(unique(vertex.begin(), vertex.end()) - vertex.begin());

        int m = vertex.size();
        //forn(j, m)
          //  printf("vertex[%d] = %d\n", j, vertex[j]);
        forn(i, m)
            forn(j, m) {
                int lca = get_lca(vertex[i], vertex[j]);
                prec[i][j] = h[vertex[i]] - h[lca] + h[vertex[j]] - h[lca];
            }
        forn(i, m)
            forn(j, m)
                forn(k, m) {
                    dist[i][j][k] = inf;
                    marked[i][j][k] = false;
                }
        dist[get(v[0])][get(v[1])][get(v[2])] = 0;
        while(true) {
            Elem v = {-1, -1, -1};
            forn(i, m)
                forn(j, m)
                    forn(k, m)
                        if (!marked[i][j][k] && (v.fi == -1 || dist[v.fi][v.se][v.third] > dist[i][j][k])) {
                                    v = {i, j, k};
                                }
            if (v.fi == -1 || dist[v.fi][v.se][v.third] == inf)
                break;
            marked[v.fi][v.se][v.third] = true;
            i64 curd = dist[v.fi][v.se][v.third];
            forn(u, m) {
                upd(u, v.se, v.third, curd + one * prec[u][v.fi]);
                upd(v.fi, u, v.third, curd + one * prec[u][v.se]);
                upd(v.fi, v.se, u, curd + one * prec[u][v.third]);
            }
            forn(u, m) {
                if (v.fi == v.se)
                    upd(u, u, v.third, curd + two * prec[u][v.fi]);
                if (v.fi == v.third)
                    upd(u, v.se, u, curd + two * prec[u][v.fi]);
                if (v.se == v.third)
                    upd(v.fi, u, u, curd + two * prec[u][v.se]);
            }
            if (v.fi == v.se && v.fi == v.third)
                forn(u, m)
                    upd(u, u, u, curd + three * prec[u][v.fi]);
        }
        cout << dist[0][0][0] << endl;
    }
}

